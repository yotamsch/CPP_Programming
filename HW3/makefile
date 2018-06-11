# compiler, onb nova set to g++-5.3.0
COMP = g++
# object for the main tournament game
OBJS = Game.o GameManagerRPS.o BoardRPS.o FightInfoRPS.o PieceRPS.o ScoreManager.o TournamentManager.o AlgorithmRegistration.o ThreadPool.o
# the executable name, don't change
EXEC = ex3
# the shared library for the player algorithm
SO = RSPPlayer_312148190.so
# the general flags for compilation
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

# COMMANDS
# --------
# creates both shared library and tournament execuatable
all: rps_tournament rps_lib
# creates the tournament binary executable file
rps_tournament: $(EXEC)
# creates the shared library *.so file
rps_lib: $(SO)

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -rdynamic -ldl -pthread -o $@

# TODO: fix the compilation
$(SO): RSPPlayer_312148190.o PieceRPS.o
	$(COMP) $(CPP_COMP_FLAG) -shared -Wl,-soname,$@ RSPPlayer_312148190.o PieceRPS.o -o $@

# TODO: verify correctness
Game.o: Game.cpp TournamentManager.h PlayerAlgorithm.h Point.h \
 PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h ThreadPool.h \
 GameManagerRPS.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

GameManagerRPS.o: GameManagerRPS.cpp GameManagerRPS.h \
 RSPPlayer_312148190.h GameUtilitiesRPS.h PlayerAlgorithm.h Point.h \
 PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h BoardRPS.h \
 FightInfoRPS.h PieceRPS.h PointRPS.h JokerChangeRPS.h MoveRPS.h ScoreManager.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

BoardRPS.o: BoardRPS.cpp BoardRPS.h Board.h FightInfoRPS.h FightInfo.h \
 GameUtilitiesRPS.h PieceRPS.h PiecePosition.h PointRPS.h Point.h \
 JokerChangeRPS.h JokerChange.h MoveRPS.h Move.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

FightInfoRPS.o: FightInfoRPS.cpp FightInfoRPS.h FightInfo.h \
 GameUtilitiesRPS.h PieceRPS.h PiecePosition.h PointRPS.h Point.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

ScoreManager.o: ScoreManager.cpp ScoreManager.h FightInfo.h JokerChange.h \
 GameUtilitiesRPS.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

TournamentManager.o: TournamentManager.cpp TournamentManager.h \
 PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h \
 JokerChange.h ThreadPool.h GameManagerRPS.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

AlgorithmRegistration.o: AlgorithmRegistration.cpp \
 AlgorithmRegistration.h PlayerAlgorithm.h Point.h PiecePosition.h \
 Board.h FightInfo.h Move.h JokerChange.h TournamentManager.h \
 ThreadPool.h GameManagerRPS.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

ThreadPool.o: ThreadPool.cpp ThreadPool.h GameManagerRPS.h \
 PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h \
 JokerChange.h TournamentManager.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

PieceRPS.o: PieceRPS.cpp PieceRPS.h GameUtilitiesRPS.h PiecePosition.h \
 PointRPS.h Point.h
	$(COMP) $(CPP_COMP_FLAG) -fPIC -c $*.cpp

RSPPlayer_312148190.o: RSPPlayer_312148190.cpp RSPPlayer_312148190.h \
 GameUtilitiesRPS.h PlayerAlgorithm.h Point.h PiecePosition.h Board.h \
 FightInfo.h Move.h JokerChange.h JokerChangeRPS.h PointRPS.h MoveRPS.h \
 PieceRPS.h AlgorithmRegistration.h
	$(COMP) $(CPP_COMP_FLAG) -fPIC -c $*.cpp

.PHONY: all

all: $(EXEC)

clean:
	rm -f $(OBJS) RSPPlayer_312148190.so RSPPlayer_312148190.o $(EXEC)