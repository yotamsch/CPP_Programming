#ifndef _H_PIECES
#define _H_PIECES

#include "game.h"
#include "player.h"
#include <iostream>
#include <ctype.h>

using namespace std;

class Piece {
        bool _is_joker;
        PieceType _piece_type;
        Player* _owner;
        static int _piece_counter; // general piece counter for debugging
    public:
        // C'tors
        Piece() : _is_joker(false), _piece_type(PieceType::NONE), _owner(nullptr) { ++_piece_counter; }
        Piece(PieceType type, bool is_joker, Player* owner);
		Piece(const Piece& p) { *this = p; }
        // D'tor
        ~Piece() { --_piece_counter; }
        // Get
        PieceType GetPieceType() const { return _piece_type; }
        PlayerType GetPlayerType() const { return _owner ? _owner->GetType() : PlayerType::NONE; }
        static int GetPieceCounter() {return _piece_counter; }
        // Set
        bool SetType(PieceType type);
        // Utility
        bool IsJoker() { return _is_joker; }
        bool IsInitiated() { return _piece_type != PieceType::NONE ? true : false; }
        bool operator<(const Piece& p);
        bool operator==(const Piece& p) { if ( this->GetPieceType() == p.GetPieceType()) return true; return false; }
        bool operator>(const Piece& p) { return (*this) < p || (*this) == p ? false : true; }
        Piece& operator=(const Piece& p);
        void NullifyPiece();
        void RemovePieceFromPlayer();
        
    friend ostream& operator<<(ostream& output, const Piece& piece);
};

char PieceTypeToChar(PieceType type);
PieceType CharToPieceType(char chr);

#endif

