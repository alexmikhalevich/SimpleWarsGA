CC=g++
CFLAGS=-c -std=c++11 -Wall -g
LFLAGS=-lSDL2

all: main.o cview.o cfield.o representation.o clogic.o
	$(CC) $(LFLAGS) cview.o cfield.o main.o representation.o clogic.o -o game
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
cview.o: cview.cpp
	$(CC) $(CFLAGS) cview.cpp
cfield.o: cfield.cpp
	$(CC) $(CFLAGS) cfield.cpp
representation.o: representation.hpp
	$(CC) $(CFLAGS) representation.hpp
clogic.o: clogic.cpp
	$(CC) $(CFLAGS) clogic.cpp
clean: 
	rm *.o game

