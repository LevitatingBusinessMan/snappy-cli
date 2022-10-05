CC=gcc
CFLAGS=
LDLIBS=-lsnappy

ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

build:
	${CC} ${CFLAGS} snappy.c ${LDLIBS} -o ./snappy

debug:
	${CC} ${CFLAGS} snappy.c ${LDLIBS} -o ./snappy -g

install:
	install -Dvm 755 ./snappy ${DESTDIR}${PREFIX}/bin/snappy

clean:
	rm -v snappy
