COMP = g++
OBJS = game.o file.o board.o piece.o player.o
# The executabel filename DON'T CHANGE
EXEC = ex1
# ----
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@

game.o: game.cpp board.h piece.h game.h player.h file.h
	$(COMP) $(CPP_COMP_FLAG) -c game.cpp

file.o: file.cpp file.h board.h piece.h game.h player.h
	$(COMP) $(CPP_COMP_FLAG) -c file.cpp

board.o: board.cpp board.h piece.h game.h player.h
	$(COMP) $(CPP_COMP_FLAG) -c board.cpp

piece.o: piece.cpp piece.h game.h player.h
	$(COMP) $(CPP_COMP_FLAG) -c piece.cpp

player.o: player.cpp player.h game.h
	$(COMP) $(CPP_COMP_FLAG) -c player.cpp

clean:
	rm -f $(OBJS) $(EXEC)
