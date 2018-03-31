#ifndef _H_BOARD
#define _H_BOARD

#include <iostream>
#include "pieces.h"

using namespace std;

class Board {
    private:
        Piece** _board;
        int _n;
        int _m;
    public:
        Board(int n, int m) : _n(n), _m(m) { _board = new Pieces[n][m]; }
        ~Board() { delete[]  _board; }
        Piece* operator[](int index) { return _board[index]; }
        bool isPositionValid(int x, int, y) { return (x <= _n) && (y <= _m); }
        bool placePiece(int type, int x, int y, bool is_joker=false);
    /* TODO: maybe add more functions */
}

#endif