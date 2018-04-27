
#ifndef __H_PIECE_RPS
#define __H_PIECE_RPS

#include "PiecePosition.h"

class PieceRPS : public PiecePosition {
private:
public:
    // D'tor
    ~PieceRPS();
    // Other
    const Point& getPosition() const;
    char getPiece() const;
    char getJokerRep() const;
};

#endif // !__H_PIECE_RPS