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
    Board b1(3, 3);
    Board b2(3, 3);
    cout << "Board b2=("<< b2.GetDimentionX() << "," << b2.GetDimentionY() << ")" << endl;
    cout << "b2.IsPositionValid(1,1)? " << b2.IsPositionValid(1,1) << endl;
    cout << "b2.IsPositionValid(4,1)? " << b2.IsPositionValid(4,1) << endl;
    string msg = "";
    if (!b1.PlacePiece(PlayerType::PLAYER_1,PieceType::ROCK,0,0,msg)) cout << msg << endl;
    if (!b1.PlacePiece(PlayerType::PLAYER_1,PieceType::PAPER,1,1,msg,true)) cout << msg << endl;
    if (!b1.PlacePiece(PlayerType::PLAYER_1,PieceType::SCISSORS, 0,1, msg)) cout << msg << endl;
    if (!b1.PlacePiece(PlayerType::PLAYER_1,PieceType::FLAG, 2,1, msg)) cout << msg << endl;
    if (!b1.PlacePiece(PlayerType::PLAYER_1,PieceType::BOMB, 2,2, msg)) cout << msg << endl;
    if (!b2.PlacePiece(PlayerType::PLAYER_2,PieceType::ROCK,0,0,msg)) cout << msg << endl;
    if (!b2.PlacePiece(PlayerType::PLAYER_2,PieceType::PAPER,1,1,msg,true)) cout << msg << endl;
    if (!b2.PlacePiece(PlayerType::PLAYER_2,PieceType::ROCK, 1,0, msg)) cout << msg << endl;
    if (!b2.PlacePiece(PlayerType::PLAYER_2,PieceType::SCISSORS, 2,0, msg)) cout << msg << endl;
    if (!b2.PlacePiece(PlayerType::PLAYER_2,PieceType::FLAG, 2,1, msg)) cout << msg << endl;
    if (!b2.PlacePiece(PlayerType::PLAYER_2,PieceType::BOMB, 1,2, msg)) cout << msg << endl;
    //
    cout << "BOARD 1" << endl;
    b1.PrettyPrint();
    //
    cout << "BOARD 2" << endl;
    b2.PrettyPrint();
    //
    Board b3 = b1 + b2;
    cout << "BOARD 3" << endl;
    b3.PrettyPrint();
    //
    cout << "MovePiece(0,1,1,0)" << endl;
    b3.MovePiece(0,1,1,0,msg);
    cout << msg << endl;
    cout << "BOARD 3" << endl;
    b3.PrettyPrint();
    //
    cout << "MovePiece(1,2,1,0)" << endl;
    b3.MovePiece(1,2,1,0,msg);
    cout << msg << endl;
    cout << "BOARD 3" << endl;
    b3.PrettyPrint();
    //
    cout << "MovePiece(1,2,2,2)" << endl;
    b3.MovePiece(1,2,2,2,msg);
    cout << msg << endl;
    cout << "BOARD 3" << endl;
    b3.PrettyPrint();
    //
    cout << "MovePiece(2,0,2,1)" << endl;
    b3.MovePiece(2,0,2,1,msg);
    cout << msg << endl;
    cout << "BOARD 3" << endl;
    b3.PrettyPrint();
    //
    cout << "End" << endl;
    return 0;
}