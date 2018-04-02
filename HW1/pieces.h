#ifndef _H_PIECES
#define _H_PIECES

#include "game.h"
#include <iostream>
#include <ctype.h>

using namespace std;

char PieceTypeToChar(PieceType type);

class Piece {
    private:
        int _index_x;
        int _index_y;
        PlayerType _player_type;
        PieceType _piece_type;
        bool _is_joker;
    public:
        // C'tors
        Piece() : _piece_type(PieceType::NONE) {}
        Piece(int x, int y, PlayerType player_id, PieceType type, bool is_joker): _index_x(x), _index_y(y), _player_type(player_id), _piece_type(type), _is_joker(is_joker) {}
        // D'tor
        virtual ~Piece() {}
        // Get
        int GetX() const { return _index_x; }
        int GetY() const { return _index_y; }
        PieceType GetPieceType() const { return _piece_type; }
        PlayerType GetPlayerType() const { return _player_type; }
        // Set
        void SetX(int x) { _index_x = x; }
        void SetY(int y) { _index_y = y; }
        void SetPosition(int new_x, int new_y) { SetX(new_x); SetY(new_y); }
        bool SetType(PieceType type) { if (_is_joker) { _piece_type = type; return true; } return false; }
        // Utility
        bool IsJoker() { return _is_joker; }
        bool IsInitiated() { return _piece_type != PieceType::NONE ? true : false; }
        bool operator<(const Piece& p);
        bool operator==(const Piece& p) { if ( this->GetPieceType() == p.GetPieceType()) return true; return false; }
        bool operator>(const Piece& p) { if ((*this) < p || (*this) == p) return false; return true; }
        void ClearPiece();
        
    friend ostream& operator<<(ostream& output, const Piece& piece);
};

#endif

