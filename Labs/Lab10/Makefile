CC = gcc
CFLAGS = -Wall
EXECS = ishell

all: $(EXECS)

ishell: ishell.c
	$(CC) $(CFLAGS) ishell.c -o ishell

.PHONY: clean
clean:
	rm -rf $(EXECS) *.o
