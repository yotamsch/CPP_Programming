COMP = g++
OBJS = Game.o GameManagerRPS.o AutoPlayerAlgorithm.o BoardRPS.o FightInfoRPS.o FilePlayerAlgorithm.o JokerChangeRPS.o MoveRPS.o PieceRPS.o PointRPS.o
# The executabel filename DON'T CHANGE
EXEC = ex2
# ----
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra \
-w -pedantic-errors -DNDEBUG
#i deleted -Werror
$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@

Game.o: Game.cpp GameManagerRPS.h
	$(COMP) $(CPP_COMP_FLAG) -c Game.cpp

GameManagerRPS.o: GameManagerRPS.cpp GameManagerRPS.h PieceRPS.h PointRPS.h FightInfoRPS.h BoardRPS.h AutoPlayerAlgorithm.h FilePlayerAlgorithm.h
	$(COMP) $(CPP_COMP_FLAG) -c GameManagerRPS.cpp

AutoPlayerAlgorithm.o: AutoPlayerAlgorithm.cpp AutoPlayerAlgorithm.h
	$(COMP) $(CPP_COMP_FLAG) -c AutoPlayerAlgorithm.cpp

BoardRPS.o: BoardRPS.cpp BoardRPS.h
	$(COMP) $(CPP_COMP_FLAG) -c BoardRPS.cpp

FightInfoRPS.o: FightInfoRPS.cpp FightInfoRPS.h
	$(COMP) $(CPP_COMP_FLAG) -c FightInfoRPS.cpp

FilePlayerAlgorithm.o: FilePlayerAlgorithm.cpp FilePlayerAlgorithm.h
	$(COMP) $(CPP_COMP_FLAG) -c FilePlayerAlgorithm.cpp

JokerChangeRPS.o: JokerChangeRPS.cpp JokerChangeRPS.h
	$(COMP) $(CPP_COMP_FLAG) -c JokerChangeRPS.cpp

MoveRPS.o: MoveRPS.cpp MoveRPS.h
	$(COMP) $(CPP_COMP_FLAG) -c MoveRPS.cpp

PieceRPS.o: PieceRPS.cpp PieceRPS.h
	$(COMP) $(CPP_COMP_FLAG) -c PieceRPS.cpp

PointRPS.o: PointRPS.cpp PointRPS.h
	$(COMP) $(CPP_COMP_FLAG) -c PointRPS.cpp

clean:
	rm -f $(OBJS) $(EXEC)