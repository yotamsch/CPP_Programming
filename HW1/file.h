#ifndef _H_FILE
#define _H_FILE

#include "board.h"
#include "piece.h"
#include "game.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class FileHandler {
	private:
		const char* _file_path;
		ifstream _f;
		int _current_line;
	public:
		// C'tor
		FileHandler(const char* f_path) : _file_path(f_path), _current_line(0) {}
		// D'tor
		virtual ~FileHandler() { _f.close(); }
		// Get
		int GetCurrentLineNumber() { return _current_line; }
		// Utility
		bool IsEOF() { return _f.eof(); }
		Reason InitializeFile();
		virtual Reason ReadLine(string& line);
};

class PositionFile : public FileHandler {
	private:
		Board _board;
	public:
		// C'tor
		PositionFile(const char* f_path) : FileHandler(f_path), _board(DIM_X,DIM_Y) {}
		// D'tor
		~PositionFile() {}
		// Get
		Board& GetBoard() { return _board; }
		// Utility
		Reason ParseFile(Player* player);
};

class MoveFile : public FileHandler {
	private:
		Board* _board;
	public:
	// C'tor
	MoveFile(const char* f_path, Board* board) : FileHandler(f_path), _board(board) {}
	// D'tor
	~MoveFile() {}
	// Utility
	Reason NextMove(Player* player);
};

#endif