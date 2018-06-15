/**
 * @brief A set of constants and simple utility functions.
 * 
 * @file GameUtilitiesRPS.h
 * @author Yotam Sechayk
 * @date 2018-05-10
 */
#ifndef __H_GAME_UTILITIES_RPS
#define __H_GAME_UTILITIES_RPS

#include <iostream>
#include <string>

// message output prefix
#define INFO "[INFO]"
#define ERROR "[ERROR]"

// board dimensions
#define DIM_X 10
#define DIM_Y 10

// piece representation
#define UNKNOWN_CHR '?'
#define NON_JOKER_CHR '#'
#define ROCK_CHR 'R'
#define PAPER_CHR 'P'
#define SCISSORS_CHR 'S'
#define BOMB_CHR 'B'
#define JOKER_CHR 'J'
#define FLAG_CHR 'F'

// piece limit
#define ROCK_LIMIT 2
#define PAPER_LIMIT 5
#define SCISSORS_LIMIT 1
#define BOMB_LIMIT 2
#define JOKER_LIMIT 2
#define FLAG_LIMIT 1

// player related
#define NUM_OF_PLAYERS 2
#define PLAYER_1 1
#define PLAYER_2 2
#define NO_PLAYER 0

// gameplay related
#define MAX_NUM_OF_MOVES 100
#define GAME_IS_STILL_ON -1
#define PRIME_NUMBER 179

// tournament related
#define NUM_OF_OPP 100

#endif // !__H_GAME_UTILITIES_RPS
