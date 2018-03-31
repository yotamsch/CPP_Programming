/**
 * @brief The main game file. Handles reading files, building board and processing steps. Prints the requested information.
 * 
 * @file game.cpp
 * @author Yotam
 * @date 2018-03-31
 */

#include "board.h"
#include "game.h"
#include "pieces.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
    Board b1(2, 2);
    Board b2(2, 2);
    cout << "Board b2=("<< b2.getDimentionX() << "," << b2.getDimentionY() << ")" << endl;
    cout << "b2.isPositionValid(1,1)? " << b2.isPositionValid(1,1) << endl;
    cout << "b2.isPositionValid(4,1)? " << b2.isPositionValid(4,1) << endl;
    string msg = "";
    if (!b1.placePiece(PLAYER_1,ROCK,0,0,msg)) cout << msg << endl;
    if (!b1.placePiece(PLAYER_1,PAPER,1,1,msg,true)) cout << msg << endl;
    if (!b1.placePiece(PLAYER_1,SCISSORS, 0,1, msg)) cout << msg << endl;
    if (!b2.placePiece(PLAYER_2,ROCK,0,0,msg)) cout << msg << endl;
    if (!b2.placePiece(PLAYER_2,PAPER,1,1,msg,true)) cout << msg << endl;
    if (!b2.placePiece(PLAYER_2,SCISSORS, 1,0, msg)) cout << msg << endl;
    cout << "BOARD 1" << endl;
    b1.prettyPrint();
    cout << "BOARD 2" << endl;
    b2.prettyPrint();
    Board b3 = b1 + b2;
    cout << "BOARD 3" << endl;
    b3.prettyPrint();
    cout << "End" << endl;
    return 0;
}