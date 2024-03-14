.POSIX:
CC = clang++
CFLAGS = -W -O
LIBS = -L/usr/local/lib -lcrossguid -lid3
INCS = -I/usr/local/include

id3test:
	${CC} id3tags.cpp testid3.cpp ${INCS} ${LIBS} -o id3test
socketstest:
	${CC} -g modules/c++/**.cpp main.cpp -o socketstest
	./socketstest
threadstest:
	${CC} -g test.cpp -o threadstest
	./threadstest
clean:
	rm -rf test
