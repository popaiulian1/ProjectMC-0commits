#include "Board.h"
#include <stdexcept>;

Eter::Board::Board(const GameType& gameType)
{
	Tile defaultTile;
	if (gameType == Eter::GameType::Duel)
	{
		m_board.resize(BOARD_SIZE_DUEL);
		for (auto& row : m_board)
		{
			row.resize(BOARD_SIZE_DUEL, defaultTile);
		}
	}
	else if (gameType == Eter::GameType::Practice)
	{
		m_board.resize(BOARD_SIZE_PRACTICE);
		for (auto& row : m_board)
		{
			row.resize(BOARD_SIZE_PRACTICE, defaultTile);
		}
	}
	else
	{
		throw std::invalid_argument("Invalid game type");
	}
}

std::vector<std::vector<Tile>> Eter::Board::getBoard() const
{
	return m_board;
}

void Eter::Board::setBoard(const std::vector<std::vector<Tile>>& board)
{
	m_board = board;
}

std::ostream& Eter::operator<<(std::ostream& os, const Board& board)
{
	for (auto& row : board.m_board)
	{
		for (auto& line : row)
		{
			os << line.getValue() << " ";
		}
		os << std::endl;
	}
	return os;
}
