#ifndef _H_PIECES
#define _H_PIECES

#include "game.h"
#include "player.h"
#include <iostream>
#include <ctype.h>

using namespace std;

class Piece {
    private:
        bool _is_joker;
        PieceType _piece_type;
        Player* _owner;
        PlayerType _player_type;
        static int _piece_counter;
    public:
        // C'tors
        Piece() : _piece_type(PieceType::NONE) { ++_piece_counter; }
        Piece(PlayerType player, PieceType type, bool is_joker, Player* owner): _player_type(player), _piece_type(type), _is_joker(is_joker), _owner(owner) { ++_piece_counter; _owner->IncrementPieceCount(_piece_type); }
        Piece(const Piece& p) { *this = p; }
        // D'tor
        ~Piece() { --_piece_counter; }
        // Get
        PieceType GetPieceType() const { return _piece_type; }
        PlayerType GetPlayerType() const { return _player_type; }
        static int GetPieceCounter() {return _piece_counter; }
        // Set
        bool SetType(PieceType type) { if (_is_joker) { _piece_type = type; return true; } return false; }
        // Utility
        bool IsJoker() { return _is_joker; }
        bool IsInitiated() { return _piece_type != PieceType::NONE ? true : false; }
        bool operator<(const Piece& p);
        bool operator==(const Piece& p) { if ( this->GetPieceType() == p.GetPieceType()) return true; return false; }
        bool operator>(const Piece& p) { if ((*this) < p || (*this) == p) return false; return true; }
        Piece& operator=(const Piece& p);
        void NullifyPiece();
        void RemovePieceFromPlayer();
        
    friend ostream& operator<<(ostream& output, const Piece& piece);
};

char PieceTypeToChar(PieceType type);

#endif

