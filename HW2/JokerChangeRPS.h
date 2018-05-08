
#ifndef __H_JOKER_CHANGE_RPS
#define __H_JOKER_CHANGE_RPS

#include "JokerChange.h"
#include "PointRPS.h"
class JokerChangeRPS : public JokerChange {
private:
    PointRPS _changePosition;
    char _newRep;
public:
    //C'tor
    JokerChangeRPS(const PointRPS& rChangePosition, char newRep): _changePosition(rChangePosition), _newRep(newRep) {
        
    }
    // D'tor
    ~JokerChangeRPS(){}
    // Other
    const Point& getJokerChangePosition() const{
        return _changePosition;
    }
    char getJokerNewRep() const{
        return _newRep;
    }
};

#endif // !__H_JOKER_CHANGE_RPS