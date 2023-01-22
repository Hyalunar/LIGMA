RM        := rm
MKDIR     := mkdir
CD        := cd
DIR_DELIM := /

CC=gcc
GTKLIBS=`pkg-config --libs gtk+-3.0`
GTKFLAGS=`pkg-config --cflags gtk+-3.0`
DEVFLAGS=-ggdb
SHAREDFLAGS=-pie -shared

.DEFAULT_TARGET: all

PLUGIN_SOURCES := $(wildcard src${DIR_DELIM}plugins${DIR_DELIM}*.c)
PLUGIN_DLLS    := $(patsubst src/plugins/%.c, bin${DIR_DELIM}plugs${DIR_DELIM}%.so, ${PLUGIN_SOURCES})

all: dev plugins
dev: bin/ligma-dev
plugins: ${PLUGIN_DLLS}

bin/ligma-dev: uiobjects logicobjects
	${CC} $(wildcard bin${DIR_DELIM}*.o) src${DIR_DELIM}main.c ${GTKFLAGS} ${DEVFLAGS} -o bin${DIR_DELIM}ligma-dev ${GTKLIBS}

uiobjects: src/ui/Makefile
	cd src/ui && ${MAKE}

logicobjects: src/logic/Makefile
	cd src/logic && ${MAKE}

bin/plugs/%.so: src/plugins/%.c
	${CC} $^ ${DEVFLAGS} ${SHAREDFLAGS} -o $@

clean:
	${RM} -r bin
	${MKDIR} bin
	${MKDIR} bin${DIR_DELIM}plugs
