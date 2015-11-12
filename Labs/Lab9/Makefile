
CC = gcc -I ./include
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG
LFLAGS = -lm

INC = ./include
SRC = ./src
OBJ = ./obj
DOC = ./doc
BIN = ./bin

vpath %.h ./include
vpath %.c ./src

EXECS = dlisttest memory-test student frag-eval

all: $(EXECS)

doc:
	doxygen

student:
	$(CC) $(CFLAGS) sfu.c dfu.c student.c $(LFLAGS) -o student

$(OBJ)/dnode.o: dnode.h dnode.c
	$(CC) $(CFLAGS) -c $(SRC)/dnode.c -o $(OBJ)/dnode.o

$(OBJ)/dlist.o: dlist.h dlist.c dnode.h
	$(CC) $(CFLAGS) -c $(SRC)/dlist.c -o $(OBJ)/dlist.o

dlisttest: $(SRC)/dlisttest.c $(OBJ)/dnode.o $(OBJ)/dlist.o
	$(CC) $(CFLAGS) $(OBJ)/dnode.o $(OBJ)/dlist.o $(SRC)/dlisttest.c -o $(BIN)/dlisttest

$(OBJ)/allocator.o: allocator.h dlist.h dnode.h  allocator.c 
	$(CC) $(CFLAGS) -c $(SRC)/allocator.c -o $(OBJ)/allocator.o

memory-test: $(OBJ)/allocator.o $(SRC)/memory-test.c
	$(CC) $(CFLAGS) $(OBJ)/dnode.o $(OBJ)/dlist.o $(OBJ)/allocator.o $(SRC)/memory-test.c -o $(BIN)/memory-test

frag-eval: $(OBJ)/allocator.o $(SRC)/frag-eval.c
	$(CC) $(CFLAGS) $(OBJ)/dnode.o $(OBJ)/dlist.o $(OBJ)/allocator.o $(SRC)/frag-eval.c -o $(BIN)/frag-eval


.PHONY: clean
clean:
	/bin/rm -rf $(BIN)/* $(OBJ)/* core* *~

