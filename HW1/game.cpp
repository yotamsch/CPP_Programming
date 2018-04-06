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
#include "file.h"
#include <iostream>
#include <string>

using namespace std;

void Testing() {
    bool res;
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
    Board b3(3,3);
    b3.Merge(b1).Merge(b2);
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
    //
    cout << "BOARD 1" << endl;
    b1.PrettyPrint();
    //
    cout << "BOARD 2" << endl;
    b2.PrettyPrint();
    //
    cout << "BOARD 3" << endl;
    b3.PrettyPrint();
    //
    cout << p1 << endl;
    cout << p2 << endl;
    //
    if (DEBUG) cout << "9. Counter=" << Piece::GetPieceCounter() << endl;
    cout << "End Board/Piece test\n\n" << endl;
    // File 1
    const char* f_path_1 = "/home/tom/Documents/CPP_Programming_CS3058/HW1/resaurces/ex1_simpletest/player1.rps_board";
    PositionFile f1(f_path_1);
    cout << "FILE 01: Initialize (1=true): " << f1.InitializeFile() << endl;
    res = f1.ParseFile(&p1, msg);
    cout << "FILE 01: File Parsing (1=true): " << res << endl;
    if (!res) cout << "-> Message: " << msg << endl;
    // File 2
    const char* f_path_2 = "/home/tom/Documents/CPP_Programming_CS3058/HW1/resaurces/ex1_simpletest/player2.rps_board";
    PositionFile f2(f_path_2);
    cout << "FILE 02: Initialize (1=true): " << f2.InitializeFile() << endl;
    res = f2.ParseFile(&p2, msg);
    cout << "FILE 02: File Parsing (1=true): " << res << endl;
    if (!res) cout << "-> Message: " << msg << endl;
    Board b_file(DIM_X, DIM_Y);
    b_file.Merge(f1.GetBoard()).Merge(f2.GetBoard());
    //
    cout << "BOARD FILE" << endl;
    b_file.PrettyPrint();
    //
    const char * m_path_1 = "/home/tom/Documents/CPP_Programming_CS3058/HW1/resaurces/ex1_simpletest/player1.rps_moves";
    MoveFile mf1(m_path_1, &b_file);
    cout << "MOVE FILE 01: Initialize (1=true): " << mf1.InitializeFile() << endl;
    //
    const char * m_path_2 = "/home/tom/Documents/CPP_Programming_CS3058/HW1/resaurces/ex1_simpletest/player2.rps_moves";
    MoveFile mf2(m_path_2, &b_file);
    cout << "MOVE FILE 01: Initialize (1=true): " << mf2.InitializeFile() << endl;
    //
    cout << "Moving player 1..." << endl;
    res = mf1.NextMove(&p1, msg);
    if (!res) cout << "-> Message: " << msg << endl;
    cout << "Moving player 2..." << endl;
    res = mf2.NextMove(&p2, msg);
    if (!res) cout << "-> Message: " << msg << endl;
    //
    cout << "BOARD FILE" << endl;
    b_file.PrettyPrint();
    //
    cout << "\nFreeing memory..." << endl;
}

int main(int argc, char** argv) {
    const char* p1_posfile_path = "./resaurces/ex1_simpletest/player1.rps_board";
    const char* p2_posfile_path = "./resaurces/ex1_simpletest/player2.rps_board";
    const char* p1_movfile_path = "./resaurces/ex1_simpletest/player1.rps_moves";
    const char* p2_movfile_path = "./resaurces/ex1_simpletest/player2.rps_moves";

    string msg; // will have output message from functions
    bool p1_lose, p2_lose;

    // Create player instances
    Player p1(PlayerType::PLAYER_1);
    Player p2(PlayerType::PLAYER_2);

    // Analyze position files
    PositionFile pos_p1(p1_posfile_path);
    if (!pos_p1.InitializeFile()) {
        // handle case
        cout << "A1" << endl;
    }
    PositionFile pos_p2(p2_posfile_path);
    if (!pos_p2.InitializeFile()) {
        // handle case
        cout << "A2" << endl;
    }
    if (!pos_p1.ParseFile(&p1, msg)) {
        // handle case
        cout << "B1" << " " << msg << endl;
    }
    if (!pos_p2.ParseFile(&p2, msg)) {
        // handle case
        cout << "B2" << " " << msg << endl;
    }
    // Get combined board 
    Board b(DIM_X, DIM_Y);
    b.Merge(pos_p1.GetBoard()).Merge(pos_p2.GetBoard());
    // -> Check if win/lose
    if (p1.IsLosing()) {
        cout << "C1" << endl;
    }
    if (p2.IsLosing()) {
        cout << "C2" << endl;
    }

    // Start practicing the moves
    MoveFile mov_p1(p1_movfile_path, &b);
    MoveFile mov_p2(p2_movfile_path, &b);

    if (!mov_p1.InitializeFile()) {
        // invalid file case
        cout << "D1" << endl;
    }
    if (!mov_p2.InitializeFile()) {
        // invalid file case
        cout << "D2" << endl;
    }

    while ((!mov_p1.IsEOF() || !mov_p2.IsEOF()) && (!p1_lose && !p2_lose)) {
        b.PrettyPrint();
        p1_lose = false;
        p2_lose = false;
        // -> Handle moves
        if (!mov_p1.IsEOF()) {
            if (!mov_p1.NextMove(&p1, msg)) {
                cout << "E1" << " " << msg << endl;
                p1_lose = true;
            }
        }
        if (!mov_p2.IsEOF()) {
            if (!mov_p2.NextMove(&p2, msg)) {
                cout << "E2" << " " << msg << endl;
                p2_lose = true;
            }
        }
        // -> check win/lose after each move set
        if (p1.IsLosing()) {
            p1_lose = true;
        }
        if (p2.IsLosing()) {
            p2_lose = true;
        }
    }
    if (p1_lose) {
        cout << "player 1 lost" << endl;
    }
    if (p2_lose) {
        cout << "player 2 lost" << endl;
    }
}