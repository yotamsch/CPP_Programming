/**
 * @brief A set of constants and simple utility functions.
 * 
 * @file GameUtilitiesRPS.h
 * @author Yotam Sechayk
 * @date 2018-05-05
 */
#ifndef __H_GAME_UTILITIES_RPS
#define __H_GAME_UTILITIES_RPS

#include <iostream>
#include <string>

// game-play options
#define AUTO_VS_AUTO 1
#define FILE_VS_FILE 2
#define AUTO_VS_FILE 3
#define FILE_VS_AUTO 4

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

// possible output messages
// TODO re-think possible messages
#define BAD_ARGS_MESSAGE "Please enter (as the first argument): auto-vs-auto, file-vs-file, auto-vs-file or file-vs-auto and try again."
#define RSN_ALL_FLAGS_CAPTURED "All flags of the opponent are captured"
#define RSN_ALL_PIECES_EATEN "All moving PIECEs of the opponent are eaten"
#define RSN_MOVE_FILES_NO_WINNER "A tie - both Moves input files done without a winner"
#define RSN_POSITION_NO_FLAGS "A tie - all flags are eaten by both players in the position files"
#define RSN_POSITION_NO_PIECES "A tie - all moving PIECEs of both players are eaten"
#define RSN_BAD_POSISION_FILE_SINGLE "Bad positioning input for opponent"
#define RSN_BAD_POSITION_FILE_DOUBLE "Bad positioning input for both players"
#define RSN_BAD_MOVE_FILE_SINGLE "Bad move input for opponent"

// player related
#define NUM_OF_PLAYERS 2
#define PLAYER_1 1
#define PLAYER_2 2
#define NO_PLAYER 0

// gameplay related
#define MAX_NUM_OF_MOVES 100
#define GAME_IS_STILL_ON -1
#define PRIME_NUMBER 179

/**
 * @brief An enum representing the returned reason of gameplay functions
 * 
 */
// TODO concider replacing
enum class Reason {
    BAD_MOVE_ERROR,
    POSITION_FILE_ERROR
};

#endif // !__H_GAME_UTILITIES_RPS
