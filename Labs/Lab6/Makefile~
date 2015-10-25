CC = gcc
CFLAGS = -Wall
EXECS = wrappers recv_udp send_udp

all: $(EXECS)

recv_udp: recv_udp.c
	$(CC) $(CFLAGS) recv_udp.c wrappers.o -o recv_udp
send_udp: send_udp.c
	$(CC) $(CFLAGS) send_udp.c wrappers.o -o send_udp
wrappers: wrappers.c
	$(CC) $(CFLAGS) wrappers.c -c

.PHONY: clean
clean:
	rm -rf $(EXECS) *.o
