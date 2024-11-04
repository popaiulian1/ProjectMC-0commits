#include "Board.h"
#include <stdexcept>;

Eter::Board::Board(const GameType& gameType)
{
	Tile defaultTile;
	if (gameType == GameType::Practice)
	{
		m_maxSize = BOARD_SIZE_PRACTICE;
	}
	else if (gameType == GameType::Duel)
	{
		m_maxSize = BOARD_SIZE_DUEL;
	}
	else
	{
		throw std::invalid_argument("Invalid game type");
	}
	
	m_board.resize(1);
	m_board[0].resize(1);
}

std::vector<std::vector<Tile>> Eter::Board::getBoard() const
{
	return m_board;
}

void Eter::Board::setBoard(const std::vector<std::vector<Tile>>& board)
{
	m_board = board;
}

void Eter::Board::setTileValue(uint8_t x, uint8_t y, char value)
{
	if (x >= m_board.size() || y >= m_board[x].size())
	{
		throw std::out_of_range("Invalid position");
	}

	m_board[x][y].setValue(value);
	m_board[x][y].setIsEmpty(false);

	increaseBoardSize();
}

void Eter::Board::increaseBoardSize()
{
	if (m_board.size() < m_maxSize && !checkEmptyTiles())
	{
		m_board.resize(m_board.size() + 1);
		for (auto& line : m_board) {
			line.resize(m_board.size());
		}
	}
	
}

bool Eter::Board::checkEmptyTiles()
{
	for (auto& row : m_board)
	{
		for (auto& line : row)
		{
			if (line.isEmpty())
			{
				return true;
			}
		}
	}
	return false;
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
