CC=gcc
GTKLIBS=`pkg-config --libs gtk+-3.0`
GTKFLAGS=`pkg-config --cflags gtk+-3.0`
DEVFLAGS=-ggdb

SOURCES := $(wildcard *.c)
OBJECTS := $(patsubst %.c, ../../bin/%.o, ${SOURCES})

.DEFAULT_TARGET: all

all: ${OBJECTS}

show:
	@echo ${OBJECTS}

../../bin/%.o: %.c
	${CC} $^ ${GTKFLAGS} ${DEVFLAGS} ${GTKLIBS} -c -o $@
