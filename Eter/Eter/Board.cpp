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

std::vector<std::vector<char>> Eter::Board::getBoard() const
{
	return m_board;
}

void Eter::Board::setBoard(const std::vector<std::vector<char>>& board)
{
	m_board = board;
}

std::ostream& Eter::operator<<(std::ostream& os, const Board& board)
{
	for (auto& row : board.m_board)
	{
		for (auto& line : row)
		{
			os << line << " ";
		}
		os << std::endl;
	}
	return os;
}
