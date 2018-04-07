#ifndef _H_GAME
#define _H_GAME

// How many pieces of each kind
#define R 2
#define P 5
#define S 1
#define B 2
#define J 2
#define F 1

#define DEBUG 1

// Output messages
#define RSN_ALL_FLAGS_CAPTURED "All flags of the opponent are captured"
#define RSN_ALL_PIECES_EATEN "All moving PIECEs of the opponent are eaten"
#define RSN_MOVE_FILES_NO_WINNER "A tie - both Moves input files done without a winner"
#define RSN_POSITION_NO_FLAGS "A tie - all flags are eaten by both players in the position files"
#define RSN_POSITION_NO_PIECES "A tie - all moving PIECEs of both players are eaten in the position files"
#define RSN_BAD_POSISION_FILE_SINGLE "Bad Positioning input file for "
#define RSN_BAD_POSITION_FILE_DOUBLE "Bad Positioning input file for both players - "
#define RSN_BAD_MOVE_FILE_SINGLE "Bad Moves input file for "
//player %d - line %d
//player 1: line %d, player 2: line %d

/**
 * @brief An enum representing the player type (player 1 or player 2)
 * 
 */
enum class PlayerType {NONE=-1, PLAYER_1=1, PLAYER_2};

/**
 * @brief An enum representing the different types of play pieces
 * 
 */
enum class PieceType {NONE=-1, ROCK=0, PAPER, SCISSORS, FLAG, BOMB, JOKER};

/**
 * @brief An enum representing the returned reason of gameplay functions
 * 
 */
enum class Reason {UNKNOWN_ERROR=-1, SUCCESS=0, FILE_ERROR, LINE_ERROR, NO_FLAGS, NO_PIECES};


#endif