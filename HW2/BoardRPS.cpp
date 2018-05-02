#include "BoardRPS.h"
#include <cassert>
#include <iostream>
#include <cmath>
#include <memory>

using namespace std;

/**
 * @brief Construct a new BoardRPS:: BoardRPS object
 * 
 * @param n The number of rows in the board
 * @param m The number of colums in the board
 */
BoardRPS::BoardRPS(int n, int m) {
    _n = n;
    _m = m;
    _board.resize(n, std::vector<PieceRPS>(m, PieceRPS()));
}

/**
 * @brief Construct a new BoardRPS:: BoardRPS object (Copy C'tor)
 * 
 * @param b The board to copy from
 */
BoardRPS::BoardRPS(const BoardRPS& b) {
    *this = b;
}

/**
 * @brief Destroy the BoardRPS:: BoardRPS object
 * 
 */
BoardRPS::~BoardRPS() {
    //? make sure that there's no need to delete anything
    /*for (int i=0; i < _n; ++i) {
        delete[] (_board[i]);
    }
    delete[] _board;
    */
}


int BoardRPS::getPlayer(const Point& pos) const{}

/**
 * @brief Overloading on the assignment (=) operator.
 * 
 * @param b The assignment variable
 * @return BoardRPS& Reference to the object for reassignment
 */
BoardRPS& BoardRPS::operator=(const BoardRPS& rOtherBoard) {
    cout << this << ", " << (*this) << endl;
    if (this != &rOtherBoard) {
        _n = rOtherBoard._n;
        _m = rOtherBoard._m;
        for(int i = 0; i < _n; i++){
            for(int j = 0; j< _m; j++){
                _board[i][j] = rOtherBoard._board[i][j];
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
BoardRPS& BoardRPS::Merge(const BoardRPS& b) {
    assert(_m == b._m);
    assert(_n == b._n);
    for (int i=0;i<_n;++i) {
        for (int j=0;j<_m;++j) {
            if (_board[i][j].GetPieceType() == b._board[i][j].GetPieceType()) {
                _board[i][j].RemovePieceFromPlayer();
                PieceRPS oppPiece = b._board[i][j];
                oppPiece.RemovePieceFromPlayer();     
               // b._board[i][j].RemovePieceFromPlayer();
                _board[i][j].NullifyPiece();
            } else if (_board[i][j].GetPieceType() == PieceType::NONE) {
                _board[i][j] = b._board[i][j];
            } 
            else {
                if (_board[i][j] < b._board[i][j]) {
                    _board[i][j].RemovePieceFromPlayer();
                    _board[i][j] = b._board[i][j];
                } else {
                    PieceRPS oppPiece = b._board[i][j];
                    oppPiece.RemovePieceFromPlayer();
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


bool BoardRPS::isThereAFight(int vNewX, int vNewY){
    PieceRPS pieceAtDestination = _board[vNewX][vNewX];
    return pieceAtDestination.IsInitiated();
}


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
bool BoardRPS::PlacePiece(int owner, PieceType type, int x, int y, bool is_joker) {
    if (!IsPositionValid(x, y)) {
        return false;
    }
    if (_board[x][y].IsInitiated()) {
        return false;
    }
    if (is_joker && (type == PieceType::FLAG)) {
        // joker cannot be flag
        return false;
    }
    PieceRPS p(type, is_joker, owner);
    _board[x][y] = p;
    return true;
}

/**
 * @brief Checks if a certain move is legal. If not updates a message correctly.
 * 
 * @param x The origin X.
 * @param y The origin Y.
 * @param new_x The destination X.
 * @param new_y The destination Y.
 * @return true The move is legal.
 * @return false The move is illegal.
 */
bool BoardRPS::IsMoveLegal(int x, int y, int new_x, int new_y) {
    PieceRPS& origin_piece = _board[x][y];
    PieceRPS& destination_piece = _board[new_x][new_y];
    if (!IsPositionValid(x, y) || !IsPositionValid(new_x, new_y) || !origin_piece.IsInitiated() || origin_piece.GetPlayerType() == destination_piece.GetPlayerType() || origin_piece.GetPieceType() == PieceType::BOMB || origin_piece.GetPieceType() == PieceType::FLAG || (abs(x - new_x) == 1 && abs(y - new_y) == 1) || abs(x-new_x) > 1 || abs(y - new_y) > 1) {
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
 */
bool BoardRPS::MovePiece(int x, int y, int new_x, int new_y) {
    if (!IsMoveLegal(x, y, new_x, new_y)) {
        return false;
    }

    PieceRPS& origin_piece = _board[x][y];
    PieceRPS& destination_piece = _board[new_x][new_y];
    PieceRPS temp_p;
    if (origin_piece == destination_piece) {
        origin_piece.RemovePieceFromPlayer();
        destination_piece.RemovePieceFromPlayer();
    }
    else if (!destination_piece.IsInitiated()) {
        temp_p = origin_piece;
    }
    else if (origin_piece > destination_piece) {
        temp_p = origin_piece;
        destination_piece.RemovePieceFromPlayer();
    }
    else if (origin_piece < destination_piece) {
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

bool BoardRPS::ChangeJoker(int x, int y, PieceType new_type) {
    if (!IsPositionValid(x,y)) {
        return false;
    }
    PieceRPS& piece = _board[x][y];
    if (!piece.IsJoker() || new_type == PieceType::FLAG) {
        return false;
    }
    piece.SetType(new_type); // handles joker piece count
    return true;
}

ostream& operator<<(ostream& output, const BoardRPS& rOtherBoard) {
    for (int i=0; i<rOtherBoard._n; ++i) {
        for (int j=0; j<rOtherBoard._m;++j) {
            output  << rOtherBoard._board[i][j];
        }
        output << endl;
    }
    return output;
}

/**
 * @brief Helper function for BoardRPS::PrettyPrint(). prints a line of dashes based on the number of columns
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
void BoardRPS::PrettyPrint() {
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