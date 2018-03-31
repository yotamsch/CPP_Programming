CPP=g++
CPPFLAGS=-c

all: game.o board.o pieces.o
	$(CPP) game.o board.o pieces.o -o game

game.o: game.cpp
	$(CPP) $(CPPFLAGS) game.cpp

board.o: board.cpp
	$(CPP) $(CPPFLAGS) board.cpp -I.

pieces.o: pieces.cpp
	$(CPP) $(CPPFLAGS) pieces.cpp -I.

clean:
	rm -rf *.o game