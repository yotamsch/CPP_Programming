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
	public:
		// C'tor
		FileHandler(const char* f_path) : _file_path(f_path) {}
		// D'tor
		virtual ~FileHandler() { _f.close(); if (DEBUG) cout << "-> Freed File" << endl; }
		// Utility
		bool IsEOF() { return _f.eof(); }
		bool InitializeFile();
		virtual bool ReadLine(string& line);
};

class PositionFile : public FileHandler {
	private:
		int _dim_x; // will get value in initialization
		int _dim_y; // will get value in initialization
		Board _board;
	public:
		// C'tor
		PositionFile(const char* f_path) : FileHandler(f_path), _board(DIM_X,DIM_Y) {}
		// D'tor
		~PositionFile() {}
		// Get
		Board& GetBoard() { return _board; }
		// Utility
		bool ParseFile(Player* player, string& msg);
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
	bool NextMove(const Player* player, string& msg);
};

#endif