
#ifndef __H_JOKER_CHANGE_RPS
#define __H_JOKER_CHANGE_RPS

#include "JokerChange.h"
#include "PointRPS.h"
/**
 * @brief a class inheriting from the abstract class JokerChange. Holds information about joker change
 * 
 */
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

    /**
     * @brief Get the Joker Change Position
     * 
     * @return const Point& - the point/position in which a joker wants to change its representation
     */
    const Point& getJokerChangePosition() const
    {
        return _changePosition;
    }

    /**
     * @brief Get the joker's new desired representation
     * 
     * @return char - joker's new char representation
     */
    char getJokerNewRep() const
    {
        return _newRep;
    }
};

#endif // !__H_JOKER_CHANGE_RPS