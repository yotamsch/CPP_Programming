#ifndef _H_BOARD
#define _H_BOARD

#include <iostream>
#include <string>
#include "pieces.h"
#include "game.h"

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
        int GetDimentionX() { return _n; }
        int GetDimentionY() { return _m; }
        // Utility
        Piece* operator[](int index) { return _board[index]; }
        Board& operator+(const Board& b);
        Board& operator=(const Board& b);
        bool IsPositionValid(int x, int y) { return (x <= _n) && (y <= _m); }
        bool PlacePiece(PlayerType player, PieceType type, int x, int y, string& msg, bool is_joker=false);
        bool MovePiece(int x, int y, int new_x, int new_y, string& msg);
        void PrettyPrint();
};

#endif