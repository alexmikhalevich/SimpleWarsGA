CC=g++
CFLAGS=-c -std=c++11 -Wall -g
LFLAGS=-lSDL2

all: main.o cview.o
	$(CC) $(LFLAGS) cview.o main.o -o game
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
cview.o: cview.cpp
	$(CC) $(CFLAGS) cview.cpp
clean: 
	rm *.o game

