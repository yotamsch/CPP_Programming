/**
 * @brief The implementation file of the automatic player (AI) or Rock Paper Scissors game.
 * 
 * @file AutoPlayerAlgorithm.cpp
 * @author Yotam Sechayk
 * @date 2018-05-04
 */
#include "AutoPlayerAlgorithm.h"
#include "GameUtilitiesRPS.h"
#include "PieceRPS.h"
#include "PointRPS.h"

#include <random>

int AutoPlayerAlgorithm::getRandomPos()
{
    const int range_from = 0;
    const int range_to = DIM_X * DIM_Y;
    return rand() % (range_to - range_from) + range_from;
}

int AutoPlayerAlgorithm::getXDim(int vPos)
{
    return vPos % DIM_X;
}

int AutoPlayerAlgorithm::getYDim(int vPos)
{
    return vPos / DIM_X;
}

int AutoPlayerAlgorithm::getPos(int vX, int vY)
{
    return vY * DIM_X + vX;
}

char AutoPlayerAlgorithm::getRandomJokerPieceType()
{
    char vTypes[] = { BOMB_CHR, ROCK_CHR, PAPER_CHR, SCISSORS_CHR };
    int choose = rand() % 4;
    return vTypes[choose];
}

void AutoPlayerAlgorithm::positionPiecesOfType(int vLimit,
    char vType, std::vector<unique_ptr<PiecePosition>>& vectorToFill)
{
    int i;
    int vRandPosition;
    std::unique_ptr<PiecePosition> pPiece;
    bool vIsJoker = vType == JOKER_CHR;
    for (i = 0; i < vLimit; ++i) {
        vRandPosition = getPositionNotSelectedYet();
        vType = vIsJoker ? getRandomJokerPieceType() : vType;
        pPiece = std::make_unique<PieceRPS>(this->_player, vIsJoker, vType, PointRPS(getXDim(vRandPosition), getYDim(vRandPosition)));
        vectorToFill.push_back(std::move(pPiece));
        // add the known board and player pieces
        _knownBoard[vRandPosition] = { this->_player, vIsJoker, vType };
        _playerPieces.insert(vRandPosition);
    }
}

int AutoPlayerAlgorithm::getPositionNotSelectedYet() const
{
    int vRandPosition = 0;
    do {
        vRandPosition = getRandomPos();
    } while (_playerPieces.count(vRandPosition) != 0);
    return vRandPosition;
}

// Implemented with Smart Random method, which spreads the pices randomly.
// It will not place two pieces in the same spot.
void AutoPlayerAlgorithm::getInitialPositions(int player,
    std::vector<unique_ptr<PiecePosition>>& vectorToFill)
{
    // set the player number
    this->_player = player;

    // set the seed for the randomization
    // TODO place lines agter testing
    // srand((unsigned)time(NULL) + player);
    srand(10 * player);

    // insert flags
    positionPiecesOfType(FLAG_LIMIT, FLAG_CHR, vectorToFill);
    // insert bombs
    positionPiecesOfType(BOMB_LIMIT, BOMB_CHR, vectorToFill);
    // insert and choose joker
    positionPiecesOfType(JOKER_LIMIT, JOKER_CHR, vectorToFill);
    // insert rock
    positionPiecesOfType(ROCK_LIMIT, ROCK_CHR, vectorToFill);
    // insert paper
    positionPiecesOfType(PAPER_LIMIT, PAPER_CHR, vectorToFill);
    // insert scissors
    positionPiecesOfType(SCISSORS_LIMIT, SCISSORS_CHR, vectorToFill);
}

void AutoPlayerAlgorithm::removePlayerPiece(int vPos)
{
    this->_playerPieces.erase(vPos);
    this->editPieceInPosition(vPos, NO_PLAYER);
}

void AutoPlayerAlgorithm::editPieceInPosition(int vPos, int vPlayer,
    char vType /*= '\0'*/, bool vIsJoker /*= false*/)
{
    this->_knownBoard[vPos]._M_player = vPlayer;
    this->_knownBoard[vPos]._M_isJoker = vIsJoker;
    this->_knownBoard[vPos]._M_piece = vType;
}

void AutoPlayerAlgorithm::notifyOnInitialBoard(const Board& b,
    const std::vector<unique_ptr<FightInfo>>& fights)
{
    // asume i know the board dimentions
    // go over the board and mark pieces in internal board
    int i, player, pos;
    std::unique_ptr<Point> pp;

    // go over fights and place/update pieces
    for (auto&& fight : fights) {
        pos = getPos(fight->getPosition().getX(), fight->getPosition().getY());
        // tie or other player won
        if (fight->getWinner() != this->_player) {
            removePlayerPiece(pos);
            if (fight->getWinner() != NO_PLAYER) {
                editPieceInPosition(pos, fight->getWinner(),
                    fight->getPiece(fight->getWinner()));
            }
        }
    }
    // mark the rest of the board if a known piece exists
    for (i = 0; i < DIM_X * DIM_Y; ++i) {
        pp = std::make_unique<PointRPS>(getXDim(i), getYDim(i));
        player = b.getPlayer(*pp);
        if (player != NO_PLAYER && this->_knownBoard[getPos(pp->getX(), pp->getY())]._M_player == NO_PLAYER) {
            editPieceInPosition(i, player,UNKNOWN_CHR);
        }
    }
}

void AutoPlayerAlgorithm::notifyOnOpponentMove(const Move& move)
{
}

void AutoPlayerAlgorithm::notifyFightResult(const FightInfo& fightInfo)
{
}

unique_ptr<Move> AutoPlayerAlgorithm::getMove()
{
}

unique_ptr<JokerChange> AutoPlayerAlgorithm::getJokerChange()
{
}
