CC = gcc
EXECS = pipes upper tokens

all: $(EXECS)

pipes.o: pipes.c
	$(CC) -c pipes.c -o pipes.o

upper.o: upper.c
	$(CC) -c upper.c -o upper.o

tokens.o: tokens.c
	$(CC) -c tokens.c -o tokens.o

.PHONY: clean
clean:
	rm -rf $(EXECS) *.o
