CC=gcc
CFLAGS=-lsnappy

build:
	${CC} ${CFLAGS} -o ./snappy src/main.c

debug:
	${CC} ${CFLAGS} -o ./snappy src/main.c -g

install:
	cp ./snappy /usr/bin/snappy
