.POSIX:
CC = clang++
CFLAGS = -g -W -O0

SRCS = app/c++/**.cpp lib/**.cpp modules/c++/**.cpp
TAGS = -lboost_filesystem -lboost_random -ltag -lglog
SYS = -L/usr/lib -L/usr/local/lib -L/usr/lib/x86_64-linux-gnu -L.
SERVER = -lX11 -lXrandr -lmpg123 -lsndfile -lsfml-system -lsfml-audio -lsfml-graphics -lsfml-window -lglog
LOCAL_INCS = -Iapp/c++ -Ilib -Imodules/c++

INCS = -I/usr/include -I/usr/local/include ${LOCAL_INCS}

.ifdef OPENBSD
SYS = -L/usr/lib -L/usr/local/lib -L/usr/X11R6/lib -L.
INCS = -I/usr/local/include -I/usr/include ${LOCAL_INCS}
.endif

LIBS = ${SYS} ${SERVER} ${TAGS}


server:
	${CC} ${CFLAGS} ${SRCS} main.cpp ${INCS} ${LIBS} -o $@
id3test: mp3tags
	${CC} ${CFLAGS} test/testid3.cpp ${INCS} ${SYS} ${TAGS} -lmp3tags -o $@
testpa: libmp3tags.a libpagedarray.a
	${CC} ${CFLAGS} test/testpagedarray.cpp ${INCS} ${LIBS} -lmp3tags -lpagedarray -o $@
libmp3tags.a:
	${CC} ${CFLAGS} -c modules/c++/MP3Tags.cpp ${INCS} ${SYS} ${TAGS} -o $@.o
	ar rcs lib$@.a $@.o
libpagedarray.a: libmp3tags.a
	${CC} ${CFLAGS} -c modules/c++/PagedArray.cpp ${INCS} ${SYS} ${TAGS} -o $@.o
	ar rcs lib$@.a $@.o
libmod.a: ${SRCS}
	${CC} ${CFLAGS} -c ${SRCS} ${INCS} ${LIBS}
	ar rcs $@ $(notdir $(SRCS:.cpp=.o))
cleanall: cleanserv
	rm -rf id3test testpa *.a *.o *.core *.bin
cleanserv:
	rm -rf server
