CC=gcc
CFLAGS=-lsnappy

build:
	${CC} ${CFLAGS} -o ./snappy src/main.c

debug:
	${CC} ${CFLAGS} -o ./snappy src/main.c -g

install:
	install -Dvm 755 ./snappy /usr/bin/snappy

clean:
	rm -v snappy
