.POSIX:
CC = clang++
CFLAGS = -W -O
LIBS = -L/usr/lib -luuid -lid3
INCS = -I/usr/include

.ifdef OPENBSD
X11INC = -I/usr/X11R6/include
X11LIB = -L/usr/X11R6/lib -lX11 -lxcb -lXau -lXdmcp -lXft -lXss -lfontconfig -lXext -lfreetype -lXrender -lz -lexpat
LIBS = -L/usr/lib -L/usr/local/lib ${X11LIB} -pthread -lid3 -ltk86 -ltcl86 -ltkstub86 -ltclstub86 -lcrossguid
INCS = -I/usr/local/include -I/usr/include ${X11INC}
TKINCS = -I/usr/local/include/tk86 -I/usr/local/include/tcl86
.endif

id3test:
	${CC} ${CFLAGS} Cancion.cpp testid3.cpp ${INCS} ${LIBS} -o id3test
socketstest:
	${CC} ${CFLAGS} -g modules/c++/**.cpp main.cpp -o socketstest
	./socketstest
threadstest:
	${CC} ${CFLAGS} -g test.cpp -o threadstest
	./threadstest
main:
	${CC} ${CFLAGS} -g modules/c++/**.cpp main.cpp ${INCS} ${TKINCS} ${LIBS} -o program_binary
	./program_binary
clean:
	rm -rf threadstest socketstest id3test program_binary
