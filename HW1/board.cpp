
#include "board.h"
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
 * @brief Construct a new Board:: Board object (Copy C'tor)
 * 
 * @param b The board to copy from
 */
Board::Board(const Board& b) {
    *this = b;
}

/**
 * @brief Destroy the Board:: Board object
 * 
 */
Board::~Board() {
    for (int i=0; i < _n; ++i) {
        delete[] _board[i];
    }
    delete[] _board;
}

/**
 * @brief Overloading on the assignment (=) operator.
 * 
 * @param b The assignment variable
 * @return Board& Reference to the object for reassignment
 */
Board& Board::operator=(const Board& b) {
    if (this != &b) {
        if (_board != nullptr) {
            for (int i=0; i < _n; ++i) {
                delete[] _board[i];
            }
            delete[] _board;
        }
        _n = b._n;
        _m = b._m;
        _board = new Piece*[_n];
        if (_board) {
            for (int i=0;i < _n; ++i) {
                _board[i] = new Piece[_m];
                assert(_board[i]);
            }
        }
        for (int i=0;i<_n;++i) {
            if (!_board[i]) _board[i] = new Piece[_m];
            for (int j=0;j<_m;++j) {
                _board[i][j] = b._board[i][j];
            }
        }
    }
    return *this;
}

/**
 * @brief Overloading on the addition (+) operator. It adds together 2 boards.
 * Taking care of the rules. Used to combine the board for Player 1 and Player 2.
 * 
 * @param b The Board to add.
 * @return Board& A new board of the addition
 */
Board& Board::operator+(const Board& b) {
    assert(_m == b._m);
    assert(_n == b._n);
    Board* b_new = new Board(_n,_m);
    for (int i=0;i<_n;++i) {
        for (int j=0;j<_m;++j) {
            if (_board[i][j].GetPieceType() != b._board[i][j].GetPieceType()) {
                if (_board[i][j] < b._board[i][j]) {
                    b_new->_board[i][j] = b._board[i][j];
                } else {
                    b_new->_board[i][j] = _board[i][j];
                }
            }
        }
    }
    return *b_new;
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
bool Board::PlacePiece(PlayerType player, PieceType type, int x, int y, string& msg, bool is_joker) {
    if (!IsPositionValid(x, y)) {
        msg = "Bad position.";
        return false;
    }
    if (_board[x][y].IsInitiated()) {
        msg = "Piece already exists.";
        return false;
    }
    Piece p(x, y, player, type, is_joker);
    _board[x][y] = p;
    return true;
}

/**
 * @brief Helper function for Board::PrettyPrint(). prints a line of dashes based on the number of columns
 * 
 * @param columns An integer
 */
void printLineOfDashes(int columns) {
    for (int i=0; i< (columns*4+1); ++i) {
        cout << "-";
    }
    cout << endl;
}

/**
 * @brief Prints the board.
 * 
 */
void Board::PrettyPrint() {
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

/**
 * @brief Moves a piece from (x,y) to (new_x,new_y). Based on the rules of the game.
 * 
 * @param x The origin X
 * @param y The origin Y
 * @param new_x The destination X
 * @param new_y The destination Y
 * @param msg A message if any error occured, or the Move is illegal
 * @return true If origin piece won
 * @return false If destination piece won
 */
bool Board::MovePiece(int x, int y, int new_x, int new_y, string& msg) {
    Piece& origin_piece = _board[x][y];
    Piece& destination_piece = _board[new_x][new_y];
    if (!origin_piece.IsInitiated() || origin_piece.GetPlayerType() == destination_piece.GetPlayerType() || origin_piece.GetPieceType() == PieceType::BOMB || origin_piece.GetPieceType() == PieceType::FLAG) {
        // The piece cannot be moved
        msg = "The piece canot be moved, or doesn't exist.";
        return false;
    }
    else if (!destination_piece.IsInitiated() || origin_piece > destination_piece) {
        // origin piece wins
        msg = "Origin piece wins.";
        destination_piece = origin_piece;
        destination_piece.SetPosition(new_x, new_y);
        origin_piece.ClearPiece();
        return true;
    }
    // destination piece wins
    msg = "Destination piece wins.";
    origin_piece.ClearPiece();
    return false;
}
