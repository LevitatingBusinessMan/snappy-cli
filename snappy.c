#include <snappy-c.h>
#include <argp.h>
#include <stdlib.h>
#include <string.h>

const char *argp_program_version = "v1.0.0";
const char *argp_program_bug_address = "https://github.com/LevitatingBusinessMan/snappy-cli";

static char args_doc[] = "FILE";

static char doc[] = "snappy-cli, a cli utility for compressing files via snappy";

struct arguments {
	enum {COMPRESS, DECOMPRESS} mode;
	char* filename;
	char* outfile;
	enum {STDOUT, OUTFILE} output;
	int arg_count;
};

static struct argp_option options[] = {
	{ "compress", 'c', 0, 0, "Compress file (default)"},
	{ "decompress", 'd', 0, 0, "Decompress file"},
	{ "output", 'o', "FILE", 0, "New file to create"},
	{0}
};

error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
	struct arguments *arguments = state->input;
	switch (key)
	{
		case 'c': arguments->mode = COMPRESS; break;
		case 'd': arguments->mode = DECOMPRESS; break;
		case 'o':
			arguments->output = OUTFILE;
			if (arg == 0) {
				argp_failure (state, 1, 0, "missing output file");
			} else {
				arguments->outfile = arg;
			}
			break;
		case ARGP_KEY_ARG:
			arguments->arg_count++;
			arguments->filename = arg;
		case ARGP_KEY_END:
			if (arguments->arg_count < 1) {
				argp_failure (state, 1, 0, "too few arguments");
			} else if (arguments->arg_count > 1) {
				argp_failure (state, 1, 0, "too many arguments");
			}
			break;
		default:
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

static struct argp argp = {options, parse_opt, args_doc, doc};

int read_file(const char *path, char **contents);
int write_file(char *path, char *data, size_t data_length);
int read_stdin(char **result);

int main(int argc, char *argv[]) {

	struct arguments arguments;

	arguments.arg_count = 0;
	arguments.mode = COMPRESS;
	arguments.output = STDOUT;
	argp_parse (&argp, argc, argv, 0, 0, &arguments);
	enum {COMPRESS, DECOMPRESS} mode = arguments.mode;
	char *filename = arguments.filename;
	enum {STDOUT, OUTFILE} output = arguments.output;
	char *outfile = arguments.outfile;

	char *contents;

	int file_size;

	if (strcmp(filename, "-") == 0) {
		file_size = read_stdin(&contents);
	} else {
		file_size = read_file(filename, &contents);
	}

	if (file_size < 1) {
		exit(1);
	}

	size_t output_length;

	if (mode == COMPRESS) output_length = snappy_max_compressed_length(file_size);
	else snappy_uncompressed_length(contents, file_size, &output_length);

	char *output_buffer = malloc(output_length);

	if (mode == COMPRESS) {
		if (snappy_compress(contents, file_size, output_buffer, &output_length) != SNAPPY_OK) {
			printf("Failed to compress data\n");
			exit(1);
		}
	}

	if (mode == DECOMPRESS) {
		if (snappy_uncompress(contents, file_size, output_buffer, &output_length) != SNAPPY_OK) {
			printf("Failed to decompress data (invalid input)\n");
			exit(1);
		}
	}

	if (output == OUTFILE) {
		if (write_file(outfile, output_buffer, output_length) < 0) exit(1);
		printf("Written new data to \"%s\", (old: %d, new: %zu, net: %zu, %.0f%%)\n",
			outfile,
			file_size,
			output_length,
			output_length - file_size,
			(float) output_length / (float) file_size * 100.0
		);
	}

	//To STDOUT
	else {
		fwrite(output_buffer, output_length, 1, stdout);
	}

	free(contents);
	free(output_buffer);
}

int read_file(const char *path, char **contents) {
	FILE* file = fopen(path, "r");

	if (file == NULL) {
		perror("Failed to open file");
		return -1;
	}

	if (fseek(file, 0, SEEK_END) < 0) {
		perror("Failed to open file");
		return -1;
	}

	size_t file_size = ftell(file);
	rewind(file);

	if (file_size == 0) {
		fprintf(stderr, "Source file is empty\n");
		return -1;
	}

	char *buffer = malloc(file_size);
	size_t n_read = fread(buffer, 1, file_size, file);
	if (n_read < file_size) {
		perror("Failed to read file");
		return -1;
	}

	fclose(file);
	*contents = buffer;

	return (int) n_read;
}

int write_file(char *path, char *data, size_t data_length) {
	FILE* file = fopen(path, "w");
	if (file == NULL) {
		perror("Failed to open file for writing");
		return -1;
	}

	if (fwrite(data, data_length, 1, file) < 0) {
		perror("Failed to write to file");
		return -1;
	};

	fclose(file);
	return 0;
}

int read_stdin(char **result) {
	int buffer_size = 10000;
	char *buffer = malloc(buffer_size);
	int length = 0;
	char c;
	while ((c=getchar()) != EOF) {
		if (length >= buffer_size) {
			buffer_size = buffer_size * 2;
			buffer = realloc(buffer, buffer_size);
		}
		buffer[length] = c;
		length++;
	}

	*result = buffer;
	return length;
}
