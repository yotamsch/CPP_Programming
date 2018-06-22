# compiler, onb nova set to g++-5.3.0
COMP = g++
# object for the main tournament game
OBJS = main.o
# the executable name, don't change
EXEC = ex4
# the general flags for compilation
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG -g

# COMMANDS
# --------

default: $(EXEC)

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@

main.o: main.cpp ex4_header.h GameBoard.h unit_test_util.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
	