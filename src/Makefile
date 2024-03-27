.POSIX:
CC = clang++
CFLAGS = -W -O0
LIBS = -L/usr/lib -L/usr/local/lib -L/usr/lib/x86_64-linux-gnu -L. -ltag
INCS = -I/usr/include -I/usr/local/include -I../modules/c++/ -I../lib/

.ifdef OPENBSD
X11INC = -I/usr/X11R6/include
X11LIB = -L/usr/X11R6/lib -lX11 -lxcb -lXau -lXdmcp -lXft -lXss -lfontconfig -lXext -lfreetype -lXrender -lz -lexpat
LIBS = -L/usr/lib -L/usr/local/lib ${X11LIB} -pthread -lid3 -ltk86 -ltcl86 -ltkstub86 -ltclstub86 -lcrossguid
INCS = -I/usr/local/include -I/usr/include ${X11INC}
.endif

id3test: mp3tags
	${CC} ${CFLAGS} testid3.cpp ${INCS} ${LIBS} -o $@
mp3tags:
	${CC} ${CFLAGS} -c modules/c++/MP3Tags.hpp ${INCS} ${LIBS} -o mp3tags.o
	ar rcs libmp3tags.a mp3tags.o
socketstest:
	${CC} -g modules/c++/**.cpp main.cpp -o $@
threadstest:
	${CC} -g test.cpp -o $@
clean:
	rm -rf id3test *.a *.o
