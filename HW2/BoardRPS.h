/**
 * @brief The header file for the BoardRPS class.
 * 
 * @file BoardRPS.h
 * @author Yotam Sechayk
 * @date 2018-05-13
 */
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

/**
 * @brief a class inheriting from the abstract class Board, controlling all that happens on the game board
 * 
 */
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
    BoardRPS(BoardRPS&& other)
        : _n(other._n) // the number of rows
        , _m(other._m) // the number of columns
    {
        std::swap(this->_board, other._board);
    }

    // d'tor
    ~BoardRPS() {}

    // getters
    // gets a reference to the pointer of a piece in position
    const std::unique_ptr<PieceRPS>& getPieceAt(const Point& point) const;

    // utility
    // move assignment
    BoardRPS& operator=(BoardRPS&& b);
    // clears the board of pieces
    void clearBoard();
    // place a piece on the board, update fight info accordingly
    bool placePiece(int player, std::unique_ptr<PiecePosition>& rpPiece, std::unique_ptr<FightInfo>& rpFightInfo);
    // move an existing piece on the board 'from' -> 'to'
    bool movePiece(int player, const std::unique_ptr<Move>& rpMove, std::unique_ptr<FightInfo>& rpFightInfo);
    // change an existing joker's representation
    bool changeJoker(int player, const std::unique_ptr<JokerChange>& rpJokerChange);
    // print the board nicely
    void prettyPrint();

    // interface defined functions
    // get the player number (id/type) of the piece in the position
    int getPlayer(const Point& pos) const;

private:

    // checks if the position is valid
    bool isPositionValid(int x, int y);
    // checks if the point position is valid for (x,y) and (new_x,new_y)
    // also checks if the position is 'movable-valid'
    bool isPositionValid(int x, int y, int new_x, int new_y);
    //check if a certain move is legal
    bool isMoveLegal(int player, int x, int y, int new_x, int new_y);
    // calculates the correct vector position
    int p(int x, int y) const { return y * _m + x; }

public:
    // friend method, overloading '<<' for printing the board
    friend std::ostream& operator<<(std::ostream& output, const BoardRPS& b);
};

#endif // !__H_BOARD_RPS
