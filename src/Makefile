.POSIX:
CC = clang++
CFLAGS = -W -O
LIBS = -L/usr/lib -lcrossguid -lid3
INCS = -I/usr/include

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
clean:
	rm -rf threadstest socketstest id3test
