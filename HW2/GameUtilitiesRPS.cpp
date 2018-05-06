#include "GameUtilitiesRPS.h"

#include <iostream>
#include <random>
#include <ctime>

void printMessageToScreen(const std::string &&rType, const std::string &&rMsg) { std::cout << rType << " " << rMsg << std::endl; }

int getRandomPositionOnBoard()
{
    const int range_from = 0;
    const int range_to = DIM_X * DIM_Y;
    /*
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int> distr(range_from, range_to);

    return distr(generator);*/
    return rand() % (range_to - range_from) + range_from;
}

int getXDimensionParameter(int vPos) {
    return vPos % DIM_X;
}

int getYDimensionParameter(int vPos) {
    return vPos / DIM_X;
}

int getCombinedPosition(int vX, int vY) {
    return vY * DIM_X + vX;
}

char PieceTypeToChar(PieceType type) {
    switch(type) {
        case PieceType::ROCK:
            return 'R';
        case PieceType::PAPER:
            return 'P';
        case PieceType::SCISSORS:
            return 'S';
        case PieceType::FLAG:
            return 'F';
        case PieceType::BOMB:
            return 'B';
        case PieceType::JOKER:
            return 'J';
        case PieceType::UNKNOWN:
            return '?';
        default:
            return ' ';
    }
}

PieceType CharToPieceType(char chr) {
    switch(chr) {
        case 'R':
            return PieceType::ROCK;
        case 'P':
            return PieceType::PAPER;
        case 'S':
            return PieceType::SCISSORS;
        case 'F':
            return PieceType::FLAG;
        case 'B':
            return PieceType::BOMB;
        case 'J':
            return PieceType::JOKER;
        case '?':
            return PieceType::UNKNOWN;
        default:
            return PieceType::NONE;
    }
}

PieceType getRandomJokerPieceType() {
    PieceType vTypes[] = {PieceType::BOMB, PieceType::ROCK, PieceType::PAPER, PieceType::SCISSORS};
    int choose = rand() % 4;
    return vTypes[choose];
}
