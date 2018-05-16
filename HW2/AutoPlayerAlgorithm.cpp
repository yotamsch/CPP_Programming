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

/*static*/ int AutoPlayerAlgorithm::getRandomPos()
{
    const int range_from = 0;
    const int range_to = DIM_X * DIM_Y;
    return rand() % (range_to - range_from) + range_from;
}

/*static*/ int AutoPlayerAlgorithm::getXDim(int vPos)
{
    return vPos % DIM_X;
}

/*static*/ int AutoPlayerAlgorithm::getYDim(int vPos)
{
    return vPos / DIM_X;
}

/*static*/ int AutoPlayerAlgorithm::getPos(int vX, int vY)
{
    return vY * DIM_X + vX;
}

/*static*/ char AutoPlayerAlgorithm::getRandomJokerRep()
{
    char vTypes[] = { BOMB_CHR, ROCK_CHR, PAPER_CHR, SCISSORS_CHR };
    int choose = rand() % 4;
    return vTypes[choose];
}

void AutoPlayerAlgorithm::updateEnemyFlagsStat(int vPos)
{
    // TODO verify the condition is correct
    if (this->_knownBoard[vPos]._M_piece == UNKNOWN_CHR && this->_oppFlags.count(vPos) == 0) {
        this->_oppFlags.insert(vPos);
    } else {
        this->_oppFlags.erase(vPos);
    }
}

bool AutoPlayerAlgorithm::isMovePossible(int vOriginPos, int vDestPos)
{
    int x, y, n_x, n_y;
    x = getXDim(vOriginPos);
    y = getYDim(vOriginPos);
    n_x = getXDim(vDestPos);
    n_x = getYDim(vDestPos);

    if (n_x >= DIM_X || n_x < 0 || n_y >= DIM_Y || n_y < 0) {
        return false;
    }
    if (this->_playerPieces.count(vDestPos) != 0) {
        return false;
    }
    if (this->_knownBoard[vDestPos]._M_player == 0) {
        return true;
    }
    return willWinFight(vOriginPos, vDestPos);
}

void AutoPlayerAlgorithm::getPossibleMovesForPiece(int vPos, std::vector<int>& rMoves)
{
    int x, y;

    if (this->_knownBoard[vPos]._M_player != this->_player) {
        return;
    }
    x = getXDim(vPos);
    y = getYDim(vPos);

    // x+1,y
    if (isMovePossible(vPos, getPos(x + 1, y))) {
        rMoves.push_back(getPos(x + 1, y));
    }
    // x-1,y
    if (isMovePossible(vPos, getPos(x - 1, y))) {
        rMoves.push_back(getPos(x - 1, y));
    }
    // x,y+1
    if (isMovePossible(vPos, getPos(x, y + 1))) {
        rMoves.push_back(getPos(x, y + 1));
    }
    // x,y-1
    if (isMovePossible(vPos, getPos(x, y - 1))) {
        rMoves.push_back(getPos(x, y - 1));
    }
}

bool AutoPlayerAlgorithm::isPieceInDanger(int vPos)
{
    int x, y;
    bool isDanger = false;

    if (this->_playerPieces.count(vPos) == 0) {
        return true;
    }

    x = getXDim(vPos);
    y = getYDim(vPos);

    isDanger |= !willWinFight(vPos, getPos(x + 1, y));
    isDanger |= !willWinFight(vPos, getPos(x - 1, y));
    isDanger |= !willWinFight(vPos, getPos(x, y + 1));
    isDanger |= !willWinFight(vPos, getPos(x, y - 1));
    return isDanger;
}

