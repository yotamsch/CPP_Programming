
#include "board.h"
#include "piece.h"
#include "player.h"
#include <cassert>
#include <iostream>

#define ILLEGAL_MOVE "The attempted move is illegal."
#define EMPTY_DEST_PIECE "The destination has no piece."
#define ORIGIN_PIECE_LOST "The origin piece lost and was eaten."
#define DEST_PIECE_LOST "The destination piece lost and was eaten."
#define DEST_AND_ORIGIN_TIE "Both origin and destination are tied (both eaten)."

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
    if (DEBUG) cout << "-> Freeing BOARD : " << this << endl;
    for (int i=0; i < _n; ++i) {
        delete[] (_board[i]);
        if (DEBUG) cout << "--> Freed _board[" << i << "]" << endl;
    }
    delete[] _board;
    if (DEBUG) cout << "--> Freed _board" << endl;
    if (DEBUG) cout << "- Counter=" << Piece::GetPieceCounter() << endl;
}

/**
 * @brief Overloading on the assignment (=) operator.
 * 
 * @param b The assignment variable
 * @return Board& Reference to the object for reassignment
 */
Board& Board::operator=(const Board& b) {
    cout << this << ", " << (*this) << endl;
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
                    _board[i][j].RemovePieceFromPlayer();
                } else {
                    b_new->_board[i][j] = _board[i][j];
                    b._board[i][j].RemovePieceFromPlayer();
                }
            } else {
                _board[i][j].RemovePieceFromPlayer();
                b._board[i][j].RemovePieceFromPlayer();
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
bool Board::PlacePiece(Player* owner, PlayerType player, PieceType type, int x, int y, string& msg, bool is_joker) {
    if (!IsPositionValid(x, y)) {
        msg = "Bad position.";
        return false;
    }
    if (_board[x][y].IsInitiated()) {
        msg = "Piece already exists.";
        return false;
    }
    Piece p(player, type, is_joker, owner);
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
 * @brief Checks if a certain move is legal. If not updates a message correctly.
 * 
 * @param x The origin X.
 * @param y The origin Y.
 * @param new_x The destination X.
 * @param new_y The destination Y.
 * @param msg The message will be updated into this.
 * @return true The move is legal.
 * @return false The move is illegal.
 */
bool Board::IsMoveLegal(int x, int y, int new_x, int new_y, string& msg) {
    Piece& origin_piece = _board[x][y];
    Piece& destination_piece = _board[new_x][new_y];
    if (!origin_piece.IsInitiated() || origin_piece.GetPlayerType() == destination_piece.GetPlayerType() || origin_piece.GetPieceType() == PieceType::BOMB || origin_piece.GetPieceType() == PieceType::FLAG) {
        msg = ILLEGAL_MOVE;
        return false;
    }
    return true;
}

/**
 * @brief Moves a piece from (x,y) to (new_x,new_y). Based on the rules of the game. Assumes the move is legal. Message is updated correctly.
 * 
 * @param x The origin X
 * @param y The origin Y
 * @param new_x The destination X
 * @param new_y The destination Y
 * @param msg A message if any error occured, or the Move is illegal
 */
void Board::MovePiece(int x, int y, int new_x, int new_y, string& msg) {
    Piece& origin_piece = _board[x][y];
    Piece& destination_piece = _board[new_x][new_y];
    Piece temp_p;

    if (origin_piece == destination_piece) {
        msg = DEST_AND_ORIGIN_TIE;
        origin_piece.RemovePieceFromPlayer();
        destination_piece.RemovePieceFromPlayer();
    }
    else if (!destination_piece.IsInitiated()) {
        msg = EMPTY_DEST_PIECE;
        temp_p = origin_piece;
    }
    else if (origin_piece > destination_piece) {
        msg = DEST_PIECE_LOST;
        temp_p = origin_piece;
        destination_piece.RemovePieceFromPlayer();
    }
    else if (origin_piece < destination_piece) {
        msg = ORIGIN_PIECE_LOST;
        temp_p = destination_piece;
        origin_piece.RemovePieceFromPlayer();
    }
    destination_piece = temp_p;
    origin_piece.NullifyPiece();
}

ostream& operator<<(ostream& output, const Board& b) {
    for (int i=0; i<b._n; ++i) {
        for (int j=0; j<b._m;++j) {
            output  << b._board[i][j];
        }
        output << endl;
    }
    return output;
}
