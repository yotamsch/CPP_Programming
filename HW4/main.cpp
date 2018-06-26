#include <string>
#include <utility>
#include <stdio.h>
#include <string.h>
#include "ex4_header.h"
#include "unit_test_util.h"

using std::get;
using std::string;

static bool test1()
{
    GameBoard<12, 7, string, 4> board;
    int i = 0;
    for (int row = 0; row < 12; row++) {
        for (int col = 0; col < 7; col++) {
            board.setPiece(row, col, "Piece", i);
            i = (i + 1) % 4;
        }
    }
    int occurence[4] = { 0, 0, 0, 0 };
    for (auto pieceInfo : board) {
        occurence[get<3>(pieceInfo)]++;
    }
    for (int i = 0; i < 4; i++) {
        if (occurence[i] != 21) {
            return false;
        }
    }
    return true;
}

static bool test2()
{
    GameBoard<4, 3, char> board;
    int i = 0;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 3; col++) {
            ASSERT_TRUE(board.setPiece(row, col, 'A'+i, i) == nullptr);
            i = (i + 1) % 2;
        }
    }
    int occurence[2] = { 0, 0 };
	int pos=0;
    for (auto pieceInfo : board) {
        occurence[get<3>(pieceInfo)]++;
		ASSERT_TRUE(get<0>(pieceInfo) == pos / 3);
		ASSERT_TRUE(get<1>(pieceInfo) == pos % 3);
		ASSERT_TRUE(get<2>(pieceInfo) == 'A'+get<3>(pieceInfo));
		++pos;
    }
    for (int i = 0; i < 2; i++) {
        ASSERT_FALSE(occurence[i] != 6);
    }
	auto a = board.getPiece(0,0);
	auto b = board.setPiece(0,0,'C',1);
	ASSERT_TRUE(a->first == b->first && a->second == b->second);
	ASSERT_TRUE(board.getPiece(-1,10) == nullptr);
	ASSERT_TRUE(board.setPiece(-1,10,'C',1) == nullptr);
    return true;
}

static bool test3() {
	GameBoard<4, 3, char> board;
    int i = 0;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 3; col++) {
            ASSERT_TRUE(board.setPiece(row, col, 'A'+i, i) == nullptr);
            i = (i + 1) % 2;
        }
    }
	int counter = 0;
	for (auto pieceInfo : board.allPiecesOfPlayer(0)) {
		ASSERT_TRUE(get<3>(pieceInfo) == 0);
		++counter;
	}
	ASSERT_TRUE(counter == 6);
	counter = 0;
	for (auto pieceInfo : board.allOccureneceOfPiece('A')) {
		ASSERT_TRUE(get<2>(pieceInfo) == 'A');
		++counter;
	}
	ASSERT_TRUE(counter == 6);
	counter = 0;
	for (auto pieceInfo : board.allOccureneceOfPiece('B')) {
		ASSERT_TRUE(get<2>(pieceInfo) == 'B');
		++counter;
	}
	ASSERT_TRUE(counter == 6);
	counter = 0;
	for (auto pieceInfo : board.allOccureneceOfPieceForPlayer('B', 0)) {
		ASSERT_TRUE(get<2>(pieceInfo) != 'C');
		++counter;
	}
	ASSERT_TRUE(counter == 0);
	counter = 0;
	for (auto pieceInfo : board.allOccureneceOfPieceForPlayer('A', 1)) {
		ASSERT_TRUE(get<2>(pieceInfo) != 'C');
		++counter;
	}
	ASSERT_TRUE(counter == 0);
	counter = 0;
	for (auto pieceInfo : board.allOccureneceOfPieceForPlayer('A', 0)) {
		ASSERT_TRUE(get<3>(pieceInfo) == 0);
		ASSERT_TRUE(get<2>(pieceInfo) == 'A');
		++counter;
	}
	ASSERT_TRUE(counter == 6);
	counter = 0;
	for (auto pieceInfo : board.allOccureneceOfPieceForPlayer('B', 1)) {
		ASSERT_TRUE(get<3>(pieceInfo) == 1);
		ASSERT_TRUE(get<2>(pieceInfo) == 'B');
		++counter;
	}
	ASSERT_TRUE(counter == 6);
	int occurence[2] = { 0, 0 };
	int pos=0;
    for (auto pieceInfo : board) {
        occurence[get<3>(pieceInfo)]++;
		ASSERT_TRUE(get<0>(pieceInfo) == pos / 3);
		ASSERT_TRUE(get<1>(pieceInfo) == pos % 3);
		ASSERT_TRUE(get<2>(pieceInfo) == 'A'+get<3>(pieceInfo));
		++pos;
    }
    for (int i = 0; i < 2; i++) {
        ASSERT_FALSE(occurence[i] != 6);
    }
	return true;
}

static bool test4()
{
    GameBoard<4, 3, char> board;

	ASSERT_TRUE(board.setPiece(0, 0, 'A', 1) == nullptr);
	ASSERT_TRUE(board.setPiece(1, 1, 'B', 0) == nullptr);
	ASSERT_TRUE(board.setPiece(2, 2, 'C', 1) == nullptr);
    int occurence[2] = { 0, 0 };
	int pl = 0;
    for (auto pieceInfo : board) {
		pl = get<3>(pieceInfo);
        occurence[pl]++;
    }
    ASSERT_FALSE(occurence[0] != 1);
    ASSERT_FALSE(occurence[1] != 2);

	auto a = board.getPiece(0,0);
	auto b = board.setPiece(0,0,'C',1);
	ASSERT_TRUE(a->first == b->first && a->second == b->second);

	ASSERT_TRUE(board.getPiece(-1,10) == nullptr);
	ASSERT_TRUE(board.setPiece(-1,10,'C',1) == nullptr);
    return true;
}


