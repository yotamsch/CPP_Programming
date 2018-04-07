#COMP = g++-5.3.0
COMP = g++
#put all your object files here
OBJS = game.o file.o board.o piece.o player.o
#The executabel filename DON'T CHANGE
EXEC = ex1
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@

game.o: game.cpp board.h piece.h game.h player.h file.h
	$(COMP) $(CPP_COMP_FLAG) -c -g game.cpp

file.o: file.cpp file.h board.h piece.h game.h player.h
	$(COMP) $(CPP_COMP_FLAG) -c -g file.cpp

board.o: board.cpp board.h piece.h game.h player.h
	$(COMP) $(CPP_COMP_FLAG) -c -g board.cpp

piece.o: piece.cpp piece.h game.h player.h
	$(COMP) $(CPP_COMP_FLAG) -c -g piece.cpp

player.o: player.cpp player.h game.h
	$(COMP) $(CPP_COMP_FLAG) -c -g player.cpp

clean:
	rm -f $(OBJS) $(EXEC)
