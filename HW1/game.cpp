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
#include <sstream>
#include <fstream>

using namespace std;

string GenerateOutputResult(Reason p1_r, Reason p2_r, Reason g_r, const string& info, bool is_finished=false) {
    int winner;
    string msg_reason;

    if (is_finished && p1_r == p2_r) {
        // tie at end
        // ? only SUCCESS ??
        winner = 0;
        msg_reason = RSN_MOVE_FILES_NO_WINNER;
    }
    else {
        // only one player won
        winner = p1_r == Reason::SUCCESS ? int(PlayerType::PLAYER_1) : int(PlayerType::PLAYER_2);
        if (p1_r == Reason::LINE_ERROR || p2_r == Reason::LINE_ERROR)
            msg_reason = g_r == Reason::LINE_ERROR ? RSN_BAD_MOVE_FILE_SINGLE + info : RSN_BAD_POSISION_FILE_SINGLE + info;
        else if (p1_r == Reason::NO_FLAGS || p2_r == Reason::NO_FLAGS)
            msg_reason = RSN_ALL_FLAGS_CAPTURED;
        else if (p1_r == Reason::NO_PIECES || p2_r == Reason::NO_PIECES)
            msg_reason = RSN_ALL_PIECES_EATEN;
        if (p1_r == p2_r) {
            winner = 0;
            if (p1_r == Reason::NO_FLAGS) msg_reason = RSN_POSITION_NO_FLAGS;
            if (p1_r == Reason::NO_PIECES) msg_reason = RSN_POSITION_NO_PIECES;
            if (p1_r == Reason::LINE_ERROR) msg_reason = RSN_BAD_POSITION_FILE_DOUBLE + info;
        }
    }
    stringstream ss;
    ss << "Winner: " << winner << endl << "Reason: " << msg_reason << endl << endl;
    return ss.str();
}

void OutputResult(const char* path, const string info, const Board& b) {
    ofstream out;
    try {
		out.open(path, ios::trunc); 
        out << info << b;
        out.close();
	}
	catch (...) {
		cout << "[ERROR] Failed to open/create output file." << endl << "Exiting..." << endl;
	}
}

