#include "Board.h"
#include <stdexcept>;

Eter::Board::Board(const GameType& gameType)
{
	Tile defaultTile;
	if (gameType == GameType::Practice)
	{
		m_maxSize = kBOARD_SIZE_PRACTICE;
	}
	else if (gameType == GameType::Duel)
	{
		m_maxSize = kBOARD_SIZE_DUEL;
	}
	else
	{
		throw std::invalid_argument("Invalid game type");
	}
	
	m_board.resize(1);
	m_board[0].resize(1);
}

std::vector<std::vector<std::optional<Tile>>> Eter::Board::GetBoard() const
{
	return m_board;
}

std::vector<std::vector<std::optional<Tile>>>& Eter::Board::GetBoardReference()
{
	return m_board;  // Return a reference to the actual board
}

size_t Eter::Board::GetMaxSize() const
{
	return m_maxSize;
}

size_t Eter::Board::GetCurrentSize() const
{
	return m_board.size();
}

void Eter::Board::SetBoard(const std::vector<std::vector<std::optional<Tile>>>& board)
{
	m_board = board;
}

void Eter::Board::SetTileValue(uint8_t x, uint8_t y, char value)
{
	if (x >= m_board.size() || y >= m_board[x].size())
	{
		throw std::out_of_range("Invalid position");
	}

	m_board[x][y] = Tile{value};

	IncreaseBoardSize();
}

std::optional<Tile>& Eter::Board::operator[](const Position& pos)
{
	return const_cast<std::optional<Tile>&>(std::as_const(*this)[pos]);
}

const std::optional<Tile>& Eter::Board::operator[](const Position& pos) const
{
	const auto& [line, column] = pos;
	if (line < m_board.size() && column < m_board[line].size()) {
		return m_board[line][column];
	}
	throw std::out_of_range("Invalid position");
}

void Eter::Board::IncreaseBoardSize()
{
	if (m_board.size() < m_maxSize && !CheckEmptyTiles())
	{
		m_board.resize(m_board.size() + 1);
		for (auto& line : m_board) {
			line.resize(m_board.size());
		}
	}
	
}

bool Eter::Board::CheckEmptyTiles()
{
	for (auto& row : m_board)
	{
		for (auto& line : row)
		{
			if (!line.has_value())
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
			if (line.has_value()) {
				os << line.value() << " ";
			}
			else
			{
				os << kEMPTY_BOARD_CELL << " ";
			}
		}
		os << std::endl;
	}
	return os;
}
