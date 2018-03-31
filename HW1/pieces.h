#ifndef _H_PIECES
#define _H_PIECES

#include <string>
#include <iostream>

using namespace std;

class Piece {
    int _index_x;
    int _index_y;
public:
    Piece(int x, int y): _index_x(x), _index_y(y) {}
    virtual ~Piece() {}
    int getX() const {return _index_x;}
    int getY() const {return _index_y;}
    friend ostream& operator<<(ostream& output, const Piece& piece) {
        output << "(" << piece->_index_x << "," << piece->_index_y << ")";
        return output;
    }
};

class Rock : public Piece {
public:
    void move() {}
    ~Rock() override {}
}

class Paper : public Piece {
public:
    void move() {}
    ~Paper() override {}
}

class Scissors : public Piece {
public:
    void move() {}
    ~Scissors() override {}
}

class Joker : public Piece {
public:
    void move() {}
    ~Joker() override {}
}

class Bomb : public Piece {
public:
    ~Bomb() override {}
}

class Flag : public Piece {
public:
    ~Flag() override {}
}

#endif

