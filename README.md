# snappy-cli
This is a cli program for the very fast compression library [snappy](https://github.com/google/snappy) developed by google. With this binary you can easily test snappy's compression, or use compression in shell scripts.

## Usage
```
Usage: snappy [OPTION...] FILE
snappy-cli, a cli utility for compressing files via snappy

  -c, --compress             Compress file
  -d, --decompress           Decompress file
  -o, --output=FILE          New file to create
  -?, --help                 Give this help list
      --usage                Give a short usage message
  -V, --version              Print program version
```
For instance to compress a file you can run
```
snappy filename > compressed_file
```
You can also read from stdin
```
cat filename | snappy - > compressed_file
```

## Build
Make sure that the package `libsnappy-dev` (Debian) or `snappy` (Arch) is installed.
```
git clone https://github.com/LevitatingBusinessMan/snappy-cli.git
cd snappy-cli
make
sudo make install
```
