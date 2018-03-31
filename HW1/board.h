#ifndef _H_BOARD
#define _H_BOARD

#include <iostream>
#include <string>
#include "pieces.h"

using namespace std;

class Board {
    private:
        int _n;
        int _m;
        Piece** _board = nullptr;
    public:
        // C'tor
        Board(int n, int m);
        Board(const Board& b);
        // D'tor
        ~Board();
        // Get
        int getDimentionX() { return _n; }
        int getDimentionY() { return _m; }
        // Utility
        Piece* operator[](int index) { return _board[index]; }
        Board& operator+(const Board& b);
        Board& operator=(const Board& b);
        bool isPositionValid(int x, int y) { return (x <= _n) && (y <= _m); }
        bool placePiece(int player, int type, int x, int y, string& msg, bool is_joker=false);
        bool movePiece(int x, int y, int new_x, int new_y, string& msg);
        void prettyPrint();
};

#endif