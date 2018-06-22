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

// the Board Dimension element
using Dim = std::pair<size_t, size_t>;

template <size_t ROWS, size_t COLS, typename GAME_PIECE, size_t PLAYERS = 2>
class GameBoard {
public:
    template <decltype(typedef[](PieceInfo&) -> bool) FILTER = [](PieceInfo&) { return true; }>
    class iterator {
    private:
        PieceInfo* _pos;
        int _loc;

    public:
        iterator(PieceInfo* pos = nullptr, int loc = 0)
            : _pos(pos)
            , _loc(loc){};
        std::tuple<int, int, GAME_PIECE, int> operator*() { return std::make_tuple(row(_loc), col(_loc), *_pos->first, *_pos->second); }
        iterator operator++() { return iterator(++_pos, ++_loc); }
        bool operator!=(iterator other) const { return _pos != other._pos; }

    private:
        int row(int loc) { return loc / COLS; }
        int col(int loc) { return loc % COLS; }
    };
    iterator<> begin() { return &_board.at(0); }
    iterator<> end() { return &_board.at(ROWS * COLS - 1) + 1; }
    PieceInfo<GAME_PIECE> getPiece(int row, int col);
    PieceInfo<GAME_PIECE> setPiece(int row, int col, GAME_PIECE piece, int player);

private:
    std::array<PieceInfo, ROWS * COLS> _board;

public:
    Dim getDim() const { return std::make_pair(ROWS, COLS); }
};

#endif // !__GAME_BOARD_H_
