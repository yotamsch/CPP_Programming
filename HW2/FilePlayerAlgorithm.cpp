#include "FilePlayerAlgorithm.h"
#include "PieceRPS.h"

#include <sstream>
FilePlayerAlgorithm::~FilePlayerAlgorithm(){}

void FilePlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill){    
	for(std::vector<unique_ptr<PiecePosition>>::iterator itr = _initialPositions.begin(); itr != _initialPositions.end(); ++itr){
		vectorToFill.push_back(move(*itr)); //(*itr) is a unique ptr to a PiecePosition
	}
}
/**
 * returns null if moves file of this player ended while the other player still has some moves(if he's a file), or is a auto-player.
 * returns a bad move if there was a bad line in moves file
 * returns a Move otherwise
 */
unique_ptr<Move> FilePlayerAlgorithm::getMove(){
	PointRPS badPointFrom(-1,-1);
	PointRPS badPointTo(-2,-2);
	unique_ptr<MoveRPS> badMove = std::make_unique<MoveRPS>(badPointFrom, badPointTo);
	
	if(isThisTheFirstMove){
		if(InitializeFile(_movesFilePath)!=Reason::SUCCESS){
			//error in opening file
			return std::move(badMove);
		}
		isThisTheFirstMove = false;
	}
	if(ParseMove(_current_player) != Reason::SUCCESS){
		// a bad move in moves-file
		return std::move(badMove);
	}
	//if reached here then it's a success:
	if(IsEOF){
		_jokerChange = nullptr; // same comment below
		return nullptr;// http://moodle.tau.ac.il/mod/forum/discuss.php?d=60137 by the course convention, game should go on with the other player
	}
	return std::move(_nextMove); 
}

unique_ptr<JokerChange> FilePlayerAlgorithm::getJokerChange(){
	return std::move(_jokerChange);
}

/**
 * handles line error and file error the same: inserts a bad piece in pieces vector so that 
 * game manager knows there is something wrong with this player
 * */
void FilePlayerAlgorithm::ManageParsePositionFile(){
	std::unique_ptr<PieceRPS> badPiece = make_unique<PieceRPS>(this->_current_player, false, PieceType::PAPER, PointRPS(-1,-1));
	if(InitializeFile(_positionFilePath) != Reason::SUCCESS){
		//failed to open or find file
		(this->_initialPositions).push_back(move(badPiece));
		return;
	}
	if(ParsePositionFile(_current_player) != Reason::SUCCESS){
		//there is a line error
		(this->_initialPositions).push_back(move(badPiece));
	}
}



Reason FilePlayerAlgorithm::InitializeFile(const char* filePath) { 
	try {
		_f.open(_positionFilePath); 
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
		_initialPositions.push_back(std::move(pCurrPiece));
	}
	if (piece_count[int(PieceType::FLAG)-1] > 0) { //added -1 because Yotam changed the enum's indexing
		return Reason::NO_FLAGS;
	}
	return Reason::SUCCESS;
}



Reason FilePlayerAlgorithm::ParseMove(int player) {
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

		PointRPS pointToChangeJoker(joker_x, joker_y);
		_jokerChange = std::make_unique<JokerChangeRPS>(pointToChangeJoker, new_j_type);
	}
	else{ //no joker change
		_jokerChange = nullptr;
	}
    PointRPS pointFrom(from_x, from_y);
    PointRPS pointTo(to_x, to_y);
	_nextMove = std::make_unique<MoveRPS>(pointFrom, pointTo);
	return Reason::SUCCESS;
}

