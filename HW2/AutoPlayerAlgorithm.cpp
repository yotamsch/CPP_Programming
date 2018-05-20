/**
 * @brief The implementation file of the automatic player (AI) or Rock Paper Scissors game.
 * 
 * @file AutoPlayerAlgorithm.cpp
 * @author Yotam Sechayk
 * @date 2018-05-04
 */
#include "AutoPlayerAlgorithm.h"
#include "GameUtilitiesRPS.h"
#include "JokerChangeRPS.h"
#include "MoveRPS.h"
#include "PieceRPS.h"
#include "PointRPS.h"

#include <algorithm>
#include <random>

// %% INFO %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void AutoPlayerAlgorithm::info::addPiece(AutoPlayerAlgorithm::piece p, int position)
{
    if (p._M_player == NO_PLAYER) {
        return;
    }

    if (p._M_player == this->_M_this_player._M_id) {
        if (p._M_piece == FLAG_CHR || p._M_piece == UNKNOWN_CHR)
            this->_M_this_player._M_flags.insert(position);
        else if (p._M_isJoker)
            this->_M_this_player._M_jokers.insert(position);
        this->_M_this_player._M_pieces.insert(position);
    } else {
        if (p._M_piece == FLAG_CHR || p._M_piece == UNKNOWN_CHR)
            this->_M_other_player._M_flags.insert(position);
        else if (p._M_isJoker)
            this->_M_other_player._M_jokers.insert(position);
        this->_M_other_player._M_pieces.insert(position);
    }
    this->_M_board[position] = p;
}

void AutoPlayerAlgorithm::info::removePiece(int position)
{
    auto& p = this->_M_board[position];
    if (p._M_player == NO_PLAYER)
        return;

    if (p._M_player == this->_M_this_player._M_id) {
        this->_M_this_player._M_flags.erase(position);
        this->_M_this_player._M_jokers.erase(position);
        this->_M_this_player._M_pieces.erase(position);
    } else {
        this->_M_other_player._M_flags.erase(position);
        this->_M_other_player._M_jokers.erase(position);
        this->_M_other_player._M_pieces.erase(position);
    }
    emptyPiece(position);
}

void AutoPlayerAlgorithm::info::removeFlag(int position)
{
    auto& p = this->_M_board[position];
    if (p._M_player == NO_PLAYER)
        return;

    if (p._M_player == this->_M_this_player._M_id) {
        this->_M_this_player._M_flags.erase(position);
    } else {
        this->_M_other_player._M_flags.erase(position);
    }
}

void AutoPlayerAlgorithm::info::emptyPiece(int position)
{
    this->_M_board[position]._M_player = 0;
    this->_M_board[position]._M_isJoker = false;
    this->_M_board[position]._M_piece = '\0';
}

void AutoPlayerAlgorithm::info::updateJoker(int position)
{
    this->_M_board[position]._M_isJoker = true;
}

void AutoPlayerAlgorithm::info::swapPieces(int pos1, int pos2)
{
    auto p1 = this->_M_board[pos1];
    auto p2 = this->_M_board[pos2];

    removePiece(pos1);
    removePiece(pos2);

    addPiece(p1, pos2);
    addPiece(p2, pos1);

    removeFlag(pos1);
    removeFlag(pos2);
}

void AutoPlayerAlgorithm::info::addMove(int from, int to)
{
    this->_M_moves.push_back({ from, to });
}

const AutoPlayerAlgorithm::move& AutoPlayerAlgorithm::info::peekMove() const
{
    return this->_M_moves.back();
}

