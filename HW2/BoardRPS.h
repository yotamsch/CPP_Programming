
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
    // clears the board of pieces
    void clearBoard();

    /**
     * @brief Gets a reference to the pointer of the piece at position point
     * 
     * @param point - the position that we need to know what piece happens to be in.
     * @return const std::unique_ptr<PieceRPS>& -reference to the piece at the specified position (nullptr if there is no piece)
     */
    const std::unique_ptr<PieceRPS>& getPieceAt(const Point& point);
    

/**
 * @brief The function creates and places a new piece on the board. 
 * Based on the rules of each piece (found by its type).
 * 
 * @param player The player type (PLAYER_1 or PLAYER_2)
 * @param type The piece type
 * @param x The x position on the board
 * @param y The y position on the board
 * @param is_joker Is the piece a joker piece
 * @return true If everything went fine and the piece has been inserted into the board.
 * @return false If an error occured
 */
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

    /**
     * @brief checks if the point position is valid 
     * 
     * @param x - row coordinate
     * @param y - column coordinate
     * @return false - if x<0 or x> #of rows or y<0 or y> #of columns
     * @return true - otherwise
     */
    bool isPositionValid(int x, int y);

    // checks if the point position is valid for (x,y) and (new_x,new_y)
    // also checks if the position is 'movable-valid'
    bool isPositionValid(int x, int y, int new_x, int new_y);
    //check if a certain move is legal
    bool isMoveLegal(int player, int x, int y, int new_x, int new_y);
    // calculates the correct vector position
    // TODO: maybe rename to something else
    int p(int x, int y) const { return y * _m + x; }

public:
    // friend method, overloading '<<' for printing the board
    friend std::ostream& operator<<(std::ostream& output, const BoardRPS& b);
};

#endif // !__H_BOARD_RPS
