.POSIX:
CC = clang++
CFLAGS = -g -W -O0

MODS = app/c++/**.cpp lib/**.cpp modules/c++/**.cpp
TAGS = -lboost_filesystem -lboost_random -ltag
SYS = -L/usr/lib -L/usr/local/lib -L/usr/lib/x86_64-linux-gnu 
SERVER = -lmpg123 -lsndfile -lsfml-system -lsfml-audio -lsfml-graphics -lsfml-window
SERVER_INCS = -Iapp/c++/*.hpp -Ilib/**.h -Ilib/**.hpp -Imodules/c++/**.hpp -Imodules/c++/**.h

INCS = -I/usr/include -I/usr/local/include ${SERVER_INCS}

.ifdef OPENBSD
SYS = -L/usr/lib -L/usr/local/lib -L.
INCS = -I/usr/local/include -I/usr/include ${SERVER_INCS}
.endif

LIBS = ${SYS} ${SERVER} ${TAGS}


server:
	${CC} ${CFLAGS} ${MODS} main.cpp ${INCS} ${LIBS} -o $@
id3test: mp3tags
	${CC} ${CFLAGS} testid3.cpp ${INCS} ${SYS} ${TAGS} -lmp3tags -o $@
mp3tags:
	${CC} ${CFLAGS} -c modules/c++/MP3Tags.cpp ${INCS} ${SYS} ${TAGS} -o $@.o
	ar rcs lib$@.a $@.o
pagedarray: mp3tags
	${CC} ${CFLAGS} -c modules/c++/PagedArray.cpp ${INCS} ${LIBS} -o $@.o
	ar rcs lib$@.a $@.o
testpa: mp3tags pagedarray
	${CC} ${CFLAGS} testpagedarray.cpp ${INCS} ${LIBS} -lmp3tags -lpagedarray -lz -ltag -lboost_filesystem -lboost_random -o $@
clean:
	rm -rf id3test testpa server *.a *.o *.core *.bin
