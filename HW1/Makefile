CPP=g++
CPPFLAGS=-c -std=c++11

all: game.o board.o piece.o player.o
	$(CPP) game.o board.o piece.o player.o -o game

game.o: game.cpp
	$(CPP) $(CPPFLAGS) game.cpp -I.

board.o: board.cpp
	$(CPP) $(CPPFLAGS) board.cpp -I.

pieces.o: pieces.cpp
	$(CPP) $(CPPFLAGS) piece.cpp -I.

player.o: player.cpp
	$(CPP) $(CPPFLAGS) player.cpp -I.

clean:
	rm -rf *.o game