void AutoPlayerAlgorithm::info::swapPlayers()
{
    // TODO verify it works
    std::swap(_M_this_player, _M_other_player);
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// %% GENERAL %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

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

bool AutoPlayerAlgorithm::isPosValid(int x, int y, int n_x /*= -1*/, int n_y /*= -1*/)
{
    bool result = true;
    if (n_x >= DIM_X || n_x < 0 || n_y >= DIM_Y || n_y < 0) {
        result = false;
    }
    if (n_x != -1 || n_y != -1) {
        if (std::abs(n_x - x) > 1 || std::abs(n_y - y) > 1) {
            result = false;
        }
        if (std::abs(n_x - x) == 1 && std::abs(n_y - y) == 1) {
            result = false;
        }
    }
    return result;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// %% POSITION %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

int AutoPlayerAlgorithm::getPositionNotSelectedYet() const
{
    int vRandPosition = 0;
    do {
        vRandPosition = getRandomPos();
    } while (_info._M_this_player._M_pieces.count(vRandPosition) != 0);
    return vRandPosition;
}

void AutoPlayerAlgorithm::positionPiecesOfType(int vLimit,
    char vType, std::vector<unique_ptr<PiecePosition>>& vectorToFill)
{
    int i;
    int vRandPosition;
    bool vIsJoker = vType == JOKER_CHR;
    std::unique_ptr<PiecePosition> pPiece;

    for (i = 0; i < vLimit; ++i) {
        vRandPosition = getPositionNotSelectedYet();
        vType = vIsJoker ? getRandomJokerRep() : vType;
        pPiece = std::make_unique<PieceRPS>(this->_info._M_this_player._M_id, vIsJoker, vType, PointRPS(getXDim(vRandPosition), getYDim(vRandPosition)));
        vectorToFill.push_back(std::move(pPiece));
        this->_info.addPiece({ this->_info._M_this_player._M_id, vIsJoker, vType }, vRandPosition);
    }
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// %% MOVE %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

int AutoPlayerAlgorithm::getNumOfMovingPieces(AutoPlayerAlgorithm::info& data, AutoPlayerAlgorithm::player_info& player) const
{
    int counter = 0;
    for (auto p : player._M_pieces) {

        switch (data._M_board[p]._M_piece) {
        case FLAG_CHR:
        case BOMB_CHR:
            break;
        default:
            ++counter;
            break;
        }
    }
    return counter;
}

bool AutoPlayerAlgorithm::isMovePossible(AutoPlayerAlgorithm::info& data, int vOriginPos, int vDestPos)
{
    int x, y, n_x, n_y;
    x = getXDim(vOriginPos);
    y = getYDim(vOriginPos);
    n_x = getXDim(vDestPos);
    n_y = getYDim(vDestPos);

    if (!isPosValid(x, y, n_x, n_y)) {
        return false;
    }
    if (data._M_board[vOriginPos]._M_player == data._M_board[vDestPos]._M_player || data._M_board[vOriginPos]._M_piece == FLAG_CHR || data._M_board[vOriginPos]._M_piece == BOMB_CHR) {
        return false;
    }
    return willWinFight(data, vOriginPos, vDestPos);
}

void AutoPlayerAlgorithm::getPossibleMovesForPiece(AutoPlayerAlgorithm::info& data, int vPos, std::vector<int>& rMoves)
{
    int x = getXDim(vPos);
    int y = getYDim(vPos);

    // just in case
    if (data._M_board[vPos]._M_player != this->_info._M_this_player._M_id) {
        return;
    }

    for (int ix = x - 1; ix <= x + 1; ++ix) {
        for (int iy = y - 1; iy <= y + 1; ++iy) {
            if (isMovePossible(data, vPos, getPos(ix, iy))) {
                rMoves.push_back(getPos(ix, iy));
            }
        }
    }
}

bool AutoPlayerAlgorithm::isPieceThreatening(AutoPlayerAlgorithm::info& data, int vPos)
{
    int x, y;
    bool isThreat = false;

    x = getXDim(vPos);
    y = getYDim(vPos);

    for (int ix = x - 1; ix <= x + 1; ++ix) {
        for (int iy = y - 1; iy <= y + 1; ++iy) {
            if (isPosValid(x, y, ix, iy) && data._M_board[getPos(x, y)]._M_player != NO_PLAYER && data._M_board[getPos(ix, iy)]._M_player != NO_PLAYER && data._M_board[getPos(x, y)]._M_player != data._M_board[getPos(ix, iy)]._M_player) {
                if (data._M_other_player._M_flags.count(getPos(ix, iy)) <= 0)
                    isThreat |= willWinFight(data, getPos(x, y), getPos(ix, iy));
                else
                    // if opp piece might be a flag, attempt "eat" it
                    return true;
            }
        }
    }
    return isThreat;
}

bool AutoPlayerAlgorithm::isPieceInDanger(AutoPlayerAlgorithm::info& data, int vPos)
{
    int x, y;
    bool isDanger = false;

    x = getXDim(vPos);
    y = getYDim(vPos);

    for (int ix = x - 1; ix <= x + 1; ++ix) {
        for (int iy = y - 1; iy <= y + 1; ++iy) {
            if (isPosValid(x, y, ix, iy) && data._M_board[getPos(x, y)]._M_player != NO_PLAYER && data._M_board[getPos(x, y)]._M_player != data._M_board[getPos(ix, iy)]._M_player) {
                // if opp piece might be a flag, attempt "eat" it
                if (data._M_other_player._M_flags.count(getPos(ix, iy)) <= 0)
                    isDanger |= !willWinFight(data, getPos(x, y), getPos(ix, iy));
            }
        }
    }
    return isDanger;
}

bool AutoPlayerAlgorithm::willWinFight(AutoPlayerAlgorithm::info& data, int vOriginPos, int vDestPos)
{
    // NOTE: assumes that origin and dest are on the board and correct pieces of two different players
    auto& origPiece = data._M_board[vOriginPos];
    auto& destPiece = data._M_board[vDestPos];
    double chance = (double)std::rand() / (RAND_MAX);

    // checks normal rules and doesn't take chances
    if ((destPiece._M_piece == origPiece._M_piece) || (destPiece._M_piece == ROCK_CHR && origPiece._M_piece == SCISSORS_CHR) || (destPiece._M_piece == SCISSORS_CHR && origPiece._M_piece == PAPER_CHR) || (destPiece._M_piece == PAPER_CHR && origPiece._M_piece == ROCK_CHR) || (destPiece._M_piece == BOMB_CHR && origPiece._M_piece != BOMB_CHR) || (destPiece._M_piece != FLAG_CHR && origPiece._M_piece == FLAG_CHR)) {
        return false;
    }
    if ((destPiece._M_piece == UNKNOWN_CHR || origPiece._M_piece == UNKNOWN_CHR) && chance >= UNKNOWN_WIN_CHANCE) {
        return false;
    }
    return true;
}

float AutoPlayerAlgorithm::calcKNearestDistance(AutoPlayerAlgorithm::info& data, int vFromPlayer, int vPos, int k)
{
    std::vector<float> dist;
    float res = 0.0f;
    int orig_x, orig_y;

    orig_x = getXDim(vPos);
    orig_y = getYDim(vPos);

    for (int pos = 0; pos < DIM_X * DIM_Y; ++pos) {
        if (pos != vPos && data._M_board[pos]._M_player == vFromPlayer && data._M_board[pos]._M_piece != BOMB_CHR && data._M_board[pos]._M_piece != FLAG_CHR) {
            dist.push_back(std::abs(getXDim(pos) - orig_x) + std::abs(getYDim(pos) - orig_y));
        }
    }
    std::sort(dist.begin(), dist.end());
    int i;
    for (i = 0; i < k && i < dist.size(); ++i)
        res += dist[i];

    return res / i;
}

float AutoPlayerAlgorithm::calcPlayerBoardScore(AutoPlayerAlgorithm::info& data)
{
    const int ALL_PIECES_EATEN = 10;
    const int ALL_FLAGS_EATEN = 15;
    const int NUM_OF_PIECES = getNumOfMovingPieces(data, data._M_this_player);

    const int K_PROXIMITY = 0.66f * NUM_OF_PIECES;
    const float PIECES_PARAM = 9.0f;
    const float ENEMY_FLAG_EXIST_PARAM = -2.5f;
    const float DANGER_PARAM = -4.0f / NUM_OF_PIECES;
    const float THREAT_PARAM = 3.0f / NUM_OF_PIECES;
    const float OPP_FLAG_DIST_PARAM = -9.0f / (float)data._M_other_player._M_flags.size();

    float score = 0.0f; // lower is worse heigher is better
    float avg = 0.0f;
    int player = data._M_this_player._M_id;
    int opp = data._M_other_player._M_id;
    int counter;
    std::vector<int> flagSample;

    // number of pieces in danger
    // average L2 ditance between THIS flag to opponent pieces
    for (auto pos : data._M_this_player._M_pieces) {
        switch (data._M_board[pos]._M_piece) {
        case BOMB_CHR:
        case FLAG_CHR:
            break;
        default:
            if (isPieceInDanger(data, pos))
                score += DANGER_PARAM;
            if (isPieceThreatening(data, pos))
                score += THREAT_PARAM;
            break;
        }
    }
    // average L2 distance oponent flag to this player's pieces

    avg = 0.0f;
    counter = 0;

    // advances the pieces towards the "flags". if too many flags, picks a few of them
    if (data._M_other_player._M_flags.size() <= (data._M_other_player._M_pieces.size() + 1) / 2) {
        for (auto pos : data._M_other_player._M_flags) {
            avg += OPP_FLAG_DIST_PARAM * calcKNearestDistance(data, player, pos, K_PROXIMITY);
        }
        if (avg != 0)
            avg /= (float)data._M_other_player._M_flags.size();
    } else {
        for (auto itr = data._M_other_player._M_flags.begin(); counter < (data._M_other_player._M_pieces.size() + 1) / 2;) {
            std::advance(itr, std::rand() % data._M_other_player._M_flags.size());
            if (itr == data._M_other_player._M_flags.end())
                itr = data._M_other_player._M_flags.begin();
            avg += OPP_FLAG_DIST_PARAM * calcKNearestDistance(data, player, *itr, K_PROXIMITY);
            ++counter;
        }
        if (avg != 0)
            avg /= counter;
    }

    score += avg;

    // more existing player pieces is good, encourage "eating"
    score += PIECES_PARAM * (getNumOfMovingPieces(data, data._M_this_player) - getNumOfMovingPieces(data, data._M_other_player));
    // attempt to eat the flags
    score += ENEMY_FLAG_EXIST_PARAM * (float)data._M_other_player._M_flags.size();

    if (data._M_other_player._M_pieces.size() <= 0)
        score += ALL_PIECES_EATEN;
    if (data._M_other_player._M_flags.size() <= 0)
        score += ALL_FLAGS_EATEN;

    return score;
}

void AutoPlayerAlgorithm::performMoveOnBoard(AutoPlayerAlgorithm::info& data, AutoPlayerAlgorithm::move vMove)
{
    data.swapPieces(vMove._M_from, vMove._M_to);
    data.removePiece(vMove._M_from);
}

float AutoPlayerAlgorithm::getScoreForMove(AutoPlayerAlgorithm::info data, AutoPlayerAlgorithm::move vMove)
{
    // just in case
    if (data._M_board[vMove._M_from]._M_player == NO_PLAYER) {
        return 0.0f;
    }

    performMoveOnBoard(data, vMove);
    return calcPlayerBoardScore(data);
}

float AutoPlayerAlgorithm::getScoreForJokerChange(AutoPlayerAlgorithm::info data, AutoPlayerAlgorithm::joker_change vChange)
{
    // just in case
    if (data._M_board[vChange._M_position]._M_player == NO_PLAYER || !data._M_board[vChange._M_position]._M_isJoker) {
        return 0.0f;
    }

    data._M_board[vChange._M_position]._M_piece = vChange._M_new_rep;
    return calcPlayerBoardScore(data);
}

AutoPlayerAlgorithm::move AutoPlayerAlgorithm::getBestMoveForPlayer(AutoPlayerAlgorithm::info& data)
{
    AutoPlayerAlgorithm::move currMove, maxMove;
    std::vector<int> possibleMoves;
    float currScore = 0;
    float maxScore = calcPlayerBoardScore(data);

    // get the best move possible out of all available moves
    for (auto pos : data._M_this_player._M_pieces) {
        getPossibleMovesForPiece(data, pos, possibleMoves);
        for (auto mov : possibleMoves) {
            currMove = { pos, mov };
            // make sure doesn't go back and forth
            if (data._M_moves.size() > 0 && data.peekMove()._M_from == mov && data.peekMove()._M_to == pos)
                continue;
            // will use a copy of the data
            currScore = getScoreForMove(data, currMove);
            if ((maxMove._M_from == -1 && maxMove._M_to == -1 && currScore >= maxScore) || (currScore > maxScore)) {
                maxMove = currMove;
                maxScore = currScore;
            }
        }
        possibleMoves.clear();
    }
    return maxMove;
}

AutoPlayerAlgorithm::joker_change AutoPlayerAlgorithm::getBestJokerChangeForPlayer(AutoPlayerAlgorithm::info& data)
{
    AutoPlayerAlgorithm::joker_change currChange, bestChange;
    float currScore = 0;
    float maxScore = calcPlayerBoardScore(data);
    std::array<char, 4> possibleChanges = { ROCK_CHR, PAPER_CHR, SCISSORS_CHR, BOMB_CHR };

    for (auto pos : data._M_this_player._M_jokers) {
        for (auto change : possibleChanges) {
            currChange = { pos, change };
            currScore = getScoreForJokerChange(data, currChange);
            if (currScore >= maxScore) {
                bestChange = currChange;
                maxScore = currScore;
            }
        }
    }
    return bestChange;
}

// %% INTERFACE %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// Implemented with Smart Random method, which spreads the pices randomly.
// It will not place two pieces in the same spot.
void AutoPlayerAlgorithm::getInitialPositions(int player,
    std::vector<unique_ptr<PiecePosition>>& vectorToFill)
{
    // set the player number
    this->_info._M_this_player._M_id = player;

    // set the seed for the randomization
    this->_seed_value = (unsigned)time(NULL);
    srand(this->_seed_value + player * PRIME_NUMBER);

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

    // go over fights and place/update pieces
    for (auto&& fight : fights) {
        pos = getPos(fight->getPosition().getX(), fight->getPosition().getY());
        // tie or other player won
        if (fight->getWinner() != this->_info._M_this_player._M_id) {
            this->_info.removePiece(pos);
            // another player won
            if (fight->getWinner() != NO_PLAYER) {
                this->_info.addPiece({ fight->getWinner(), false, fight->getPiece(fight->getWinner()) }, pos);
            }
        }
    }
    // mark the rest of the board if a known piece exists
    for (i = 0; i < DIM_X * DIM_Y; ++i) {
        player = b.getPlayer(PointRPS(getXDim(i), getYDim(i)));
        if (player != NO_PLAYER && player != this->_info._M_this_player._M_id) {
            if (this->_info._M_other_player._M_id != player)
                this->_info._M_other_player._M_id = player;
            if (this->_info._M_board[i]._M_player == NO_PLAYER)
                this->_info.addPiece({ player, false, UNKNOWN_CHR }, i);
        }
    }
}

void AutoPlayerAlgorithm::notifyOnOpponentMove(const Move& move)
{
    // save the move into history vector
    this->_info.addMove(getPos(move.getFrom().getX(), move.getFrom().getY()), getPos(move.getTo().getX(), move.getTo().getY()));

    this->_info.updateJoker(this->_info.peekMove()._M_from);
    this->_info.removeFlag(this->_info.peekMove()._M_to);
    this->_info.removeFlag(this->_info.peekMove()._M_from);

    if (this->_info._M_board[this->_info.peekMove()._M_to]._M_player == NO_PLAYER) {
        // clean move, no fight
        this->_info.swapPieces(this->_info.peekMove()._M_from, this->_info.peekMove()._M_to);
    }
}

void AutoPlayerAlgorithm::notifyFightResult(const FightInfo& fightInfo)
{
    int fightPos = getPos(fightInfo.getPosition().getX(), fightInfo.getPosition().getY());

    if (fightPos != this->_info.peekMove()._M_to) {
        // safety check
        return;
    }

    if (fightInfo.getWinner() == NO_PLAYER) {
        // both lost
        this->_info.removePiece(this->_info.peekMove()._M_from);
        this->_info.removePiece(this->_info.peekMove()._M_to);
        return;
    }

    if (fightInfo.getWinner() == this->_info._M_board[this->_info.peekMove()._M_to]._M_player) {
        this->_info.removePiece(this->_info.peekMove()._M_from);
    } else {
        this->_info.swapPieces(this->_info.peekMove()._M_from, this->_info.peekMove()._M_to);
        this->_info.removePiece(this->_info.peekMove()._M_from);
    }
}

unique_ptr<Move> AutoPlayerAlgorithm::getMove()
{
    std::unique_ptr<Move> retMove;
    AutoPlayerAlgorithm::move bestMove;
    AutoPlayerAlgorithm::info data = this->_info;

    bestMove = getBestMoveForPlayer(data);
    if (bestMove._M_from == -1 && bestMove._M_to == -1) {
        return nullptr;
    }

    retMove = std::make_unique<MoveRPS>(PointRPS(getXDim(bestMove._M_from), getYDim(bestMove._M_from)), PointRPS(getXDim(bestMove._M_to), getYDim(bestMove._M_to)));

    // add to history
    this->_info.addMove(bestMove._M_from, bestMove._M_to);
    // perform the move if it's a clean move
    if (this->_info._M_board[bestMove._M_to]._M_player == NO_PLAYER) {
        this->_info.swapPieces(this->_info.peekMove()._M_from, this->_info.peekMove()._M_to);
    }

    // if only one piece "can" be flag, mark it as flag
    if (this->_info._M_other_player._M_flags.size() <= FLAG_LIMIT) {
        for (auto pos : this->_info._M_other_player._M_flags) {
            this->_info._M_board[pos]._M_piece = FLAG_CHR;
        }
    }

    // TODO REMOVE
    prettyPrint();
    std::cout << "\033[0;31m"
              << "move: (" << getXDim(bestMove._M_from) << "," << getYDim(bestMove._M_from) << ") -> (" << getXDim(bestMove._M_to) << "," << getYDim(bestMove._M_to) << ")"
              << "\033[0m" << std::endl;
    // -----------
    return std::move(retMove);
}

unique_ptr<JokerChange> AutoPlayerAlgorithm::getJokerChange()
{
    std::unique_ptr<JokerChange> retJokerChange;
    AutoPlayerAlgorithm::joker_change bestJokerChange;

    bestJokerChange = getBestJokerChangeForPlayer(this->_info);
    if (bestJokerChange._M_position == -1 || this->_info._M_board[bestJokerChange._M_position]._M_piece == bestJokerChange._M_new_rep) {
        return nullptr;
    }

    retJokerChange = std::make_unique<JokerChangeRPS>(PointRPS(getXDim(bestJokerChange._M_position), getYDim(bestJokerChange._M_position)), bestJokerChange._M_new_rep);

    // TODO REMOVE
    std::cout << "\033[0;35m"
              << "joker change: (" << getXDim(bestJokerChange._M_position) << "," << getYDim(bestJokerChange._M_position) << "), [" << this->_info._M_board[bestJokerChange._M_position]._M_piece << "] -> [" << bestJokerChange._M_new_rep << "]"
              << "\033[0m" << std::endl;
    // -----------

    // perform joker change
    this->_info._M_board[bestJokerChange._M_position]._M_piece = bestJokerChange._M_new_rep;

    return std::move(retJokerChange);
}

// FOR DEBUG
// TODO REMOVE
void AutoPlayerAlgorithm::prettyPrint()
{
    std::cout << "player: " << this->_info._M_this_player._M_id << std::endl;
    std::cout << "seed base: " << this->_seed_value << std::endl;
    std::cout << "flags at: ";
    for (int pos : this->_info._M_this_player._M_flags)
        std::cout << "(" << getXDim(pos) << "," << getYDim(pos) << "), ";
    std::cout << std::endl;
    std::cout << "pieces at: ";
    for (int pos : this->_info._M_this_player._M_pieces)
        std::cout << "(" << getXDim(pos) << "," << getYDim(pos) << "), ";
    std::cout << std::endl;
    std::cout << "enemy flags (maybe): ";
    for (int pos : this->_info._M_other_player._M_flags)
        std::cout << "(" << getXDim(pos) << "," << getYDim(pos) << "), ";
    std::cout << std::endl;
    std::cout << "board score: " << calcPlayerBoardScore(this->_info) << std::endl;
    prettyPrintBoard();
}

void AutoPlayerAlgorithm::prettyPrintBoard()
{
    std::cout << "board:" << std::endl;
    int idx = 0, i = 0;
    std::cout << "  ";
    for (i = 0; i < DIM_X; ++i)
        std::cout << " " << i << " ";
    i = 0;
    for (auto piece : this->_info._M_board) {
        if (idx % DIM_X == 0)
            std::cout << std::endl
                      << i++ << " ";
        if (piece._M_player == NO_PLAYER)
            std::cout << "[ ]";
        else if (piece._M_player == this->_info._M_this_player._M_id)
            std::cout << "["
                      << "\033[0;32m" << piece._M_piece << "\033[0m"
                      << "]";
        else
            std::cout << "["
                      << "\033[1;34m" << piece._M_piece << "\033[0m"
                      << "]";
        ++idx;
    }
    std::cout << std::endl;
}
