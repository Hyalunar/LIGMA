CC=gcc
RM=rm
MKDIR=mkdir
GTKLIBS=`pkg-config --libs gtk+-3.0`
GTKFLAGS=`pkg-config --cflags gtk+-3.0`
DEVFLAGS=-ggdb

.DEFAULT_TARGET := dev

dev: bin/ligma-dev
release: ligma-release

bin/ligma-dev: src/main.c \
				src/ui/mainWindow.c src/ui/toolbar.c src/ui/viewport.c src/ui/imagelist.c src/ui/colorchooser.c \
				src/logic/image.c
	${CC} $^ ${GTKFLAGS} ${DEVFLAGS} -o bin/ligma-dev ${GTKLIBS}

clean:
	${RM} -r bin/
	${MKDIR} bin