bool AutoPlayerAlgorithm::willWinFight(int vOriginPos, int vDestPos)
{
    char origPiece, destPiece;
    // TODO maybe change this condition or assume it's ok
    if (vOriginPos < 0 || vOriginPos >= this->_knownBoard.size() || vDestPos < 0 || vDestPos >= this->_knownBoard.size()) {
        return true;
    }
    origPiece = this->_knownBoard[vOriginPos]._M_piece;
    destPiece = this->_knownBoard[vDestPos]._M_piece;
    if ((destPiece == origPiece) || (destPiece == ROCK_CHR && origPiece == SCISSORS_CHR) || (destPiece == SCISSORS_CHR && origPiece == PAPER_CHR) || (destPiece == PAPER_CHR && origPiece == ROCK_CHR) || (destPiece == BOMB_CHR && origPiece != BOMB_CHR) || (destPiece != FLAG_CHR && origPiece == FLAG_CHR)) {
        return false;
    }
    return true;
}

float AutoPlayerAlgorithm::calcL2Distance(int vPlayer, int vPos) {
    float res = 0;
    int orig_x,orig_y;

    orig_x = getXDim(vPos);
    orig_y = getYDim(vPos);

    for (int pos = 0; pos < DIM_X * DIM_Y; ++pos) {
        if (this->_knownBoard[pos]._M_player != 0 && this->_knownBoard[pos]._M_player != vPlayer) {
            res += std::pow(getXDim(pos) - orig_x, 2.0f) + std::pow(getYDim(pos) - orig_y, 2.0f);
        }
    }
    return res;
}

float AutoPlayerAlgorithm::calcPlayerBoardScore(int vPlayer, std::vector<AutoPlayerAlgorithm::piece>& rBoard) {
    const float DANGER_PARAM = 120.0f;
    const float OPP_FLAG_DIST_PARAM = 85.0f;
    const float THIS_FLAG_DIST_PARAM = -100.0f; // far (large) is good

    float score = 0; // higher is worse, lower is better

    std::set<int>& playerSet = vPlayer == this->_player ? this->_playerPieces : this->_oppPieces;
    std::set<int>& oppFlags = vPlayer == this->_player ? this->_oppFlags : this->_playerFlags;

    // number of pieces in danger
    // average L2 ditance between THIS flag to opponent pieces
    for (auto pos : playerSet) {
        switch (this->_knownBoard[pos]._M_piece)
        {
            case BOMB_CHR:
                break;
            case FLAG_CHR:
                score += THIS_FLAG_DIST_PARAM * calcL2Distance(vPlayer, pos);
            default:
                score += DANGER_PARAM * isPieceInDanger(pos);
                break;
        }
    }
    // average L2 distance oponent flag to this player's pieces
    for (auto pos : oppFlags) {
        score += OPP_FLAG_DIST_PARAM * calcL2Distance(this->_knownBoard[pos]._M_player, pos);
    }
    // * maybe more?

    return score;
}

// TODO create the recursion algorithm to find the best move

