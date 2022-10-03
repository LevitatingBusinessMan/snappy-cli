CC=gcc
CFLAGS=
LDLIBS=-lsnappy

build:
	${CC} ${CFLAGS} snappy.c ${LDLIBS} -o ./snappy

debug:
	${CC} ${CFLAGS} snappy.c ${LDLIBS} -o ./snappy -g

install:
	install -Dvm 755 ./snappy ${DESTDIR}/usr/bin/snappy

clean:
	rm -v snappy
