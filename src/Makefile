.POSIX:
CC = clang++
CFLAGS = -W -O
LIBS = -L/usr/lib -lcrossguid -lid3
INCS = -I/usr/include
TKINCS = -I/usr/include/tk8.6 -I/usr/include/tcl8.6

.ifdef OPENBSD
LIBS = -L/usr/local/lib -lcrossguid -lid3
INCS = -I/usr/local/include
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
