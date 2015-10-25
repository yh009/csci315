CC = gcc
CFLAGS = -Wall -lpthread
EXECS = dp problem1

all: $(EXECS)

dp:dp.c
	$(CC) $(CFLAGS) dp.c -o dp

problem1:problem1.c
	$(CC) $(CFLAGS) problem1.c -o problem1

.PHONY: clean
clean:
	rm -rf $(EXEC) *.o