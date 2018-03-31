#include "board.h"
#include "pieces.h"
#include <cassert>
#include <iostream>

using namespace std;

/**
 * @brief Construct a new Board:: Board object
 * 
 * @param n The number of rows in the board
 * @param m The number of colums in the board
 */
Board::Board(int n, int m) : _m(m), _n(n) {
    assert(n > 0);
    assert(m > 0);
    _board = new Piece*[n];
    if (_board) {
        for (int i=0;i < n; ++i) {
            _board[i] = new Piece[m];
            assert(_board[i]);
        }
    }
}

/**
 * @brief Destroy the Board:: Board object
 * 
 */
Board::~Board() {
    if (_n == 0 && _m == 0) {
        return;
    }
    for (int i=0; i < _n; ++i) {
        delete[] _board[i];
    }
    delete[] _board;
}

/**
 * @brief The function creates and places a new piece on the board. 
 * Based on the rules of each piece (found by its type).
 * 
 * @param player The player type (PLAYER_1 or PLAYER_2)
 * @param type The piece type
 * @param x The x position on the board
 * @param y The y position on the board
 * @param msg Reference to the output message
 * @param is_joker Is the piece a joker piece
 * @return true If everything went fine and the piece has been inserted into the board.
 * @return false If an error occured, updating msg correctly
 */
bool Board::placePiece(int player, int type, int x, int y, string& msg, bool is_joker) {
    if (!isPositionValid(x, y)) {
        msg = "Bad position.";
        return false;
    }
    if (_board[x][y].isInitiated()) {
        msg = "Piece already exists.";
        return false;
    }
    Piece p(x, y, player, type, is_joker);
    _board[x][y] = p;
    return true;
}

void printLineOfDashes(int colums) {
    for (int i=0; i< (colums*4+1); ++i) {
        cout << "-";
    }
    cout << endl;
}

/**
 * @brief Prints the board.
 * 
 */
void Board::prettyPrint() {
    if (_n == 0 && _m == 0) {
        cout << "[...]" << endl;
        return;
    }
    printLineOfDashes(_m);
    for (int i=0; i<_n; ++i) {
        cout << "-";
        for (int j=0; j<_m;++j) {
            if (j%2 == 1) cout << " ";
            cout << "[" << _board[i][j] << "]";
            if (j%2 == 1) cout << " ";
        }
        cout << "-" << endl;
        printLineOfDashes(_m);
    }
}
