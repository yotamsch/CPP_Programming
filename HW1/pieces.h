#ifndef _H_PIECES
#define _H_PIECES

#include <iostream>

#define R 2
#define P 5
#define S 1
#define B 2
#define J 2
#define F 1

using namespace std;

enum {ROCK, PAPER, SCISSORS, BOMB, FLAG, JOKER};

class Piece {
    private:
        int _index_x;
        int _index_y;
    public:
        Piece(int x, int y): _index_x(x), _index_y(y) {}
        virtual ~Piece() {}
        int getX() const { return _index_x; }
        int getY() const { return _index_y; }
        void setX(int x) { _index_x = x; }
        void setY(int y) {_index_y = y; }
        virtual void move(int new_x, int new_y) { setX(new_x); setY(new_y); }
        
    friend ostream& operator<<(ostream& output, const Piece& piece) {
        output << "(" << piece->_index_x << "," << piece->_index_y << ")";
        return output;
    }
};

class Rock : public Piece {
    private:
        const static int _max_pieces = R;
        static int _pieces_count;
    public:
        Rock(int x, int y) : Piece(x, y) { _pieces_count++; }
        static bool isExcessive() { return _pieces_count > _max_pieces; }
        ~Rock() override {}
};

class Paper : public Piece {
    private:
        const static int _max_pieces = P;
        static int _pieces_count;
    public:
        Paper(int x, int y) : Piece(x, y) {_pieces_count++; }
        static bool isExcessive() { return _pieces_count > _max_pieces; }
        ~Paper() override {}
};

class Scissors : public Piece {
    private:
        const static int _max_pieces = S;
        static int _pieces_count;
    public:
        Scissors(int x, int y) : Piece(x, y) { _pieces_count++; }
        static bool isExcessive() { return _pieces_count > _max_pieces; }
        ~Scissors() override {}
};

class Joker : public Piece {
    private:
        const static int _max_pieces = J;
        static int _pieces_count;
        int _piece_type;
    public:
        Joker(int x, int y, int type) : Piece(x, y), _piece_type(type) {}
        int getPieceType() const { return _piece_type; }
        void setPieceType(int new_type) { _piece_type = new_type; }
        static bool isExcessive() { return _pieces_count > _max_pieces; }
        ~Joker() override {}
};

class Bomb : public Piece {
    private:
        const static int _max_pieces = B;
        static int _pieces_count;
    public:
        static bool isExcessive() { return _pieces_count > _max_pieces; }
        ~Bomb() override {}
};

class Flag : public Piece {
    private:
        const static int _max_pieces = F;
        static int _pieces_count;
    public:
        static bool isExcessive() { return _pieces_count > _max_pieces; }
        ~Flag() override {}
};

#endif

