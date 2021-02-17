CC=gcc
CFLAGS=-lsnappy

build:
	${CC} ${CFLAGS} -o ./snappy src/main.c -g

