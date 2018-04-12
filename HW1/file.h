#ifndef _H_FILE
#define _H_FILE

#include "board.h"
#include "piece.h"
#include <iostream>
#include <fstream>
#include <string>

#define DIM_X 10
#define DIM_Y 10

#define MSG_INVALID_FILE "The file is not valid."
#define MSG_INVALID_LINE "The line is invalid."
#define MSG_INVALID_POSITIONING "The requested positioning is invalid."
#define MSG_INVALID_MOVE "The requested move is invalid."
#define MSG_NOT_ENOUGH_FLAGS "Flag cout is insufficient."
#define MSG_ERROR_READING_FILE "Error while reading a file."

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
		Reason ParseFile(Player* player, string& msg);
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
	Reason NextMove(string& msg);
};

#endif