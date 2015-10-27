CC = gcc
CFLAGS = -g -Wall -lpthread
EXECS = wrappers readwrite recv_udp send_udp getfile fileserver getstats

all: $(EXECS)

wrappers: wrappers.c wrappers.h
	$(CC) $(CFLAGS) wrappers.c -c
readwrite: readwrite.c readwrite.h
	$(CC) $(CFLAGS) readwrite.c -c
recv_udp: recv_udp.c
	$(CC) $(CFLAGS) recv_udp.c wrappers.o -o recv_udp
send_udp: send_udp.c
	$(CC) $(CFLAGS) send_udp.c wrappers.o -o send_udp
getfile: getfile.c
	$(CC) $(CFLAGS) getfile.c wrappers.o readwrite.o -o getfile
fileserver: fileserver.c
	$(CC) $(CFLAGS) fileserver.c wrappers.o readwrite.o -o fileserver
getstats: getstats.c
	$(CC) $(CFLAGS) getstats.c wrappers.o readwrite.o -o getstats



.PHONY: clean
clean:
	rm -rf $(EXECS) *.o
