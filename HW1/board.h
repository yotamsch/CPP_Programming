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
        // C'tors D'tors
        Board() : _m(0), _n(0) {}
        Board(int n, int m);
        ~Board();
        // Getters
        int getDimentionX() { return _n; }
        int getDimentionY() { return _m; }
        // Setters

        // Etc.
        Piece* operator[](int index) { return _board[index]; }
        
        bool isPositionValid(int x, int y) { return (x <= _n) && (y <= _m); }
        bool placePiece(int type, int x, int y, bool is_joker=false);
        // TODO: maybe add more functions
};

#endif