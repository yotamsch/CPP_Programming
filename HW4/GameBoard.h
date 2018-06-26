/**
 * @brief The GameBoard class header file.
 * 
 * @file GameBoard.h
 * @author Yotam Sechayk
 * @date 2018-06-20
 */
#ifndef __GAME_BOARD_H_
#define __GAME_BOARD_H_

#include <array>
#include <functional>
#include <memory>

// the Piece Info element
template <typename GAME_PIECE>
using PieceInfo = std::unique_ptr<const std::pair<int, GAME_PIECE>>;

template <int ROWS, int COLS, typename GAME_PIECE, int PLAYERS = 2>
class GameBoard {
private:
    std::array<PieceInfo<GAME_PIECE>, ROWS * COLS> _board;

public:
    GameBoard() {}
    ~GameBoard() {}

    class iterator {
    private:
        PieceInfo<GAME_PIECE>* _pos;
        int _loc;
        static std::function<bool(const std::pair<int, GAME_PIECE>&)> filter;

    public:
        iterator(PieceInfo<GAME_PIECE>* pos = nullptr, int loc = 0)
            : _pos(pos)
            , _loc(loc)
        {
            auto r = *_pos == nullptr ? false : filter(*(*_pos));
            while (!r && _loc < ROWS * COLS) {
                ++_pos;
                ++_loc;
                r = *_pos == nullptr ? false : filter(*(*_pos));
            }
        }
        std::tuple<int, int, GAME_PIECE, int> operator*() { return std::make_tuple(row(_loc), col(_loc), (*_pos)->second, (*_pos)->first); }
        iterator operator++()
        {
            bool r;
            do {
                ++_pos;
                ++_loc;
                r = *_pos == nullptr ? false : filter(*(*_pos));
            } while (!r && _loc < COLS * ROWS);
            // if reached the end, reset the filter
            if (_loc >= COLS * ROWS) {
                filter = [](const std::pair<int, GAME_PIECE>&) { return true; };
            }
            return iterator(_pos, _loc);
        }
        bool operator!=(iterator other) const { return _pos != other._pos; }
        // set the filter of the iterator
        static void setFilter(std::function<bool(const std::pair<int, GAME_PIECE>&)> f)
        {
            filter = f;
        }

    private:
        int row(int loc) { return loc / COLS; }
        int col(int loc) { return loc % COLS; }
    };
    // begin iterator
    iterator begin() { return iterator(&_board.at(0), 0); }
    // end iterator
    iterator end() { return iterator(&_board.at(ROWS * COLS - 1) + 1, ROWS * COLS); }

    /**
     * @brief Get the Piece Info object at positiong (row,col). If no piece exists in that position, returns nullptr.
     * 
     * @param row - A 0-based row position
     * @param col - A 0-based column position
     * @return PieceInfo<GAME_PIECE> - A unique_ptr to the Piece Info object (const pair<int, piece_type>)
     */
    PieceInfo<GAME_PIECE> getPiece(int row, int col)
    {
        if (!isPositionLegal(row, col)) {
            return nullptr;
        }
        if (_board[row * COLS + col] == nullptr) {
            return nullptr;
        }
        return std::move(std::make_unique<std::pair<int, GAME_PIECE>>(_board[row * COLS + col]->first, _board[row * COLS + col]->second));
    }

    /**
     * @brief Insert a Piece Info object into the board. If a piece was already in the insertion place, it overwrites it. Returns nullptr if no piece was present, otherwise the Piece Info object of the previus piece.
     * 
     * @param row - A 0-based row position
     * @param col - A 0-based column position
     * @param piece - The piece itself, assuming same type as the board piece type
     * @param player - the player which the piece belongs to
     * @return PieceInfo<GAME_PIECE> - The previus piece in that place or nullptr if no piece existed or the position isn't valid
     */
    PieceInfo<GAME_PIECE> setPiece(int row, int col, GAME_PIECE piece, int player)
    {
        if (!isPositionLegal(row, col)) {
            return nullptr;
        }
        if (player < 0 || player >= PLAYERS) {
            return nullptr;
        }
        auto prev_piece = getPiece(row, col);
        _board[row * COLS + col] = std::make_unique<std::pair<int, GAME_PIECE>>(player, piece);
        return std::move(prev_piece);
    }

    GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>& allPiecesOfPlayer(int playerNum)
    {
        iterator::setFilter([playerNum](const std::pair<int, GAME_PIECE>& p) { return p.first == playerNum; });
        return *this;
    }

    GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>& allOccureneceOfPiece(GAME_PIECE piece)
    {
        iterator::setFilter([piece](const std::pair<int, GAME_PIECE>& p) { return p.second == piece; });
        return *this;
    }

    GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>& allOccureneceOfPieceForPlayer(GAME_PIECE piece, int playerNum)
    {
        iterator::setFilter([piece, playerNum](const std::pair<int, GAME_PIECE>& p) { return (p.second == piece && p.first == playerNum); });
        return *this;
    }

private:
    /**
     * @brief Checks if the given position is legal and within the board dimensions.
     * 
     * @param row - A 0-based row position
     * @param col - A 0-based column position
     * @return true - Only if 0 <= row < ROWS, 0 <= col < COLS
     * @return false - Otherwise
     */
    bool isPositionLegal(int row, int col)
    {
        if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
            return false;
        }
        return true;
    }
};

template <int ROWS, int COLS, typename GAME_PIECE, int PLAYERS>
std::function<bool(const std::pair<int, GAME_PIECE>&)> GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator::filter = [](const std::pair<int, GAME_PIECE>&) -> bool { return true; };

#endif // !__GAME_BOARD_H_
