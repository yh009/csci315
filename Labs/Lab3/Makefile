CC = gcc
CFLAGS = -Wall -lm -lpthread
EXECS = summation

all: $(EXECS)

summation: summation.c
	$(CC) $(CFLAGS) -c summation.c -o summation.o

.PHONY: clean
clean:
	rm -rf $(EXECS) *.o