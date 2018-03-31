/**
 * @brief The main game file. Handles reading files, building board and processing steps. Prints the requested information.
 * 
 * @file game.cpp
 * @author Yotam
 * @date 2018-03-31
 */
#include "board.h"
#include "pieces.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    Board b1;
    Board b2(3, 3);
    Board b3(2,0);
    cout << "Board b1=("<< b1.getDimentionX() << "," << b1.getDimentionY() << ")" << endl;
    cout << "Board b2=("<< b2.getDimentionX() << "," << b2.getDimentionY() << ")" << endl;
    cout << "b1.isPositionValid(1,1)? " << b1.isPositionValid(1,1) << endl;
    cout << "b1.isPositionValid(1,0)? " << b1.isPositionValid(1,0) << endl;
    cout << "b2.isPositionValid(1,1)? " << b2.isPositionValid(1,1) << endl;
    cout << "b2.isPositionValid(4,1)? " << b2.isPositionValid(4,1) << endl;
    cout << "b2[1][1]=" << b2[1][1] << endl;
    cout << "End" << endl;
    return 0;
}