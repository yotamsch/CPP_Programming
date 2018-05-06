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
    // vopy c'tor
    PieceRPS(const PieceRPS& p) { *this = p; }
    // * PieceRPS() : _is_joker(false), _piece_type(PieceType::NONE), _player(-1),

    // d'tor
    ~PieceRPS() {}

    // getters
    int getPlayer() const { return this->_player; }
    PieceType getPieceType() const { return _piece_type; }

    // setters
    void setType(PieceType type);

    // utility
    bool isJoker() { return _is_joker; }
    PieceRPS& operator=(const PieceRPS& p);
    bool operator==(const PieceRPS& p) const = delete;
    bool operator>(const PieceRPS& p) const;
    bool operator<(const PieceRPS& p) const;
    // * bool operator==(const PieceRPS& p) const;
    // * bool isInitiated() { return _piece_type != PieceType::NONE ? true : false;
    // * void NullifyPiece();
    // * void RemovePieceFromPlayer();

    // interface defined functions
    const Point& getPosition() const;
    char getPiece() const;
    char getJokerRep() const;

    friend std::ostream& operator<<(std::ostream& output, const PieceRPS& piece);
};

#endif // !__H_PIECE_RPS
