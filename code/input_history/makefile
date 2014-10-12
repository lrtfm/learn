CC=gcc
SOURCE_DIR=src
OBJECT_DIR=obj
BIN_DIR=bin
#CFLAGS=-g -c
NCURSES_CFLAGS=$(shell pkg-config --cflags ncurses)
NCURSES_LIBS=$(shell pkg-config --libs ncurses)
CFLAGS=-g ${NCURSES_CFLAGS}

all:input_history

input_history:create_dir ${SOURCE_DIR}/main.c
	${CC} ${CFLAGS} -o ${BIN_DIR}/input_history ${SOURCE_DIR}/main.c ${NCURSES_LIBS}

test:
	@echo "nothing to test"


create_dir:
	mkdir -p ${OBJECT_DIR}
	mkdir -p ${BIN_DIR}

clean:
	rm -rf ${BIN_DIR} ${OBJECT_DIR}
