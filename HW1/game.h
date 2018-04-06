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


/**
 * @brief An enum representing the player type (player 1 or player 2)
 * 
 */
enum class PlayerType {PLAYER_1=1, PLAYER_2};

/**
 * @brief An enum representing the different types of play pieces
 * 
 */
enum class PieceType {NONE=-1, ROCK=0, PAPER, SCISSORS, FLAG, BOMB, JOKER};


#endif