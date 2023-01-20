RM        := rm
MKDIR     := mkdir
CD        := cd
DIR_DELIM := /

CC=gcc
GTKLIBS=`pkg-config --libs gtk+-3.0`
GTKFLAGS=`pkg-config --cflags gtk+-3.0`
DEVFLAGS=-ggdb

.DEFAULT_TARGET := dev

dev: bin/ligma-dev
release: bin/ligma-release

bin/ligma-dev: uiobjects logicobjects
	${CC} $(wildcard bin${DIR_DELIM}*.o) src${DIR_DELIM}main.c ${GTKFLAGS} ${DEVFLAGS} -o bin${DIR_DELIM}ligma-dev ${GTKLIBS}

uiobjects: src/ui/Makefile
	cd src/ui && ${MAKE}

logicobjects: src/logic/Makefile
	cd src/logic && ${MAKE}

clean:
	${RM} -r bin
	${MKDIR} bin
