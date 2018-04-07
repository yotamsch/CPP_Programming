
#ifndef _H_PLAYER
#define _H_PLAYER

#include <iostream>
#include "game.h"

using namespace std;

class Player {
    private:
        PlayerType _type;
        int _number_of_flags;
        int _number_of_pieces;
    public:
        // C'tor
        Player();
        Player(PlayerType type) : _type(type), _number_of_flags(0), _number_of_pieces(0) {}
        // D'tor
        ~Player() { if (DEBUG) cout << "-> Freed Player " << int(_type) << endl; }
        // Get
        PlayerType GetType() { return _type; }
        // Utilities
        void IncrementPieceCount(PieceType type);
        void DecrementPieceCount(PieceType type);
        Reason IsLosing();
    
    friend ostream& operator<<(ostream& output, const Player& p);
};

#endif