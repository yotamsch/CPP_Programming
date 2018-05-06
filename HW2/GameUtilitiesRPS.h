/**
 * @brief A set of constants and simple utility functions.
 * 
 * @file GameUtilitiesRPS.h
 * @author Yotam Sechayk
 * @date 2018-05-05
 */
#ifndef __H_GAME_UTILITIES_RPS
#define __H_GAME_UTILITIES_RPS

#include <string>

// game-play options
#define AUTO_VS_AUTO 1
#define FILE_VS_FILE 2
#define AUTO_VS_FILE 3
#define FILE_VS_AUTO 4

// message output prefix
#define INFO "[INFO]"
#define ERROR "[ERROR]"

// Board dimensions
#define DIM_X 10
#define DIM_Y 10

// How many pieces of each kind
#define ROCK_LIMIT 2
#define PAPAER_LIMIT 5
#define SCISSORS_LIMIT 1
#define BOMB_LIMIT 2
#define JOKER_LIMIT 2
#define FLAG_LIMIT 1

// possibleoutput messages
#define BAD_ARGS_MESSAGE "Please enter (as the first argument): auto-vs-auto, file-vs-file, auto-vs-file or file-vs-auto and try again."
#define RSN_ALL_FLAGS_CAPTURED "All flags of the opponent are captured"
#define RSN_ALL_PIECES_EATEN "All moving PIECEs of the opponent are eaten"
#define RSN_MOVE_FILES_NO_WINNER "A tie - both Moves input files done without a winner"
#define RSN_POSITION_NO_FLAGS "A tie - all flags are eaten by both players in the position files"
#define RSN_POSITION_NO_PIECES "A tie - all moving PIECEs of both players are eaten"
#define RSN_BAD_POSISION_FILE_SINGLE "Bad Positioning input file for "
#define RSN_BAD_POSITION_FILE_DOUBLE "Bad Positioning input file for both players - "
#define RSN_BAD_MOVE_FILE_SINGLE "Bad Moves input file for "
// Additions made in the game itself:
// 1) player %d - line %d
// 2) player 1: line %d, player 2: line %d

// things from GameManagerRPS.h
// ? maybe some not needed
#define NO_WINNER 0
#define MAX_NUM_OF_MOVES 100
#define NON_JOKER_FLAG '#'

/**
 * @brief An enum representing the player type (player 1 or player 2).
 * 
 */
enum class PlayerType
{
    NONE = 0,
    PLAYER_1 = 1,
    PLAYER_2 = 2
};

/**
 * @brief An enum representing the different types of play pieces.
 * 
 */
enum class PieceType
{
    UNKNOWN = -1,
    NONE = 0,
    ROCK = 1,
    PAPER,
    SCISSORS,
    FLAG,
    BOMB,
    JOKER
};

/**
 * @brief Inline function. Prints a message to the screen with the desired label type.
 * 
 * @param type A string representing the type (i.e. INFO, ERROR, ...).
 * @param msg The message to be printed alongside the label.
 */
void printMessageToScreen(const std::string &&rType, const std::string &&rMsg);

/**
 * @brief Get a random position on the board by the boarrd dimensions.
 * 
 * @return int Position = Row * Y-Dimension + Column.
 */
int getRandomPositionOnBoard();

int getXDimensionParameter(int vPos);

int getYDimensionParameter(int vPos);

int getCombinedPosition(int vX, int vY);

/**
 * @brief Converts the recieved type to a representing char
 * 
 * @param type The type to convert (e.g. ROCK, PAPER...)
 * @return char The representing character
 */
char PieceTypeToChar(PieceType type);

PieceType CharToPieceType(char chr);

PieceType getRandomJokerPieceType();

#endif // !__H_GAME_UTILITIES_RPS
