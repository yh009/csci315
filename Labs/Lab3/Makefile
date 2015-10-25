CC = gcc
CFLAGS = -Wall -lm -lpthread
EXECS = summation	summation4	summation5

all: $(EXECS)

summation: summation.c
	$(CC) $(CFLAGS) summation.c -o summation
summation4: summation4.c
	$(CC) $(CFLAGS) summation4.c -o summation4
summation5: summation5.c
	$(CC) $(CFLAGS) summation5.c -o summation5

.PHONY: clean
clean:
	rm -rf $(EXECS) *.o