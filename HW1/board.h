#ifndef _H_BOARD
#define _H_BOARD

#include <iostream>
#include <string>
#include "piece.h"
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
        Board& operator+(const Board& b);
        Board& operator=(const Board& b);
        bool IsPositionValid(int x, int y) { return (x <= _n) && (y <= _m); }
        bool IsMoveLegal(int x, int y, int new_x, int new_y, string& msg);
        bool PlacePiece(Player* owner, PlayerType player, PieceType type, int x, int y, string& msg, bool is_joker=false);
        void MovePiece(int x, int y, int new_x, int new_y, string& msg);
        void PrettyPrint();
    
    friend ostream& operator<<(ostream& output, const Board& b);
};

#endif