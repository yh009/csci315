CC = gcc
CFLAGS = -Wall -lpthread
EXECS = dp

all: $(EXECS)

dp:dp.c
	$(CC) $(CFLAGS) dp.c -o dp

.PHONY: clean
clean:
	rm -rf $(EXEC) *.o