int main() {
    const char* p1_posfile_path = "./testsTala/case14/player1.rps_board";
    const char* p2_posfile_path = "./testsTala/case14/player2.rps_board";
    const char* p1_movfile_path = "./testsTala/case14/player1.rps_moves";
    const char* p2_movfile_path = "./testsTala/case14/player2.rps_moves";
    const char* outfile_path = "./rps.output";

    string msg; // will have output message from functions
    string msg_reason; // will have reason message
    Reason p1_reason, p2_reason;
    Reason p1_lose, p2_lose;

    // Create player instances
    Player p1(PlayerType::PLAYER_1);
    Player p2(PlayerType::PLAYER_2);
    Board b(DIM_X, DIM_Y);

    // Analyze position files
    PositionFile pos_p1(p1_posfile_path);
    p1_reason = pos_p1.InitializeFile();
    if (p1_reason == Reason::UNKNOWN_ERROR) {
        // handle case: File can't be opened
        cout << "[ERROR] Can't open the position file of PLAYER 1." << endl;
    }
    if (p1_reason == Reason::FILE_ERROR) {
        // handle case: File is empty
        cout << "[INFO] The position file of PLAYER 1 is empty." << endl;
    }
    PositionFile pos_p2(p2_posfile_path);
    p2_reason = pos_p2.InitializeFile();
    if (p2_reason == Reason::UNKNOWN_ERROR) {
        // handle case: File can't be opened
        cout << "[ERROR] Can't open the position file of PLAYER 2." << endl;
    }
    if (p2_reason == Reason::FILE_ERROR) {
        // handle case: File is empty
        cout << "[INFO] The position file of PLAYER 2 is empty." << endl;
    }
    MoveFile mov_p1(p1_movfile_path, &b);
    MoveFile mov_p2(p2_movfile_path, &b);
    p1_reason = mov_p1.InitializeFile();
    if (p1_reason == Reason::UNKNOWN_ERROR) {
        // handle case: File can't be opened
        cout << "[ERROR] Can't open the moves file of PLAYER 1." << endl;
    }
    if (p1_reason == Reason::FILE_ERROR) {
        // handle case: File is empty
        cout << "[INFO] The moves file of PLAYER 1 is empty." << endl;
    }
    p2_reason = mov_p2.InitializeFile();
    if (p2_reason == Reason::UNKNOWN_ERROR) {
        // handle case: File can't be opened
        cout << "[ERROR] Can't open the moves file of PLAYER 2." << endl;
    }
    if (p2_reason == Reason::FILE_ERROR) {
        // handle case: File is empty
        cout << "[INFO] The moves file of PLAYER 2 is empty." << endl;
    }
    if (p1_reason == Reason::UNKNOWN_ERROR || p2_reason == Reason::UNKNOWN_ERROR) {
        cout << "Please fix the mentioned error(s) and retry." << endl;
        return 1;
    }

    // Files loaded fine
    // ? Maybe need to take care of reading error
    p1_reason = pos_p1.ParseFile(&p1, msg);
    if (p1_reason == Reason::NO_FLAGS) {
        // handle case: File error (not enough flags)
        cout << "[INFO] Not enough flags implemented in positioning file for PLAYER 1." << endl;
        // TODO: Decide what to do in this case, leave it or report it now?
    }
    if (p1_reason == Reason::LINE_ERROR) {
        // handle case: Incorrect line
        msg_reason = "player 1 - line " + to_string(pos_p1.GetCurrentLineNumber());
    }
    p2_reason = pos_p2.ParseFile(&p2, msg);
    if (p2_reason == Reason::NO_FLAGS) {
        // handle case: File error (not enough flags)
        cout << "[INFO] Not enough flags implemented in positioning file for PLAYER 2." << endl;
        // TODO: Decide what to do in this case, leave it or report it now?
    }
    if (p2_reason == Reason::LINE_ERROR) {
        // handle case: Incorrect line
        msg_reason = "player 2 - line " + to_string(pos_p2.GetCurrentLineNumber());
    }
    // Check win/lose
    if (p1_reason != Reason::SUCCESS || p2_reason != Reason::SUCCESS) {
        if (p1_reason == p2_reason) {
            msg_reason = "player 1: line " + to_string(pos_p1.GetCurrentLineNumber());
            msg_reason += ", player 2: line " + to_string(pos_p2.GetCurrentLineNumber());
        }
        OutputResult(outfile_path, GenerateOutputResult(p1_reason, p2_reason, Reason::FILE_ERROR, msg_reason), b.Merge(pos_p1.GetBoard()).Merge(pos_p2.GetBoard()));
        return 0;
    }

    if (DEBUG) {cout << "Board 1" << endl; pos_p1.GetBoard().PrettyPrint();}
    if (DEBUG) {cout << "Board 2" << endl; pos_p2.GetBoard().PrettyPrint();}

    // Get combined board 
    b.Merge(pos_p1.GetBoard()).Merge(pos_p2.GetBoard());
    if (DEBUG) {cout << "Board MAIN" << endl; b.PrettyPrint();}

    // -> Check if win/lose
    p1_lose = p1.IsLosing();
    p2_lose = p2.IsLosing();

    // Start parsing moves
    while ((!mov_p1.IsEOF() || !mov_p2.IsEOF()) && (p1_lose == Reason::SUCCESS && p2_lose == Reason::SUCCESS)) {
        // -> Handle moves
        if (!mov_p1.IsEOF()) {
            p1_reason = mov_p1.NextMove(msg);
            if (p1_reason == Reason::UNKNOWN_ERROR) {
                // handle case: File error (while reading the file)
                cout << "[ERROR] Failed while reading moves file for PLAYER 1." << endl << "Please fix the mentioned error(s) and retry." << endl;
                return 1;
            }
            if (p1_reason == Reason::LINE_ERROR) {
                // handle case: Incorrect line
                msg_reason = "player 1 - line " + to_string(mov_p1.GetCurrentLineNumber());
                if (DEBUG) {cout << "Board MAIN" << endl; b.PrettyPrint();}
                OutputResult(outfile_path, GenerateOutputResult(p1_reason,Reason::SUCCESS, Reason::LINE_ERROR, msg_reason), b);
                return 0;
            }
        }
        if (!mov_p2.IsEOF()) {
            p2_reason = mov_p2.NextMove(msg);
            if (p2_reason == Reason::UNKNOWN_ERROR) {
                // handle case: File error (while reading the file)
                cout << "[ERROR] Failed while reading moves file for PLAYER 2." << endl << "Please fix the mentioned error(s) and retry." << endl;
                return 1;
            }
            if (p2_reason == Reason::LINE_ERROR) {
                // handle case: Incorrect line
                msg_reason = "player 2 - line " + to_string(mov_p2.GetCurrentLineNumber());
                if (DEBUG) {cout << "Board MAIN" << endl; b.PrettyPrint();}
                OutputResult(outfile_path, GenerateOutputResult(Reason::SUCCESS,p2_reason, Reason::LINE_ERROR, msg_reason), b);
                return 0;
            }
        }
        p1_lose = p1.IsLosing();
        p2_lose = p2.IsLosing();
        if (DEBUG) {cout << "Board MAIN" << endl; b.PrettyPrint();}
    }
    bool is_finished = mov_p1.IsEOF() && mov_p2.IsEOF();
    OutputResult(outfile_path, GenerateOutputResult(p1_lose,p2_lose, Reason::SUCCESS, msg_reason, is_finished), b);
    if (DEBUG) {cout << "Board MAIN" << endl; b.PrettyPrint();}
    if (DEBUG) cout << "- Piece count=" << Piece::GetPieceCounter() << endl;
}