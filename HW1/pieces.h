#ifndef _H_PIECES
#define _H_PIECES

#include "game.h"
#include <iostream>
#include <ctype.h>

using namespace std;

/**
 * @brief An enum representing the different types of play pieces
 * 
 */
enum {NONE=-1, ROCK=0, PAPER, SCISSORS, BOMB, FLAG, JOKER};
char pieceTypeToChar(int type, int player_id);

class Piece {
    private:
        int _index_x;
        int _index_y;
        int _player_id;
        int _piece_type;
        bool _is_joker;
    public:
        // C'tors
        Piece() : _piece_type(NONE) {}
        Piece(int x, int y, int player_id, int type, bool is_joker): _index_x(x), _index_y(y), _player_id(player_id), _piece_type(type), _is_joker(is_joker) {}
        // D'tor
        virtual ~Piece() {}
        // Get
        int getX() const { return _index_x; }
        int getY() const { return _index_y; }
        int getPieceType() const { return _piece_type; }
        int getPlayerId() const { return _player_id; }
        // Set
        void setX(int x) { _index_x = x; }
        void setY(int y) { _index_y = y; }
        bool setType(int type) { if (_is_joker) { _piece_type = type; return true; } return false; }
        // Utility
        bool isJoker() { return _is_joker; }
        bool isInitiated() { return _piece_type != NONE ? true : false; }
        bool operator<(const Piece& p);
        virtual bool move(int new_x, int new_y) { setX(new_x); setY(new_y); }
        
    friend ostream& operator<<(ostream& output, const Piece& piece);
};

#endif

