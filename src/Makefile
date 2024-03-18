.POSIX:
CC = clang++
CFLAGS = -W -O
LIBS = -L/usr/lib -lcrossguid -lid3
INCS = -I/usr/include
TKINCS = -I/usr/include/tk8.6 -I/usr/include/tcl8.6

.ifdef OPENBSD
LIBS = -L/usr/local/lib -L/usr/X11R6/lib -lcrossguid -lid3 -lX11
INCS = -I/usr/X11R6/include -I/usr/local/include
TKINCS = -I/usr/local/include/tk8.6 -I/usr/local/include/tcl8.6
.endif

id3test:
	${CC} ${CFLAGS} id3tags.cpp testid3.cpp ${INCS} ${LIBS} -o id3test
socketstest:
	${CC} ${CFLAGS} -g modules/c++/**.cpp main.cpp -o socketstest
	./socketstest
threadstest:
	${CC} ${CFLAGS} -g test.cpp -o threadstest
	./threadstest
tktest:
	${CC} ${CFLAGS} -g modules/c++/**.cpp main.cpp ${INCS} ${TKINCS} ${LIBS} -o tktest
	./tktest
clean:
	rm -rf threadstest socketstest id3test
