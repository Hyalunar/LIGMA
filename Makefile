CC=gcc
RM=rm
MKDIR=mkdir
GTKLIBS=`pkg-config --libs gtk+-3.0`
GTKFLAGS=`pkg-config --cflags gtk+-3.0`
DEVFLAGS=-ggdb

.DEFAULT_TARGET := dev

dev: bin/ligma-dev
release: ligma-release

bin/ligma-dev: src/main.c src/mainWindow.c src/toolbar.c src/viewport.c src/imagelist.c
	${CC} $^ ${GTKFLAGS} ${DEVFLAGS} -o bin/ligma-dev ${GTKLIBS}

clean:
	${RM} -r bin/
	${MKDIR} bin