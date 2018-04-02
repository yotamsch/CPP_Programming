/**
 * @brief The main game file. Handles reading files, building board and processing steps. Prints the requested information.
 * 
 * @file game.cpp
 * @author Yotam
 * @date 2018-03-31
 */

#include "board.h"
#include "game.h"
#include "piece.h"
#include "player.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
    Player p1(PlayerType::PLAYER_1);
    Player p2(PlayerType::PLAYER_2);

    if (DEBUG) cout << "1. Counter=" << Piece::GetPieceCounter() << endl;
    Board b1(3, 3);
    if (DEBUG) cout << "2. Counter=" << Piece::GetPieceCounter() << endl;
    Board b2(3, 3);
    
    if (DEBUG) cout << "3. Counter=" << Piece::GetPieceCounter() << endl;
    cout << "Board b1=("<< b1.GetDimentionX() << "," << b1.GetDimentionY() << ")" << endl;
    b1.PrettyPrint();
    cout << "Board b2=("<< b2.GetDimentionX() << "," << b2.GetDimentionY() << ")" << endl;
    b2.PrettyPrint();

    cout << p1 << endl;
    cout << p2 << endl;
    
    string msg = "";
    if (!b1.PlacePiece(&p1, PlayerType::PLAYER_1,PieceType::ROCK,0,0,msg)) cout << msg << endl;
    if (!b1.PlacePiece(&p1, PlayerType::PLAYER_1,PieceType::PAPER,1,1,msg,true)) cout << msg << endl;
    if (!b1.PlacePiece(&p1, PlayerType::PLAYER_1,PieceType::SCISSORS, 0,1, msg)) cout << msg << endl;
    if (!b1.PlacePiece(&p1, PlayerType::PLAYER_1,PieceType::FLAG, 2,1, msg)) cout << msg << endl;
    if (!b1.PlacePiece(&p1, PlayerType::PLAYER_1,PieceType::BOMB, 2,2, msg)) cout << msg << endl;
    if (!b2.PlacePiece(&p2, PlayerType::PLAYER_2,PieceType::ROCK,0,0,msg)) cout << msg << endl;
    if (!b2.PlacePiece(&p2, PlayerType::PLAYER_2,PieceType::PAPER,1,1,msg,true)) cout << msg << endl;
    if (!b2.PlacePiece(&p2, PlayerType::PLAYER_2,PieceType::ROCK, 1,0, msg)) cout << msg << endl;
    if (!b2.PlacePiece(&p2, PlayerType::PLAYER_2,PieceType::SCISSORS, 2,0, msg)) cout << msg << endl;
    if (!b2.PlacePiece(&p2, PlayerType::PLAYER_2,PieceType::FLAG, 2,1, msg)) cout << msg << endl;
    if (!b2.PlacePiece(&p2, PlayerType::PLAYER_2,PieceType::BOMB, 1,2, msg)) cout << msg << endl;
    if (DEBUG) cout << "4. Counter=" << Piece::GetPieceCounter() << endl;
    cout << p1 << endl;
    cout << p2 << endl;
    //
    cout << "BOARD 1" << endl;
    b1.PrettyPrint();
    //
    cout << "BOARD 2" << endl;
    b2.PrettyPrint();
    //
    // The plus (+) operator returns a new heap assigned object, so in order to not lose the object we define b3 as a reference to that object. so we have a name for the returned object.
    Board& b3 = b1 + b2;
    cout << "BOARD 3" << endl;
    b3.PrettyPrint();
    cout << p1 << endl;
    cout << p2 << endl;
    //
    if (DEBUG) cout << "5. Counter=" << Piece::GetPieceCounter() << endl;
    cout << "MovePiece(0,1,1,0)" << endl;
    if (b3.IsMoveLegal(0,1,1,0,msg)) b3.MovePiece(0,1,1,0,msg);
    cout << msg << endl;
    cout << "BOARD 3" << endl;
    b3.PrettyPrint();
    cout << p1 << endl;
    cout << p2 << endl;
    //
    if (DEBUG) cout << "6. Counter=" << Piece::GetPieceCounter() << endl;
    cout << "MovePiece(1,2,1,0)" << endl;
    if (b3.IsMoveLegal(1,2,1,0,msg)) b3.MovePiece(1,2,1,0,msg);
    cout << msg << endl;
    cout << "BOARD 3" << endl;
    b3.PrettyPrint();
    cout << p1 << endl;
    cout << p2 << endl;
    //
    if (DEBUG) cout << "7. Counter=" << Piece::GetPieceCounter() << endl;
    cout << "MovePiece(1,1,2,2)" << endl;
    if (b3.IsMoveLegal(1,1,2,2,msg)) b3.MovePiece(1,1,2,2,msg);
    cout << msg << endl;
    cout << "BOARD 3" << endl;
    b3.PrettyPrint();
    cout << p1 << endl;
    cout << p2 << endl;
    //
    if (DEBUG) cout << "8. Counter=" << Piece::GetPieceCounter() << endl;
    cout << "MovePiece(2,0,2,1)" << endl;
    if (b3.IsMoveLegal(2,0,2,1,msg)) b3.MovePiece(2,0,2,1,msg);
    cout << msg << endl;
    cout << "BOARD 3" << endl;
    b3.PrettyPrint();
    cout << p1 << endl;
    cout << p2 << endl;
    //
    if (DEBUG) cout << "9. Counter=" << Piece::GetPieceCounter() << endl;
    cout << "End" << endl;
    delete &b3;
    return 0;
}