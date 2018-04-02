
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
        ~Player() {}
        // Get
        PlayerType GetType() { return _type; }
        // Utilities
        void IncrementPieceCount(PieceType type);
        void DecrementPieceCount(PieceType type);
        bool IsLosing();
    
    friend ostream& operator<<(ostream& output, const Player& p);
};