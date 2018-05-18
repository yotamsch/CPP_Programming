
#ifndef __H_FIGHT_INFO_RPS
#define __H_FIGHT_INFO_RPS

#include "FightInfo.h"
#include "GameUtilitiesRPS.h"
#include "PieceRPS.h"
#include "PointRPS.h"
#include <array>

/**
 * @brief a class inheriting from FightInfo. handles a fight between two players in a specific position on board
 * member fields:
 *  _position - the position where the fight happens
 *  _pieceChar - array containing the pieces that participated in the fight, indexed by (symbol of owner-1)
 *  _winner - holds the number of the winner of the fight 
 */
class FightInfoRPS : public FightInfo {
private:
    PointRPS _position; // the fight position (x,y)
    std::array<char, NUM_OF_PLAYERS> _pieceChar; //array  [0] : player 1 | [1] : player 2 ...
    int _winner; // the winner of the fight

public:
    /**
     * @brief Construct a new FightInfoRPS object
     * assumes that (rPieceA->position == rPieceB->position)
     * gets the right values from both pieces and decides on the winner
     * @param rPieceA - the first piece that participates in the fight
     * @param rPieceB - the second piece that participates in the fight
     * @param rPos - the position where the fight happens
     */
    FightInfoRPS(PieceRPS& rPieceA, PieceRPS& rPieceB, PointRPS&& rPos);

    // d'tor
    ~FightInfoRPS() {}

    // interface defined functions
    // get the position of the fight
    const Point& getPosition() const;

    /**
     * @brief given a player, return the char representation of the player's piece that was involved in current fight
     * 
     * @param player - the owner
     * @return char - char representation of the player's piece that was involved in current fight
     *              could be R, P, S, B or F (but NOT J)
     */
    char getPiece(int player) const;

    /**
     * @brief Get the Winner of the fight
     * 
     * @return int - 1 if player 1 won, 2 if player 2 won, 0 if the fight results in a tie
     */
    int getWinner() const;

private:

    /**
     * @brief Get the char representation of the Piece object
     * 
     * @param p - reference to PieceRPS object
     * @return char - char representation of p
     */
    char getActualPiece (PieceRPS& p);
};

#endif // !__H_FIGHT_INFO_RPS