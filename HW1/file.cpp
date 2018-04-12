
#include "file.h"
#include "piece.h"
#include "board.h"
#include "game.h"
#include <string>
#include <sstream>
#include <vector>

using namespace std;

string& TrimLine(string& s, const string& delmiters="\f\n\r\t\v") {
	return s.erase(s.find_last_not_of(delmiters) + 1).erase(0, s.find_first_not_of(delmiters));	
}

vector<string> SplitLine(const string& s, const char delimiter) {
	vector<string> result;
	stringstream ss(s);
	string word;
	while (getline(ss, word, delimiter)) {
		result.push_back(word);
	}
	return result;
}

Reason FileHandler::InitializeFile() { 
	try {
		_f.open(_file_path); 
	}
	catch (...) {
		return Reason::UNKNOWN_ERROR;
	}
	string line;
	if (_f.is_open()) {
		while (!_f.eof()) {
			getline(_f, line);
			if (TrimLine(line).size() > 0) {
				_f.seekg(0, ios::beg);
				_current_line = 0;
				return Reason::SUCCESS;
			}
		}
	} else {
		return Reason::UNKNOWN_ERROR;
	}
	return Reason::FILE_ERROR;
}

Reason FileHandler::ReadLine(string& line) {
	try {
		if (!_f.eof()) {
			do {
				getline(_f, line);
				line = TrimLine(line);
				++_current_line;
			} while (line.size() <= 0 && !_f.eof());
		}
	} catch (...) {
		return Reason::UNKNOWN_ERROR;
	}
	/*if (line.size() == 0 && _f.eof()) {
		return Reason::FILE_ERROR;
	}*/
	return Reason::SUCCESS;
}

Reason PositionFile::ParseFile(Player* player, string& msg) {
	const char delim = ' ';
	// counting the pieces [0]=rock, [1]=paper, [2]=scissors,
	// [3]=flag, [4]=bonb, [5]=scissors
	int piece_count[] = {R, P, S, F, B, J};
	PieceType piece_type;
	bool is_joker;
	int x, y;

	string line;
	
	while(!IsEOF()) {
		is_joker = false;
		if (ReadLine(line) != Reason::SUCCESS ) {
			return Reason::UNKNOWN_ERROR;
		}
		vector<string> s_line = SplitLine(line, delim);
		if (s_line.size() == 0) {
			// empty line, continues
			continue;
		}
		if (s_line.size() < 3) {
			msg = MSG_INVALID_LINE;
			return Reason::LINE_ERROR;
		}
		piece_type = CharToPieceType(s_line[0][0]);
		if (s_line[0].size() != 1 || piece_type == PieceType::NONE) {
			msg = MSG_INVALID_LINE;
			return Reason::LINE_ERROR;
		}
		try {
			x = stoi(s_line[2]) - 1;
			y = stoi(s_line[1]) - 1;
		} catch (...) {
			// number conversion error
			msg = MSG_INVALID_LINE;
			return Reason::LINE_ERROR;
		}
		--piece_count[int(piece_type)];
		if (piece_type == PieceType::JOKER){
			// joker piece
			is_joker = true;
			if (s_line.size() != 4 || s_line[3].size() != 1) {
				msg = MSG_INVALID_LINE;
				return Reason::LINE_ERROR;
			}
			piece_type = CharToPieceType(s_line[3][0]);
		}
		if (piece_count[int(piece_type)] < 0) {
			msg = MSG_INVALID_FILE;
			return Reason::LINE_ERROR;
		}
		if (!_board.PlacePiece(player, piece_type, x, y, msg, is_joker)) {
			return Reason::LINE_ERROR;
		}
	}
	if (piece_count[int(PieceType::FLAG)] > 0) {
		msg = MSG_NOT_ENOUGH_FLAGS;
		return Reason::NO_FLAGS;
	}
	return Reason::SUCCESS;
}

Reason MoveFile::NextMove(string& msg) {
	// get a move from the file and parse it
	const char delim = ' ';
	const char* joker_str = "J:";
	string line;
	int from_x, from_y, to_x, to_y;
	bool is_j_change = false;
	int joker_x, joker_y;
	PieceType new_j_type;

	if (ReadLine(line) == Reason::UNKNOWN_ERROR) {
		msg = MSG_ERROR_READING_FILE;
		return Reason::UNKNOWN_ERROR;
	}
	vector<string> s_line = SplitLine(line, delim)
	;
	if (s_line.size() == 0) return Reason::SUCCESS;

	if (s_line.size() < 4) {
		msg = MSG_INVALID_LINE;
		return Reason::LINE_ERROR;
	}
	if (s_line.size() == 8) {
		if (s_line[4].compare(joker_str) != 0) {
			msg = MSG_INVALID_LINE;
			return Reason::LINE_ERROR;
		}
		is_j_change = true;
	}
	try {
		from_x = stoi(s_line[1]) - 1;
		from_y = stoi(s_line[0]) - 1;
		to_x = stoi(s_line[3]) - 1;
		to_y = stoi(s_line[2]) - 1;
	} catch (...) {
		// number conversion error
		msg = MSG_INVALID_LINE;
		return Reason::LINE_ERROR;
	}
	if (is_j_change) {
		if (s_line.size() != 8 || s_line[7].size() != 1) {
			msg = MSG_INVALID_LINE;
			return Reason::LINE_ERROR;
		}
		try {
			joker_x = stoi(s_line[6]) - 1;
			joker_y = stoi(s_line[5]) - 1;
		} catch (...) {
			// number conversion error
			msg = MSG_INVALID_LINE;
			return Reason::LINE_ERROR;
		}
		new_j_type = CharToPieceType(s_line[7][0]);
	}
	if (!_board->MovePiece(from_x, from_y, to_x, to_y, msg)) {
		return Reason::LINE_ERROR;
	}
	if (is_j_change && !_board->ChangeJoker(joker_x, joker_y, new_j_type, msg)) {
		return Reason::LINE_ERROR;
	}
	return Reason::SUCCESS;
}