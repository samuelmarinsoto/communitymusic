.POSIX:
CC = clang++
CFLAGS = -W -O0
LIBS = -L/usr/lib -L/usr/local/lib -L/usr/lib/x86_64-linux-gnu -L.
INCS = -I/usr/include -I/usr/local/include -I./modules/c++

.ifdef OPENBSD
LIBS = -L/usr/lib -L/usr/local/lib -L.
INCS = -I/usr/local/include -I/usr/include -I./modules/c++
.endif

id3test: mp3tags
	${CC} ${CFLAGS} testid3.cpp ${INCS} ${LIBS} -lmp3tags -lz -ltag -lboost_filesystem -lboost_random -o $@
mp3tags:
	${CC} ${CFLAGS} -c modules/c++/MP3Tags.cpp ${INCS} ${LIBS} -o $@.o
	ar rcs lib$@.a $@.o
pagedarray: mp3tags
	${CC} ${CFLAGS} -c modules/c++/PagedArray.cpp ${INCS} ${LIBS} -o $@.o
	ar rcs lib$@.a $@.o
testpa: mp3tags pagedarray
	${CC} ${CFLAGS} testpagedarray.cpp ${INCS} ${LIBS} -lmp3tags -lpagedarray -lz -ltag -lboost_filesystem -lboost_random -o $@
clean:
	rm -rf id3test testpa *.a *.o *.core *.bin
