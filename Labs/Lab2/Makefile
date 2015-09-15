CC = gcc
EXECS = pipes upper tokens

all: $(EXECS)
pipes.o: pipes.c
         $(CC) -c pipes.c

upper.o: upper.c
         $(CC) -c upper.c

tokens.o: tokens.c
         $(CC) -c tokens.c

.PHONY: clean
clean:
         /bin/rm -rf $(EXECS) *.o
