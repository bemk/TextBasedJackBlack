CXX:=g++
CC:=clang

CFLAGS=-std=c11
CXXFLAGS=-L/usr/local/lib/ -lwiringPi -lwiringPiDev -lm -lpthread

.PHONY: all clean
all: TextBasedBlackJack

clean: =
	rm -fv *.o
	rm -fv TextBasedBlackJack

TextBasedBlackJack: src/Card.o src/TextBasedBlackJack.o
	g++ -o TextBasedJackBlack src/*.o -L/usr/local/lib/ -lwiringPi -lwiringPiDev -lm -lpthread


src/Card.o: src/Card.cpp

src/TextBasedBlackJack.o: src/TextBasedBlackJack.cpp
