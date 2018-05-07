#ifndef __H_PIECE_RPS
#define __H_PIECE_RPS

#include "GameUtilitiesRPS.h"
#include "PiecePosition.h"
#include "PointRPS.h"
#include <iostream>

class PieceRPS : public PiecePosition {
private:
    int _player;
    bool _is_joker;
    PieceType _piece_type;
    PointRPS _position;

public:
    // basic c'tors
    PieceRPS(int player, bool is_joker, PieceType type, const PointRPS& position)
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
    // TODO: maybe change to 'int _player'
    int getPlayer() const { return this->_player; }
    // get the piece type [currently enum]
    PieceType getPieceType() const { return _piece_type; }

    // setters
    // set the type for joker pieces
    void setType(PieceType type);

    // utility
    bool isJoker() { return _is_joker; }
    // overloading the copy assignment operator '='
    PieceRPS& operator=(const PieceRPS& p);
    // no need for equivalance operator
    // TODO: maybe implement anyway
    bool operator==(const PieceRPS& p) const = delete;
    bool operator>(const PieceRPS& p) const;
    bool operator<(const PieceRPS& p) const;

    // interface defined functions
    const Point& getPosition() const;
    char getPiece() const;
    char getJokerRep() const;

public:
    // overloading the '<<' operator for printing piece
    friend std::ostream& operator<<(std::ostream& output, const PieceRPS& piece);
};

#endif // !__H_PIECE_RPS
