CC   = gcc
CFLAGS = -g 
LFLAGS = -lpthread
ALL  = wrappers gshell print

all : $(ALL)

wrappers: wrappers.c
	$(CC) -c $(CFLAGS) $(LFLAGS) wrappers.c -c 

print: print.c
	$(CC) -c $(CFLAGS) $(LFLAGS) print.c -c

gshell:	gshell.c wrappers.o print.o
	$(CC) $(LFLAGS) gshell.c -lreadline -o gshell print.o wrappers.o

clean:
	/rm -f *.o *~ core $(ALL)