void AutoPlayerAlgorithm::positionPiecesOfType(int vLimit,
    char vType, std::vector<unique_ptr<PiecePosition>>& vectorToFill)
{
    int i;
    int vRandPosition;
    std::unique_ptr<PiecePosition> pPiece;
    bool vIsJoker = vType == JOKER_CHR;
    for (i = 0; i < vLimit; ++i) {
        vRandPosition = getPositionNotSelectedYet();
        vType = vIsJoker ? getRandomJokerRep() : vType;
        pPiece = std::make_unique<PieceRPS>(this->_player, vIsJoker, vType, PointRPS(getXDim(vRandPosition), getYDim(vRandPosition)));
        vectorToFill.push_back(std::move(pPiece));
        // add the known board and player pieces
        this->_knownBoard[vRandPosition] = { this->_player, vIsJoker, vType };
        _playerPieces.insert(vRandPosition);
        if (vType == FLAG_CHR) {
            _playerFlags.insert(vRandPosition);
        }
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

void AutoPlayerAlgorithm::removePiece(int vPos)
{
    if (this->_knownBoard[vPos]._M_player == this->_player) {
        if (this->_knownBoard[vPos]._M_piece == FLAG_CHR) {
            this->_playerFlags.erase(vPos);
        }
        this->_playerPieces.erase(vPos);
    } else {
        if (this->_knownBoard[vPos]._M_piece == FLAG_CHR) {
            this->_oppFlags.erase(vPos);
        }
        this->_oppPieces.erase(vPos);
    }
    this->editPieceInPosition(vPos, NO_PLAYER);
}

void AutoPlayerAlgorithm::editPieceInPosition(int vPos, int vPlayer,
    char vType /*= '\0'*/, bool vIsJoker /*= false*/)
{
    this->_knownBoard[vPos]._M_player = vPlayer;
    this->_knownBoard[vPos]._M_isJoker = vIsJoker;
    this->_knownBoard[vPos]._M_piece = vType;
}

// Implemented with Smart Random method, which spreads the pices randomly.
// It will not place two pieces in the same spot.
void AutoPlayerAlgorithm::getInitialPositions(int player,
    std::vector<unique_ptr<PiecePosition>>& vectorToFill)
{
    // set the player number
    this->_player = player;

    // set the seed for the randomization
    // TODO replace lines after testing
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
            removePiece(pos);
            // another player won
            if (fight->getWinner() != NO_PLAYER) {
                editPieceInPosition(pos, fight->getWinner(),
                    fight->getPiece(fight->getWinner()));
                this->_oppPieces.insert(pos);
            }
        }
    }
    // mark the rest of the board if a known piece exists
    for (i = 0; i < DIM_X * DIM_Y; ++i) {
        pp = std::make_unique<PointRPS>(getXDim(i), getYDim(i));
        player = b.getPlayer(*pp);
        if (player != NO_PLAYER && this->_knownBoard[getPos(pp->getX(), pp->getY())]._M_player == NO_PLAYER) {
            editPieceInPosition(i, player, UNKNOWN_CHR);
            updateEnemyFlagsStat(i);
        }
    }
}

void AutoPlayerAlgorithm::notifyOnOpponentMove(const Move& move)
{
    // save the move into history vector
    AutoPlayerAlgorithm::move opMove = { getPos(move.getFrom().getX(), move.getFrom().getY()), getPos(move.getTo().getX(), move.getTo().getY()) };
    this->_oppMoveHistory.push_back(opMove);

    updateEnemyFlagsStat(opMove._M_from);

    if (this->_playerPieces.count(opMove._M_to) == 0) {
        // clean move, no fight
        this->_knownBoard[opMove._M_to] = this->_knownBoard[opMove._M_from];
        this->editPieceInPosition(opMove._M_from, NO_PLAYER);
    }
}

void AutoPlayerAlgorithm::notifyFightResult(const FightInfo& fightInfo)
{
    AutoPlayerAlgorithm::move lastMove;
    int fightPos;

    fightPos = getPos(fightInfo.getPosition().getX(), fightInfo.getPosition().getY());
    lastMove = this->_oppMoveHistory[this->_oppMoveHistory.size() - 1];

    if (fightPos != lastMove._M_to) {
        // safety check
        return;
    }

    if (fightInfo.getWinner() == NO_PLAYER) {
        // both lost
        removePiece(lastMove._M_from);
        removePiece(lastMove._M_to);
    } else if (fightInfo.getWinner() == this->_player) {
        // this player won, remove enemy piece
        removePiece(lastMove._M_from);
    } else {
        // enemy won, assumes only single enemy
        if (this->_knownBoard[lastMove._M_from]._M_piece != UNKNOWN_CHR && this->_knownBoard[lastMove._M_from]._M_piece != fightInfo.getPiece(fightInfo.getWinner())) {
            // discovered joker
            this->_knownBoard[lastMove._M_from]._M_isJoker = true;
        }
        removePiece(lastMove._M_to);
        editPieceInPosition(lastMove._M_to, fightInfo.getWinner(), fightInfo.getPiece(fightInfo.getWinner()), this->_knownBoard[lastMove._M_from]._M_isJoker);
        editPieceInPosition(lastMove._M_from, NO_PLAYER);
    }
}

unique_ptr<Move> AutoPlayerAlgorithm::getMove()
{
}

unique_ptr<JokerChange> AutoPlayerAlgorithm::getJokerChange()
{
}
