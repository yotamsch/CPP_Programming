#include <string>
#include <utility>

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

int main()
{
    RUN_TEST(test1);
    RUN_TEST(test2);
    RUN_TEST(test3);
    RUN_TEST(test4);
    return 0;
}
