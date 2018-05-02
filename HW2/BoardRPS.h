
#ifndef __H_BOARD_RPS
#define __H_BOARD_RPS

#include "Board.h"
#include "PieceRPS.h"
#include "GameManagerRPS.h" //included this just to get the enum types, maybe should be changed
/*COPIED FROM HW1- board.h*/
#define MSG_ILLEGAL_MOVE "The attempted move is illegal."
#define MSG_EMPTY_DEST_PIECE "The destination has no piece."
#define MSG_ORIGIN_PIECE_LOST "The origin piece lost and was eaten."
#define MSG_DEST_PIECE_LOST "The destination piece lost and was eaten."
#define MSG_DEST_AND_ORIGIN_TIE "Both origin and destination are tied (both eaten)."
#define MSG_PIECE_ALREADY_IN_PLACE "Another piece exists in the requested place."
#define MSG_INVALID_POSITION "The requested position is invalid."
/*end of copy*/

class BoardRPS : public Board {
private:
    /*COPIED FROM HW1- board.h*/
    int _n;
    int _m;
    std::vector<std::vector<PieceRPS>> _board;
public:
    // C'tor
    BoardRPS(int n, int m);
    BoardRPS(const BoardRPS& b);

    // D'tor
    ~BoardRPS();
    // Other
    int getPlayer(const Point& pos) const;
    int GetDimentionX() { return _n; }
    int GetDimentionY() { return _m; }
    std::vector<std::vector<PieceRPS>>& getBoard(){return _board;}

    // Utility
    BoardRPS& operator=(const BoardRPS& b);
    bool IsPositionValid(int x, int y) { return (x >= 0 && x < _n) && (y >= 0 && y < _m); }
    bool IsMoveLegal(int x, int y, int new_x, int new_y);
    bool PlacePiece(int owner, PieceType type, int x, int y, bool is_joker=false);
    bool MovePiece(int x, int y, int new_x, int new_y);
    bool ChangeJoker(const Point& point, PieceType new_type);
    BoardRPS& Merge(const BoardRPS& b);
    bool isThereAFight(int vNewX, int vNewY);
    void PrettyPrint();

friend ostream& operator<<(ostream& output, const BoardRPS& b);

};

#endif // !__H_BOARD_RPS
