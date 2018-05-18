#ifndef __H_PIECE_RPS
#define __H_PIECE_RPS

#include "GameUtilitiesRPS.h"
#include "PiecePosition.h"
#include "PointRPS.h"
#include <iostream>

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
    // get the player [currently enum]
    int getPlayer() const { return this->_player; }

    // setters

    /**
     * @brief called ONLY when setting a joker's representation. Changes/Sets the calling joker's type(char representation)
     * 
     * @param type - the desired representation of a joker
     */
    void setType(char type);

    // utility
    bool isJoker() { return _is_joker; }
    // overloading the copy assignment operator '='
    PieceRPS& operator=(const PieceRPS& p);
    // no need for equivalance operator
    // TODO: maybe implement anyway
    bool operator==(const PieceRPS& p) const = delete;
    bool operator>(const PieceRPS& p) const = delete;
    bool operator<(const PieceRPS& p) const;

    // interface defined functions

    //Gets the current position of this piece
    const Point& getPosition() const;
    // gets the char representation of this piece
    char getPiece() const;
    //if this piece is a joker, gets its char representation(R, P, S or B). otherwise returns '#'
    char getJokerRep() const;

public:
    // overloading the '<<' operator for printing piece
    friend std::ostream& operator<<(std::ostream& output, const PieceRPS& piece);
};

#endif // !__H_PIECE_RPS
