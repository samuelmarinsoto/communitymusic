.POSIX:
CC = clang++
CFLAGS = -W -O
LIBS = -L/usr/local/lib -lcrossguid -lid3
INCS = -I/usr/local/include

test:
	${CC} id3tags.cpp testid3.cpp ${INCS} ${LIBS} -o test
clean:
	rm -rf test
