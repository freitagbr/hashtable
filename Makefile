.POSIX:
CC      = cc
CFLAGS  = -Wall -O
LDFLAGS = -O
LDLIBS  = -lm

all: hashtable

debug: CFLAGS += -DDEBUG
debug: hashtable

hashtable: main.c hashtable.o primes.o hash.o
	$(CC) $(LDFLAGS) -o hashtable main.c hashtable.o primes.o hash.o $(LDLIBS)

hashtable.o: hashtable.c hashtable.h primes.h hash.h debug.h

primes.o: primes.c primes.h

hash.o: hash.c hash.h primes.h debug.h

clean:
	rm -f hashtable *.o *.h.gch

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $<
