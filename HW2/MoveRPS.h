#ifndef __H_MOVE_RPS
#define __H_MOVE_RPS

#include "Move.h"
#include "PointRPS.h"

/**
 * @brief a class inheriting from the abstract class Move,
 * responsible for creating a move, each move consisting from a "souce position" and a "destination position"
 * 
 */
class MoveRPS : public Move {
private:
    PointRPS _fromPoint;
    PointRPS _toPoint;

public:
    // basic c'tor
    MoveRPS(const PointRPS& fromPoint, const PointRPS& toPoint)
        : _fromPoint(fromPoint)
        , _toPoint(toPoint)
    {
    }

    // d'tor
    ~MoveRPS() {}

    // interace defined functions
    /**
     * @brief Gets the source position of this move
     * 
     * @return const Point& - reference to a Point representing the source position
     */
    const Point& getFrom() const
    {
        return _fromPoint;
    }
    /**
     * @brief Gets the destination position of this move
     * 
     * @return const Point& - reference to a Point representing the destination position
     */
    const Point& getTo() const
    {
        return _toPoint;
    }
};

#endif // !__H_MOVE_RPS