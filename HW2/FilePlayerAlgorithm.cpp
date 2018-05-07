#include "FilePlayerAlgorithm.h"
#include "PieceRPS.h"

#include <sstream>
FilePlayerAlgorithm::~FilePlayerAlgorithm(){}

void FilePlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill){
    if(player==1){
        for(std::vector<unique_ptr<PiecePosition>>::iterator itr = _initialPositionsP1.begin(); itr != _initialPositionsP1.end(); ++itr){
            vectorToFill.push_back(move(*itr)); //(*itr) is a unique ptr to a PiecePosition
        }
    }
    if(player==2){
        for(std::vector<unique_ptr<PiecePosition>>::iterator itr = _initialPositionsP2.begin(); itr != _initialPositionsP2.end(); ++itr){
            vectorToFill.push_back(move(*itr)); //(*itr) is a unique ptr to a PiecePosition
        }
    }
}

unique_ptr<Move> FilePlayerAlgorithm::getMove(){}
unique_ptr<JokerChange> FilePlayerAlgorithm::getJokerChange(){}


string& TrimLine(string& s, const string& delmiters=" \f\n\r\t\v") {
	return s.erase(s.find_last_not_of(delmiters) + 1).erase(0, s.find_first_not_of(delmiters));	
}

vector<string> SplitLine(const string& s, const char delimiter) {
	vector<string> result;
	stringstream ss(s);
	string word;
	while (std::getline(ss, word, delimiter)) {
		if (word.size() > 0)
			result.push_back(TrimLine(word));
	}
	return result;
}

Reason FilePlayerAlgorithm::ReadLine(string& line) {
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
	return Reason::SUCCESS;
}



Reason FilePlayerAlgorithm::ParsePositionFile(int player) {
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
			return Reason::LINE_ERROR;
		}
		piece_type = CharToPieceType(s_line[0][0]);
		if (s_line[0].size() != 1 || piece_type == PieceType::NONE) {
			return Reason::LINE_ERROR;
		}
		try {
			x = stoi(s_line[2]) - 1;
			y = stoi(s_line[1]) - 1;
		} catch (...) {
			// number conversion error
			return Reason::LINE_ERROR;
		}
		--piece_count[int(piece_type)-1];//added -1 because Yotam changed the enum's indexing 
		if (piece_type == PieceType::JOKER){
			// joker piece
			is_joker = true;
			if (s_line.size() != 4 || s_line[3].size() != 1) {
				return Reason::LINE_ERROR;
			}
			piece_type = CharToPieceType(s_line[3][0]);
		}
		if (piece_count[int(piece_type)-1] < 0) {//added -1 because Yotam changed the enum's indexing
			return Reason::LINE_ERROR;
		}
        PointRPS currPosition(x,y);
        unique_ptr<PieceRPS> pCurrPiece = std::make_unique<PieceRPS>(player, is_joker, piece_type, currPosition);
        if(player==1)_initialPositionsP1.push_back(std::move(pCurrPiece));
        if(player==2)_initialPositionsP2.push_back(std::move(pCurrPiece));
	}
	if (piece_count[int(PieceType::FLAG)-1] > 0) { //added -1 because Yotam changed the enum's indexing
		return Reason::NO_FLAGS;
	}
	return Reason::SUCCESS;
}



Reason FilePlayerAlgorithm::ParseMoveFile(int player) {
	// get a move from the file and parse it
	const char delim = ' ';
	const char* joker_str = "J:";
	string line;
	int from_x, from_y, to_x, to_y;
	bool is_j_change = false;
	int joker_x, joker_y;
	PieceType new_j_type;

	if (ReadLine(line) == Reason::UNKNOWN_ERROR) {
		return Reason::UNKNOWN_ERROR;
	}
	vector<string> s_line = SplitLine(line, delim);

	if (s_line.size() == 0) return Reason::SUCCESS;

	if (s_line.size() < 4) {
		return Reason::LINE_ERROR;
	}
	if (s_line.size() >= 8) {
		if (s_line[4].compare(joker_str) != 0) {
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
		return Reason::LINE_ERROR;
	}
	if (is_j_change) {
		if (s_line.size() != 8 || s_line[7].size() != 1) {
			return Reason::LINE_ERROR;
		}
		try {
			joker_x = stoi(s_line[6]) - 1;
			joker_y = stoi(s_line[5]) - 1;
		} catch (...) {
			// number conversion error
			return Reason::LINE_ERROR;
		}
		new_j_type = CharToPieceType(s_line[7][0]);
	}
    PointRPS pointFrom(from_x, from_y);
    PointRPS pointTo(to_x, to_y);
    
    _nextMoveP1 = std::make_unique(pointFrom, pointTo);

	if (is_j_change && !_board->ChangeJoker(player->GetType(), joker_x, joker_y, new_j_type)) {
		return Reason::LINE_ERROR;
	}
	return Reason::SUCCESS;
}