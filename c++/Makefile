CC = g++
CFLAGS = -g -Wall -Wextra -O2 -std=c++11

TARGET = namegen

all: namegen

namegen: namegen.o example.o
	$(CC) $(CFLAGS) -o namegen namegen.o example.o

namegen.o: namegen.cc
	$(CC) $(CFLAGS) -c namegen.cc

example.o: example.cc
	$(CC) $(CFLAGS) -c example.cc

clean:
	$(RM) namegen *.o
