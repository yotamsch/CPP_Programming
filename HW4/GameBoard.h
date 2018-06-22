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
        std::function<bool(const std::pair<int, GAME_PIECE>&)> _filter;

    public:
        iterator(PieceInfo<GAME_PIECE>* pos = nullptr, int loc = 0)
            : _pos(pos)
            , _loc(loc)
            , _filter([](const std::pair<int, GAME_PIECE>&) { return true; })
        {
        }
        std::tuple<int, int, GAME_PIECE, int> operator*() { return std::make_tuple(row(_loc), col(_loc), (*_pos)->second, (*_pos)->first); }
        iterator operator++()
        {
            do {
                ++_pos;
                ++_loc;
            } while (!_filter(*(*_pos)) && _loc < COLS * ROWS);
            if (_loc >= COLS * ROWS) {
                _filter = [](const std::pair<int, GAME_PIECE>&) { return true; };
            }
            return iterator(_pos, _loc);
        }
        bool operator!=(iterator other) const { return _pos != other._pos; }
        void setFilter(std::function<bool(const std::pair<int, GAME_PIECE>&)> filter)
        {
            _filter = filter;
        }

    private:
        int row(int loc) { return loc / COLS; }
        int col(int loc) { return loc % COLS; }
    };
    iterator begin() { return &_board.at(0); }
    iterator end() { return &_board.at(ROWS * COLS - 1) + 1; }

    PieceInfo<GAME_PIECE> getPiece(int row, int col)
    {
        if (_board[row * COLS + col] == nullptr) {
            return nullptr;
        }
        return std::move(std::make_unique<std::pair<int, GAME_PIECE>>(_board[row * COLS + col]->first, _board[row * COLS + col]->second));
    }

    PieceInfo<GAME_PIECE> setPiece(int row, int col, GAME_PIECE piece, int player)
    {
        auto prev_piece = getPiece(row, col);
        _board[row * COLS + col] = std::make_unique<std::pair<int, GAME_PIECE>>(player, piece);
        return std::move(prev_piece);
    }

    GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>& allPiecesOfPlayer(int playerNum)
    {
        setFilter([playerNum](const std::pair<int, GAME_PIECE>& p) { return p.first == playerNum; });
        return *this;
    }

    GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>& allOccureneceOfPiece(GAME_PIECE piece)
    {
        setFilter([piece](const std::pair<int, GAME_PIECE>& p) { return p.second == piece; });
        return *this;
    }

    GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>& allOccureneceOfPieceForPlayer(GAME_PIECE piece, int playerNum)
    {
        setFilter([piece,playerNum](const std::pair<int, GAME_PIECE>& p) { return (p.second == piece && p.first == playerNum); });
        return *this;
    }
};

#endif // !__GAME_BOARD_H_
