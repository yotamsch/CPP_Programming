COMP = g++
OBJS = Game.o GameManagerRPS.o AutoPlayerAlgorithm.o BoardRPS.o FightInfoRPS.o FilePlayerAlgorithm.o PieceRPS.o ScoreManager.o
# The executabel filename DON'T CHANGE
EXEC = ex2
# ----
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra \
-w -pedantic-errors -DNDEBUG -g
#i deleted -Werror
$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@

# the app's main function
Game.o: Game.cpp GameManagerRPS.h GameUtilitiesRPS.h
	$(COMP) $(CPP_COMP_FLAG) -c Game.cpp

# the RPS game manager
GameManagerRPS.o: GameManagerRPS.cpp GameManagerRPS.h \
 AutoPlayerAlgorithm.h GameUtilitiesRPS.h PlayerAlgorithm.h Point.h \
 PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h BoardRPS.h \
 FightInfoRPS.h PieceRPS.h PointRPS.h JokerChangeRPS.h MoveRPS.h \
 FilePlayerAlgorithm.h ScoreManager.h
	$(COMP) $(CPP_COMP_FLAG) -c GameManagerRPS.cpp

# the score manager of the game
ScoreManager.o: ScoreManager.cpp ScoreManager.h FightInfo.h JokerChange.h \
 GameUtilitiesRPS.h
	$(COMP) $(CPP_COMP_FLAG) -c ScoreManager.cpp

# the automatic player algorithm
AutoPlayerAlgorithm.o: AutoPlayerAlgorithm.cpp AutoPlayerAlgorithm.h \
 GameUtilitiesRPS.h PlayerAlgorithm.h Point.h PiecePosition.h Board.h \
 FightInfo.h Move.h JokerChange.h PointRPS.h PieceRPS.h
	$(COMP) $(CPP_COMP_FLAG) -c AutoPlayerAlgorithm.cpp

# the file player algorithm
FilePlayerAlgorithm.o: FilePlayerAlgorithm.cpp FilePlayerAlgorithm.h \
 PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h \
 JokerChange.h GameManagerRPS.h GameUtilitiesRPS.h MoveRPS.h PointRPS.h \
 JokerChangeRPS.h PieceRPS.h
	$(COMP) $(CPP_COMP_FLAG) -c FilePlayerAlgorithm.cpp

# the board implementation
BoardRPS.o: BoardRPS.cpp BoardRPS.h Board.h FightInfoRPS.h FightInfo.h \
 GameUtilitiesRPS.h PieceRPS.h PiecePosition.h PointRPS.h Point.h \
 JokerChangeRPS.h JokerChange.h MoveRPS.h Move.h
	$(COMP) $(CPP_COMP_FLAG) -c BoardRPS.cpp

# the fight info implementation
FightInfoRPS.o: FightInfoRPS.cpp FightInfoRPS.h FightInfo.h \
 GameUtilitiesRPS.h PieceRPS.h PiecePosition.h PointRPS.h Point.h
	$(COMP) $(CPP_COMP_FLAG) -c FightInfoRPS.cpp

# the piece implementation
PieceRPS.o: PieceRPS.cpp PieceRPS.h GameUtilitiesRPS.h PiecePosition.h \
 PointRPS.h Point.h
	$(COMP) $(CPP_COMP_FLAG) -c PieceRPS.cpp

clean:
	rm -f $(OBJS) $(EXEC)