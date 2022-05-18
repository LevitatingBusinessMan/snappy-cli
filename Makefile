CC=gcc
CFLAGS=-lsnappy

build:
	${CC} ${CFLAGS} -o ./snappy snappy.c

debug:
	${CC} ${CFLAGS} -o ./snappy snappy.c -g

install:
	install -Dvm 755 ./snappy ${DESTDIR}/usr/bin/snappy

clean:
	rm -v snappy
