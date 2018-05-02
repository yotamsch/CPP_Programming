
#ifndef __H_PIECE_RPS
#define __H_PIECE_RPS

#include "PiecePosition.h"
#include "GameManagerRPS.h"
class PieceRPS : public PiecePosition {
private:
    /*COPY OF HW1- piece.h*/
    bool _is_joker;
    PieceType _piece_type;
    int _owner;

    static int _piece_counter; // general piece counter for debugging
    /*END OF COPY*/
public:
    /*COPY OF HW1- piece.h*/
    // C'tors
    PieceRPS() : _is_joker(false), _piece_type(PieceType::NONE), _owner(-1) { ++_piece_counter; }
    PieceRPS(PieceType type, bool is_joker, int owner);
    PieceRPS(const PieceRPS& p) { *this = p; }

    // D'tor
    ~PieceRPS(){--_piece_counter;}
    // Get
    PieceType GetPieceType() const { return _piece_type; }
    PlayerType GetPlayerType() const {
        if(_owner==1){
            return PlayerType::PLAYER_1;
        }
        if(_owner==2){
            return PlayerType::PLAYER_2;
        }
        return PlayerType::NONE;
    }
    static int GetPieceCounter() {return _piece_counter; }
    // Set
    bool SetType(PieceType type);
    // Utility
    bool IsJoker() { return _is_joker; }
    bool IsInitiated() { return _piece_type != PieceType::NONE ? true : false; }
    bool operator<(const PieceRPS& p);
    bool operator==(const PieceRPS& p) { if ( this->GetPieceType() == p.GetPieceType()) return true; return false; }
    bool operator>(const PieceRPS& p) { return (*this) < p || (*this) == p ? false : true; }
    PieceRPS& operator=(const PieceRPS& p);
    void NullifyPiece();
    void RemovePieceFromPlayer();
    
friend ostream& operator<<(ostream& output, const PieceRPS& piece);
    /*END OF COPY*/
    
    // Other
    const Point& getPosition() const;
    char getPiece() const;
    char getJokerRep() const;
    //added by Tala:
    void setPosition(const Point& rPoint);
};

/* COPY OF HW1- piece.h*/
char PieceTypeToChar(PieceType type);
PieceType CharToPieceType(char chr);
/*END OF COPY*/

#endif // !__H_PIECE_RPS