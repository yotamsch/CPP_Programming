
#ifndef __H_PIECE_RPS
#define __H_PIECE_RPS

#include "PiecePosition.h"
#include "GameManagerRPS.h"
#include "PointRPS.h"
class PieceRPS : public PiecePosition {
private:
    bool _is_joker;
    PieceType _piece_type;
    int _owner;
    static int _piece_counter; // general piece counter for debugging
    PointRPS _currPosition;

public:
    // C'tors
    PieceRPS() : _is_joker(false), _piece_type(PieceType::NONE), _owner(-1), _currPosition() {
        ++_piece_counter;
    }
    PieceRPS(PieceType type, bool is_joker, int owner, const PointRPS& rCurrPosition)
    : _is_joker(is_joker), _piece_type(type), _owner(owner), _currPosition(rCurrPosition){
          //  _owner->IncrementPieceCount(_piece_type); NEEDS REPLACEMENT!!

    }

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
    
    // Other
    const Point& getPosition() const;
    char getPiece() const;
    char getJokerRep() const;
};

char PieceTypeToChar(PieceType type);
PieceType CharToPieceType(char chr);

#endif // !__H_PIECE_RPS