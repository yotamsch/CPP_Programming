#ifndef _H_BOARD
#define _H_BOARD

#include <iostream>
#include <string>
#include "piece.h"
#include "game.h"

#define MSG_ILLEGAL_MOVE "The attempted move is illegal."
#define MSG_EMPTY_DEST_PIECE "The destination has no piece."
#define MSG_ORIGIN_PIECE_LOST "The origin piece lost and was eaten."
#define MSG_DEST_PIECE_LOST "The destination piece lost and was eaten."
#define MSG_DEST_AND_ORIGIN_TIE "Both origin and destination are tied (both eaten)."
#define MSG_PIECE_ALREADY_IN_PLACE "Another piece exists in the requested place."
#define MSG_INVALID_POSITION "The requested position is invalid."

using namespace std;

class Board {
    private:
        int _n;
        int _m;
        Piece** _board = nullptr;
    public:
        // C'tor
        Board() {}
        Board(int n, int m);
        Board(const Board& b);
        // D'tor
        ~Board();
        // Get
        int GetDimentionX() { return _n; }
        int GetDimentionY() { return _m; }
        // Utility
        Board& operator=(const Board& b);
        bool IsPositionValid(int x, int y) { return (x >= 0 && x < _n) && (y >= 0 && y < _m); }
        bool IsMoveLegal(int x, int y, int new_x, int new_y, string& msg);
        bool PlacePiece(Player* owner, PieceType type, int x, int y, string& msg, bool is_joker=false);
        bool MovePiece(int x, int y, int new_x, int new_y, string& msg);
        bool ChangeJoker(int x, int y, PieceType new_type, string& msg);
        Board& Merge(const Board& b);
        void PrettyPrint();
    
    friend ostream& operator<<(ostream& output, const Board& b);
};

#endif