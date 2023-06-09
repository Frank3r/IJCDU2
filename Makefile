#
#	Frantisek Sedlacek
#	VUT FIT Brno
#	Priklad: IJC-DU2
#	19.04. 2023
#



CC:= gcc
CFLAGS:= -Wextra -Wall -O2 -pedantic
# CFLAGS+= -fsanitize=address

all:tail wordcount wordcount-dynamic

tail: tail.c
	$(CC) $(CFLAGS) -o tail $<

wordcount: wordcount.o libhtab.a
	$(CC) $(CFLAGS) -o wordcount $+

wordcount-dynamic: libhtab.so wordcount.o
	$(CC) $(CFLAGS) -o wordcount-dynamic $+ -L./ -lhtab

libhtab_sources := $(wildcard htab_*.c)
libhtab_objs:= $(libhtab_sources:.c=.o)
libhtab.a: $(libhtab_objs)
	ar -rcs $@ $+

libhtab.so: $(libhtab_objs)
	$(CC) $(CFLAGS) -shared -o $@ $+

%.o: %.c
	$(CC) $(CFLAGS) -c -g -o $@ -fPIC $<

clean:
	rm $(wildcard *.o) libhtab.so libhtab.a tail wordcount wordcount-dynamic

