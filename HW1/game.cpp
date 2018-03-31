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
#include <string>

using namespace std;

int main(int argc, char** argv) {
    Board b2(5, 5);
    cout << "Board b2=("<< b2.getDimentionX() << "," << b2.getDimentionY() << ")" << endl;
    cout << "b2.isPositionValid(1,1)? " << b2.isPositionValid(1,1) << endl;
    cout << "b2.isPositionValid(4,1)? " << b2.isPositionValid(4,1) << endl;
    string msg = "";
    if (!b2.placePiece(PLAYER_1,ROCK,0,0,msg)) cout << msg << endl;
    if (!b2.placePiece(PLAYER_1,PAPER,2,2,msg,true)) cout << msg << endl;
    if (!b2.placePiece(PLAYER_2,SCISSORS, 1,2, msg)) cout << msg << endl;
    if (!b2.placePiece(PLAYER_2,FLAG, 2,8, msg)) cout << msg << endl;
    if (!b2.placePiece(PLAYER_2,SCISSORS, 1,2, msg)) cout << msg << endl;
    b2.prettyPrint();
    cout << "End" << endl;
    return 0;
}