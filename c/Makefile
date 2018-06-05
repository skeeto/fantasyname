.POSIX:
CC      = cc
CFLAGS  = -ansi -pedantic -Wall -Wextra -O3 -g3 -fpie
LDFLAGS = -pie

namegen: example.c namegen.h
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ example.c $(LDLIBS)

test: check
check: namegen
	@./namegen --test

clean:
	rm -f namegen
