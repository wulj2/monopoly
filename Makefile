CC=g++
CPPFLAGS=-std=c++11 -g -Wall -O3

all: mp

mp:
	$(CC) $(CPPFLAGS) -o mp board.cpp dice.cpp monopoly.cpp

.PHONY:all clean cleanlocal

cleanlocal:
	rm -rf mp mp.dSYM

clean:cleanlocal
