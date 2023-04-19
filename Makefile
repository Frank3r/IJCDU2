CC:= gcc
FILES:= tail.c
CFLAGS:= -Wextra -Wall -O2

tail: tail.o
	$(CC) $(CFLAGS) -o tail $(FILES)
