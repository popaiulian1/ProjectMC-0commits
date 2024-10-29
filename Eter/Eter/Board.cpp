#include "Board.h"
#include <stdexcept>;

Eter::Board::Board(const GameType& gameType)
{
	if (gameType == Eter::GameType::Duel)
	{
		m_board.resize(BOARD_SIZE_DUEL);
		for (auto& row : m_board)
		{
			row.resize(BOARD_SIZE_DUEL, '_');
		}
	}
	else if (gameType == Eter::GameType::Practice)
	{
		m_board.resize(BOARD_SIZE_PRACTICE);
		for (auto& row : m_board)
		{
			row.resize(BOARD_SIZE_PRACTICE,'_');
		}
	}
	else
	{
		throw std::invalid_argument("Invalid game type");
	}
}