static bool test7() {
	GameBoard<6, 4, std::string, 3> board;
    int i = 0;
    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 4; col++) {	
			std::string s("shwifty");
			s = s+std::to_string(i);
			ASSERT_TRUE(board.setPiece(row, col, s, i) == nullptr);
      		i = (i + 1) % 3;
        }
    }
		int counter = 0;
	for (auto pieceInfo : board.allPiecesOfPlayer(0)) {
		ASSERT_TRUE(get<3>(pieceInfo) == 0);
		++counter;
	}
	
	ASSERT_TRUE(counter == 8);

	counter = 0;
	for (auto pieceInfo : board.allPiecesOfPlayer(2)) {
		ASSERT_TRUE(get<3>(pieceInfo) == 2);
		++counter;
	}
	ASSERT_TRUE(counter == 8);

	counter = 0;
	for (auto pieceInfo : board.allOccureneceOfPiece("shwifty0")) {
		ASSERT_TRUE(get<2>(pieceInfo).compare("shwifty0") == 0 );
		++counter;
	}

	ASSERT_TRUE(counter == 8);
	counter = 0;
	for (auto pieceInfo : board.allOccureneceOfPiece("shwifty1")) {
		ASSERT_TRUE(get<2>(pieceInfo).compare("shwifty1") == 0 );
		++counter;
	}

	ASSERT_TRUE(counter == 8);
	counter = 0;
	for (auto pieceInfo : board.allOccureneceOfPieceForPlayer("shwifty1", 2)) {
		ASSERT_TRUE(get<2>(pieceInfo).compare("world") != 0);
		ASSERT_TRUE(get<2>(pieceInfo).compare("shwifty1") == 0);
		ASSERT_TRUE(get<3>(pieceInfo) == 2);
		++counter;
	}

	ASSERT_TRUE(counter == 0);
	
	counter = 0;
	for (auto pieceInfo : board.allOccureneceOfPieceForPlayer("A str", 1)) {
		ASSERT_TRUE(get<2>(pieceInfo).compare("C") != 0);
		++counter;
	}
	ASSERT_TRUE(counter == 0);

	counter = 0;
	for (auto pieceInfo : board.allOccureneceOfPieceForPlayer("shwifty0", 0)) {
		ASSERT_TRUE(get<3>(pieceInfo) == 0);
		ASSERT_TRUE(get<2>(pieceInfo).compare("shwifty0") == 0);
		++counter;
	}
	ASSERT_TRUE(counter == 8);
	counter = 0;
	for (auto pieceInfo : board.allOccureneceOfPieceForPlayer("shwifty1", 1)) {
		ASSERT_TRUE(get<3>(pieceInfo) == 1);
		ASSERT_TRUE(get<2>(pieceInfo).compare("shwifty1") == 0);
		++counter;
	}
	ASSERT_TRUE(counter == 8);
	
	int occurence[3] = { 0, 0, 0 };
	int pos=0;
    for (auto pieceInfo : board) {
        occurence[get<3>(pieceInfo)]++;
		ASSERT_TRUE(get<0>(pieceInfo) == pos / 4);
		ASSERT_TRUE(get<1>(pieceInfo) == pos % 4);
		ASSERT_TRUE(get<2>(pieceInfo).compare("shwifty"+std::to_string(get<3>(pieceInfo))) == 0);
		++pos;
    }
    for (int i = 0; i < 3; i++) {
        ASSERT_FALSE(occurence[i] != 8);
    }
	return true;
}

static bool test5()
{
    GameBoard<3, 6, int, 3> board;
    if(board.setPiece(0, 1, 40, 0) != nullptr){}
	if(board.setPiece(0, 2, 40, 0) != nullptr){}
	if(board.setPiece(1, 2, 40, 0) != nullptr){}
	if(board.setPiece(1, 3, 41, 0) != nullptr){}
	if(board.setPiece(2, 4, 42, 0) != nullptr){}
	
	//if(board.setPiece(0, 3, 40, 1) != nullptr){}
	if(board.setPiece(2, 2, 41, 1) != nullptr){}
	if(board.setPiece(1, 4, 42, 1) != nullptr){}
	if(board.setPiece(1, 1, 43, 1) != nullptr){}
	
	if(board.setPiece(0,0 , 40, 2) != nullptr){}
	if(board.setPiece(0, 4, 41, 2) != nullptr){} //when col is 5 - problem
	
    int occurence[3] = { 0, 0, 0 };
    for (auto pieceInfo : board) {
		occurence[get<3>(pieceInfo)]++;
	}
    for (int i = 0; i < 3; i++) {
        if(i==0) ASSERT_FALSE(occurence[i] != 5);
        if(i==1) ASSERT_FALSE(occurence[i] != 3);
        if(i==2) ASSERT_FALSE(occurence[i] != 2);
    }
	auto a = board.getPiece(0,0);
	auto b = board.setPiece(0,0,67,1);
	ASSERT_TRUE(a->first == b->first && a->second == b->second);
	auto c = board.getPiece(1,2);
	auto d = board.setPiece(1,2,56,0);
	ASSERT_TRUE(c->first == d->first && c->second == d->second);

	ASSERT_TRUE(board.getPiece(-1,10) == nullptr);
	ASSERT_TRUE(board.setPiece(-1,10,90,1) == nullptr);
	
    return true;
}



int main()
{
    RUN_TEST(test1);
    RUN_TEST(test2);
    RUN_TEST(test3);
    RUN_TEST(test4);
    RUN_TEST(test5);
    RUN_TEST(test7);
    return 0;
}
