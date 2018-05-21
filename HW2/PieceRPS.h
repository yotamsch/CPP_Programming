#ifndef __H_PIECE_RPS
#define __H_PIECE_RPS

#include "GameUtilitiesRPS.h"
#include "PiecePosition.h"
#include "PointRPS.h"
#include <iostream>
/**
 * @brief A class inheriting from the abstract class PiecePosition, 
 * responsible for the creation of game pieces,
 * each piece consisting of 1. its owner 2. a boolean to tell if it's a joker
 * 3. its char representation 4.its location on the board 
 * 
 */
class PieceRPS : public PiecePosition {
private:
    int _player; // the id of the owning player
    bool _is_joker; // true iff this is a joker piece
    char _piece_type; // the piece char or joker representation
    PointRPS _position; // the location of the piece

public:
    // basic c'tors
    PieceRPS(int player, bool is_joker, char type, const PointRPS& position)
        : _player(player) // 1 : player 1 | 2 : player 2
        , _is_joker(is_joker) // true iff this is joker piece
        , _piece_type(type) // the type R, P, S, B, F (no J)
        , _position(position) // the point (x,y)
    {
    }
    // copy c'tor
    PieceRPS(const PieceRPS& other) { *this = other; }
    // no need for move constructor
    PieceRPS(PieceRPS&& other) = delete;

    // d'tor
    ~PieceRPS() {}

    // getters
    // get the player owner of the piece
    int getPlayer() const { return this->_player; }

    // setters

    /**
     * @brief called ONLY when setting a joker's representation. Changes/Sets the calling joker's type(char representation)
     * 
     * @param type - the desired representation of a joker
     */
    void setType(char type);

    // utility
    //Tells if current piece is a joker
    bool isJoker() { return _is_joker; }
    // overloading the copy assignment operator '='
    PieceRPS& operator=(const PieceRPS& p);
    // no need for equivalance operator
    // TODO: maybe implement anyway
    bool operator==(const PieceRPS& p) const = delete;
    //no need to implement because it's enough to overload the > operator
    bool operator>(const PieceRPS& p) const = delete;
    
    /**
     * @brief Overloading on the lower than (<) operator. According to the rules of the game. Returns true only if the left side is lower "in strength" than the right side.
     * 
     * @param p The right hand side to compare to.
     * @return true If the left side is lower "in strength" than the right side
     * @return false Otherwise
     */
    bool operator<(const PieceRPS& p) const;

    // interface defined functions

    //Gets the current position of this piece
    const Point& getPosition() const;
    // gets the char representation of this piece
    char getPiece() const;
    //if this piece is a joker, gets its char representation(R, P, S or B). otherwise returns '#'
    char getJokerRep() const;

public:

/**
 * @brief Overloading on the print to ostream (<<) operator.
 * 
 * @param output The ostream to output into
 * @param piece The play piece to print
 * @return ostream& The modified ostream
 */
    friend std::ostream& operator<<(std::ostream& output, const PieceRPS& piece);
};

#endif // !__H_PIECE_RPS
