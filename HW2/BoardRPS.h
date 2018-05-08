
#ifndef __H_BOARD_RPS
#define __H_BOARD_RPS

#include "Board.h"
#include "FightInfoRPS.h"
#include "GameUtilitiesRPS.h"
#include "JokerChangeRPS.h"
#include "MoveRPS.h"
#include "PieceRPS.h"
#include <iostream>
#include <memory>
#include <vector>

class BoardRPS : public Board {
private:
    int _n; // rows
    int _m; // columns
    // the board vector is of size : rows * columns
    std::vector<std::unique_ptr<PieceRPS>> _board;

public:
    // basic c'tors
    BoardRPS(int n, int m)
        : _n(n) // the number of rows
        , _m(m) // the number of columns
        , _board(_n * _m) // initialize the board vector
    {
    }
    // no need for copy c'tor
    BoardRPS(const BoardRPS& other) = delete;
    // move c'tor
    // TODO: maybe move c'tor not needed
    BoardRPS(BoardRPS&& other)
        : _n(other._n) // the number of rows
        , _m(other._m) // the number of columns
    {
        std::swap(this->_board, other._board);
    }

    // d'tor
    ~BoardRPS() {}

    // getters
    // TODO: not sure if they are in use, maybe not needed
    int getN() const { return _n; }
    int getM() const { return _m; }
    // TODO: not sure this getter is needed
    const std::vector<std::unique_ptr<PieceRPS>>& getBoard() const { return _board; }

    // utility
    // move assignment
    // TODO: maybe move assignment not needed
    BoardRPS& operator=(BoardRPS&& b);
    // gets a reference to the pointer of the piece at position (nullptr if no piece)
    const std::unique_ptr<PieceRPS> const& getPieceAt(const Point& point);
    // place a piece into the board
    bool placePiece(int player, std::unique_ptr<PiecePosition>& rpPiece, std::unique_ptr<FightInfo>& rpFightInfo);
    // move an existing piece on the board 'from' -> 'to'
    bool movePiece(int player, const std::unique_ptr<Move>& rpMove, std::unique_ptr<FightInfo>& rpFightInfo);
    // change an existing joker's representation
    bool changeJoker(int player, const std::unique_ptr<JokerChange>& rpJokerChange);
    // print the board nicely
    // TODO: remove method before submission
    void prettyPrint();

    // interface defined functions
    // get the player number (id/type) of the piece in the position
    int getPlayer(const Point& pos) const;

private:
    // checks if the point position is valid
    bool isPositionValid(int x, int y);
    // checks if the point position is valid for (x,y) and (new_x,new_y)
    // also checks if the position is 'movable-valid'
    bool isPositionValid(int x, int y, int new_x, int new_y);
    // checks if a certain move is legal for the player
    bool isMoveLegal(int player, int x, int y, int new_x, int new_y);

    // calculates the correct vector position
    // TODO: maybe rename to something else
    int p(int x, int y) const { return y * _m + x; }

public:
    // friend method, overloading '<<' for printing the board
    friend std::ostream& operator<<(std::ostream& output, const BoardRPS& b);
};

#endif // !__H_BOARD_RPS
