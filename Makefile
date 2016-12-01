CC=g++
CFLAGS=-c -std=c++11 -Wall -g
LFLAGS=-lSDL2

all:
	$(CC) $(CFLAGS) $(LFLAGS) view.o main.o -o game
main.o: main.cpp
	$(CC) $(CFLAGS) $(LFLAGS) main.cpp
view.o: cview.cpp
	$(CC) $(CFLAGS) $(LFLAGS) cview.cpp
clean: 
	rm *.o game

