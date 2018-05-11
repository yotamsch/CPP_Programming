
#ifndef __H_JOKER_CHANGE_RPS
#define __H_JOKER_CHANGE_RPS

#include "JokerChange.h"
#include "PointRPS.h"
class JokerChangeRPS : public JokerChange {
private:
    PointRPS _changePosition;
    char _newRep;

public:
    // basic c'tor
    JokerChangeRPS(const PointRPS& rChangePosition, char newRep)
        : _changePosition(rChangePosition)
        , _newRep(newRep)
    {
    }
    
    // d'tor
    ~JokerChangeRPS() {}

    // interface defined functions
    const Point& getJokerChangePosition() const
    {
        return _changePosition;
    }
    char getJokerNewRep() const
    {
        return _newRep;
    }
};

#endif // !__H_JOKER_CHANGE_RPS