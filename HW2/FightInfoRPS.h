/**
 * @brief The header of the FightInfoRPS class.
 * 
 * @file FightInfoRPS.h
 * @author Yotam Sechayk
 * @date 2018-05-06
 */
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
    // basic c'tor
    FightInfoRPS(PieceRPS& rPieceA, PieceRPS& rPieceB, PointRPS&& rPos);

    // d'tor
    ~FightInfoRPS() {}

    // interface defined functions
    // get the position of the fight
    const Point& getPosition() const { return _position; }
    // given a player, return the char representation of the player's piece that was involved in current fight. could be R, P, S, B or F (but NOT J)
    char getPiece(int player) const { return this->_pieceChar[player - 1]; }
    // get the Winner of the fight. 1 if player 1 won, 2 if player 2 won, 0 if the fight results in a tie
    int getWinner() const { return _winner; }

private:
    // gets the actual representation of the piece
    char getActualPiece(PieceRPS& p);
};

#endif // !__H_FIGHT_INFO_RPS