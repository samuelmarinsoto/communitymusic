.POSIX:
CC = clang++
CFLAGS = -g -W -O0

MODS = app/c++/**.cpp lib/**.cpp modules/c++/**.cpp
TAGS = -lboost_filesystem -lboost_random -ltag -lglog
SYS = -L/usr/lib -L/usr/local/lib -L/usr/lib/x86_64-linux-gnu -L.
SERVER = -lX11 -lXrandr -lmpg123 -lsndfile -lsfml-system -lsfml-audio -lsfml-graphics -lsfml-window -lglog
LOCAL_INCS = -Iapp/c++/*.hpp -Ilib/**.h -Ilib/**.hpp -Imodules/c++/**.hpp -Imodules/c++/**.h

INCS = -I/usr/include -I/usr/local/include ${LOCAL_INCS}

.ifdef OPENBSD
SYS = -L/usr/lib -L/usr/local/lib -L/usr/X11R6/lib -L.
INCS = -I/usr/local/include -I/usr/include ${LOCAL_INCS}
.endif

LIBS = ${SYS} ${SERVER} ${TAGS}


server: mp3tags pagedarray
	${CC} ${CFLAGS} ${MODS} main.cpp ${INCS} ${LIBS} -lmp3tags -lpagedarray -o $@
id3test: mp3tags
	${CC} ${CFLAGS} test/testid3.cpp ${INCS} ${SYS} ${TAGS} -lmp3tags -o $@
mp3tags:
	${CC} ${CFLAGS} -c modules/c++/MP3Tags.cpp ${INCS} ${SYS} ${TAGS} -o $@.o
	ar rcs lib$@.a $@.o
pagedarray: mp3tags
	${CC} ${CFLAGS} -c modules/c++/PagedArray.cpp ${INCS} ${SYS} ${TAGS} -o $@.o
	ar rcs lib$@.a $@.o
mod:
	for i in app/c++/**.cpp;do \
		${CC} ${CFLAGS} -c $$i ${INCS} ${LIBS} -o app.o; \
	done
	for i in modules/c++/**.cpp;do \
		${CC} ${CFLAGS} -c $$i ${INCS} ${LIBS} -o mod.o; \
	done
	for i in lib/**.cpp;do \
		${CC} ${CFLAGS} -c $$i ${INCS} ${LIBS} -o lib.o; \
	done
	ar rcs lib$@.a app.o mod.o lib.o
testpa: mp3tags pagedarray
	${CC} ${CFLAGS} test/testpagedarray.cpp ${INCS} ${LIBS} -lmp3tags -lpagedarray -lz -ltag -lboost_filesystem -lboost_random -o $@
cleanall: cleanserv
	rm -rf id3test testpa *.a *.o *.core *.bin
cleanserv:
	rm -rf server
