.POSIX:
CC      = cc
CFLAGS  = -Wall -Wextra -O --std=c99
LDFLAGS = -O
LDLIBS  = -lm

all: hashtable

debug: CFLAGS += -DDEBUG
debug: hashtable

hashtable: main.c hashtable.o prime.o hash.o
	$(CC) $(CFLAGS) -o hashtable main.c hashtable.o prime.o hash.o $(LDLIBS)

hashtable.o: hashtable.c hashtable.h prime.h hash.h debug.h

prime.o: prime.c prime.h

hash.o: hash.c hash.h prime.h debug.h

clean:
	rm -f hashtable *.o *.h.gch

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $<
