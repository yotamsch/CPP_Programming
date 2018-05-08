/**
 * @brief The implementation file of the automatic player (AI) or Rock Paper Scissors game.
 * 
 * @file AutoPlayerAlgorithm.cpp
 * @author Yotam Sechayk
 * @date 2018-05-04
 */
#include "AutoPlayerAlgorithm.h"
#include "GameUtilitiesRPS.h"
#include "PointRPS.h"
#include "PieceRPS.h"

void AutoPlayerAlgorithm::positionPiecesOfType(int player, int vLimit,
		PieceType vType, std::set<int>& rPositions,
		std::vector<unique_ptr<PiecePosition> >& vectorToFill) {
	// set the player number
	this->_player = player;
	//
	int i;
	int vRandPosition;
	std::unique_ptr<PiecePosition> pPiece;
	bool vIsJoker = vType == PieceType::JOKER;
	for (i = 0; i < vLimit; ++i) {
		vRandPosition = getPositionNotSelectedYet(rPositions);
		vType = vIsJoker ? getRandomJokerPieceType() : vType;
		pPiece = std::make_unique < PieceRPS
				> (vType, vIsJoker, player, PointRPS(
						getXDimensionParameter(vRandPosition),
						getYDimensionParameter(vRandPosition)));
		vectorToFill.push_back(std::move(pPiece));
		rPositions.insert(vRandPosition);
		// add the known board and player pieces
		_knownBoard[vRandPosition] = {player, {vType, vIsJoker}};
		_playerPieces.insert(vRandPosition);
	}
}

// Implemented with Smart Random method, which spreads the pices randomly.
// It will not place two pieces in the same spot.
void AutoPlayerAlgorithm::getInitialPositions(int player,
		std::vector<unique_ptr<PiecePosition>> &vectorToFill) {
	std::set<int> vPositions;

	// set the seed for the randomization
	// srand((unsigned)time(NULL) + player);
	srand(10 * player); // TODO remove after testing

	// insert flags
	positionPiecesOfType(player, FLAG_LIMIT, PieceType::FLAG, vPositions,
			vectorToFill);
	// insert bombs
	positionPiecesOfType(player, BOMB_LIMIT, PieceType::BOMB, vPositions,
			vectorToFill);
	// insert and choose joker
	positionPiecesOfType(player, JOKER_LIMIT, PieceType::JOKER, vPositions,
			vectorToFill);
	// insert rock
	positionPiecesOfType(player, ROCK_LIMIT, PieceType::ROCK, vPositions,
			vectorToFill);
	// insert paper
	positionPiecesOfType(player, PAPAER_LIMIT, PieceType::PAPER, vPositions,
			vectorToFill);
	// insert scissors
	positionPiecesOfType(player, SCISSORS_LIMIT, PieceType::SCISSORS,
			vPositions, vectorToFill);
}

void AutoPlayerAlgorithm::removePlayerPiece(int vPos) {
	this->_playerPieces.erase(vPos);
	this->editPieceInPosition(vPos, (int) PlayerType::NONE, PieceType::NONE,
			false);
}

void AutoPlayerAlgorithm::editPieceInPosition(int vPos, int vPlayer,
		PieceType vType, bool vIsJoker) {
	this->_knownBoard[vPos].first = vPlayer;
	this->_knownBoard[vPos].second.first = vType;
	this->_knownBoard[vPos].second.second = vIsJoker;
}

void AutoPlayerAlgorithm::notifyOnInitialBoard(const Board &b,
		const std::vector<unique_ptr<FightInfo>> &fights) {
	// asume i know the board dimentions
	// go over the board and mark pieces in internal board
	int i, player, pos;
	std::unique_ptr<Point> pp;

	// go over fights and place/update pieces
	for (const auto& fight : fights) {
		pos = getCombinedPosition(fight->getPosition().getX(),
				fight->getPosition().getY());
		// tie or other player won
		if (fight->getWinner() != _player) {
			removePlayerPiece(pos);
			if (fight->getWinner() != 0) {
				editPieceInPosition(pos, fight->getWinner(),
						CharToPieceType(fight->getPiece(fight->getWinner())),
						false);
			}
		}
	}
	// mark the rest of the board if known a piece exists
	for (i = 0; i < DIM_X * DIM_Y; ++i) {
		pp = std::make_unique < PointRPS
				> (getXDimensionParameter(i), getYDimensionParameter(i));
		player = b.getPlayer(*pp);
		if (this->_knownBoard[getCombinedPosition(pp->getX(), pp->getY())].second.first
				== PieceType::NONE) {
			editPieceInPosition(getCombinedPosition(pp->getX(), pp->getY()),
					player, PieceType::UNKNOWN, false);
		}
	}
}

void AutoPlayerAlgorithm::notifyOnOpponentMove(const Move &move) {
}

void AutoPlayerAlgorithm::notifyFightResult(const FightInfo &fightInfo) {
}

unique_ptr<Move> AutoPlayerAlgorithm::getMove() {
}

unique_ptr<JokerChange> AutoPlayerAlgorithm::getJokerChange() {
}

int AutoPlayerAlgorithm::getPositionNotSelectedYet(
		const std::set<int> &rPositions) {
	int vRandPosition = 0;
	do {
		vRandPosition = getRandomPositionOnBoard();
	} while (rPositions.count(vRandPosition) != 0);
	return vRandPosition;
}
