#include "board.h"
#include <cassert>

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
 * @param type The type of the piece (enum)
 * @param x The x position on the board
 * @param y The y position on the board
 * @param is_joker Optional. If the piece is a joker (default: false)
 * @return true If the operation was successful
 * @return false If the input makes an invalid piece
 */
bool Board::placePiece(int type, int x, int y, bool is_joker) {
    // TODO: implementation
    return false;
}
