COMP = g++
OBJS = GameManagerRPS.o Game.cpp main.o BoardRPS.o FightInfoRPS.o PieceRPS.o ScoreManager.o TournamentManager.o
EXEC = ex3
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra \
-pedantic-errors -DNDEBUG

$(EXEC): $(OBJS) RSPPlayer_312148190.so
	$(COMP) $(OBJS) -rdynamic -ldl -pthread -o $@

RSPPlayer_312148190.so: RSPPlayer_312148190.o
	$(COMP) RSPPlayer_312148190.o -shared -o $@

############this should be handled later, not implemented yet!!##############
#AlgorithmRegistration.o: AlgorithmRegistration.cpp AlgorithmRegistration.h
#	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

Game.o: Game.cpp GameManagerRPS.h GameUtilitiesRPS.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

GameManagerRPS.o: GameManagerRPS.cpp GameManagerRPS.h \
 RSPPlayer_312148190.h GameUtilitiesRPS.h PlayerAlgorithm.h Point.h \
 PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h BoardRPS.h \
 FightInfoRPS.h PieceRPS.h PointRPS.h JokerChangeRPS.h MoveRPS.h ScoreManager.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

############this should be handled later, not implemented yet!!##############
main.o: main.cpp TournamentManager.h PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

BoardRPS.o: BoardRPS.cpp BoardRPS.h Board.h FightInfoRPS.h FightInfo.h \
 GameUtilitiesRPS.h PieceRPS.h PiecePosition.h PointRPS.h Point.h \
 JokerChangeRPS.h JokerChange.h MoveRPS.h Move.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

FightInfoRPS.o: FightInfoRPS.cpp FightInfoRPS.h FightInfo.h \
 GameUtilitiesRPS.h PieceRPS.h PiecePosition.h PointRPS.h Point.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

PieceRPS.o: PieceRPS.cpp PieceRPS.h GameUtilitiesRPS.h PiecePosition.h \
 PointRPS.h Point.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

ScoreManager.o: ScoreManager.cpp ScoreManager.h FightInfo.h JokerChange.h \
 GameUtilitiesRPS.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

############this should be handled later, not implemented yet!!##############
TournamentManager.o: TournamentManager.h TournamentManager.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

RSPPlayer_312148190.o: RSPPlayer_312148190.cpp RSPPlayer_312148190.h \
 GameUtilitiesRPS.h PlayerAlgorithm.h Point.h PiecePosition.h Board.h \
 FightInfo.h Move.h JokerChange.h PointRPS.h PieceRPS.h
	$(COMP) -fPIC $(CPP_COMP_FLAG) -c $*.cpp

.PHONY: all

all: $(EXEC)

clean:
	rm -f $(OBJS) RSPPlayer_312148190.so RSPPlayer_312148190.o $(EXEC)