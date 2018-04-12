
#include "board.h"
#include "piece.h"
#include "player.h"
#include <cassert>
#include <iostream>
#include <cmath>

using namespace std;

/**
 * @brief Construct a new Board:: Board object
 * 
 * @param n The number of rows in the board
 * @param m The number of colums in the board
 */
Board::Board(int n, int m) {
    _n = n;
    _m = m;
    _board = new Piece*[n];
    if (_board) {
        for (int i=0;i < n; ++i) {
            _board[i] = new Piece[m];
            assert(_board[i]);
        }
        if (DEBUG) cout << "-> Created new board, (" << n << "," << m << ")" << ", [0,0]=" << _board[0][0] << endl;
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
        delete[] (_board[i]);
    }
    delete[] _board;
    if (DEBUG) cout << "--> Freed _board" << endl;
    if (DEBUG) cout << "- Piece count=" << Piece::GetPieceCounter() << endl;
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
 * @brief Merges a second board to the current board based on the rules of the game.
 * 
 * @param b The board to merge into the calling board.
 * @return Board& the current board as reference type.
 */
Board& Board::Merge(const Board& b) {
    assert(_m == b._m);
    assert(_n == b._n);
    for (int i=0;i<_n;++i) {
        for (int j=0;j<_m;++j) {
            if (_board[i][j].GetPieceType() == b._board[i][j].GetPieceType()) {
                _board[i][j].RemovePieceFromPlayer();
                b._board[i][j].RemovePieceFromPlayer();
                _board[i][j].NullifyPiece();
            } else if (_board[i][j].GetPieceType() == PieceType::NONE) {
                _board[i][j] = b._board[i][j];
            } 
            else {
                if (_board[i][j] < b._board[i][j]) {
                    _board[i][j].RemovePieceFromPlayer();
                    _board[i][j] = b._board[i][j];
                } else {
                    b._board[i][j].RemovePieceFromPlayer();
                }
                if (b._board[i][j].GetPieceType() != PieceType::NONE && _board[i][j].GetPieceType() == PieceType::BOMB) {
                    _board[i][j].RemovePieceFromPlayer();
                    _board[i][j].NullifyPiece();
                }
            }
        }
    }
    return *this;
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
bool Board::PlacePiece(Player* owner, PieceType type, int x, int y, string& msg, bool is_joker) {
    if (!IsPositionValid(x, y)) {
        msg = MSG_INVALID_POSITION;
        return false;
    }
    if (_board[x][y].IsInitiated()) {
        msg = MSG_PIECE_ALREADY_IN_PLACE;
        return false;
    }
    if (is_joker && (type == PieceType::FLAG)) {
        // joker cannot be flag
        return false;
    }
    Piece p(type, is_joker, owner);
    _board[x][y] = p;
    if (DEBUG) cout << "--> Piece initialized, " << _board[x][y] << endl;
    return true;
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
    if (!IsPositionValid(x, y) || !IsPositionValid(new_x, new_y) || !origin_piece.IsInitiated() || origin_piece.GetPlayerType() == destination_piece.GetPlayerType() || origin_piece.GetPieceType() == PieceType::BOMB || origin_piece.GetPieceType() == PieceType::FLAG || (abs(x - new_x) == 1 && abs(y - new_y) == 1) || abs(x-new_x) > 1 || abs(y - new_y) > 1) {
        msg = MSG_ILLEGAL_MOVE;
        return false;
    }
    return true;
}

/**
 * @brief Moves a piece from (x,y) to (new_x,new_y). Based on the rules of the game. Message is updated correctly.
 * 
 * @param x The origin X
 * @param y The origin Y
 * @param new_x The destination X
 * @param new_y The destination Y
 * @param msg A message if any error occured, or the Move is illegal
 */
bool Board::MovePiece(int x, int y, int new_x, int new_y, string& msg) {
    if (DEBUG) cout << "Moving (" << x << "," << y << "), to (" << new_x << "," << new_y << ")" << endl;
    if (!IsMoveLegal(x, y, new_x, new_y, msg)) {
        return false;
    }

    Piece& origin_piece = _board[x][y];
    Piece& destination_piece = _board[new_x][new_y];
    Piece temp_p;
    if (origin_piece == destination_piece) {
        msg = MSG_DEST_AND_ORIGIN_TIE;
        origin_piece.RemovePieceFromPlayer();
        destination_piece.RemovePieceFromPlayer();
    }
    else if (!destination_piece.IsInitiated()) {
        msg = MSG_EMPTY_DEST_PIECE;
        temp_p = origin_piece;
    }
    else if (origin_piece > destination_piece) {
        msg = MSG_DEST_PIECE_LOST;
        temp_p = origin_piece;
        destination_piece.RemovePieceFromPlayer();
    }
    else if (origin_piece < destination_piece) {
        msg = MSG_ORIGIN_PIECE_LOST;
        temp_p = destination_piece;
        origin_piece.RemovePieceFromPlayer();
    }
    destination_piece = temp_p;
    origin_piece.NullifyPiece();
    if (destination_piece.GetPieceType() == PieceType::BOMB) {
        destination_piece.NullifyPiece();
    }
    return true;
}

bool Board::ChangeJoker(int x, int y, PieceType new_type, string& msg) {
    if (!IsPositionValid(x,y)) {
        msg = MSG_ILLEGAL_MOVE;
        return false;
    }
    Piece& piece = _board[x][y];
    if (!piece.IsJoker() || new_type == PieceType::FLAG) {
        msg = MSG_ILLEGAL_MOVE;
        return false;
    }
    piece.SetType(new_type); // handles joker piece count
    return true;
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

/**
 * @brief Helper function for Board::PrettyPrint(). prints a line of dashes based on the number of columns
 * 
 * @param columns An integer
 */
void printLineOfDashes(int columns) {
    cout << "\t";
    for (int i=0; i< (columns*4 - 1); ++i) {
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
        cout << i+1 << "\t";
        for (int j=0; j<_m;++j) {
            if (j%2 == 1) cout << " ";
            cout << "[" << _board[i][j] << "]";
            if (j%2 == 1) cout << " ";
        }
        cout << endl;
        printLineOfDashes(_m);
    }
}