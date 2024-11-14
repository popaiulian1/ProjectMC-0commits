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

Eter::BoardMatrix Eter::Board::GetBoard() const
{
	return m_board;
}

Eter::BoardMatrix& Eter::Board::GetBoardReference()
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

void Eter::Board::SetBoard(const BoardMatrix& board)
{
	m_board = board;
}

void Eter::Board::SetTileValue(const Position& pos, const char& value, const Player& player)
{
	IncreaseBoardSize(pos);
}

std::optional<Eter::Tile>& Eter::Board::operator[](const Position& pos)
{
	return const_cast<std::optional<Tile>&>(std::as_const(*this)[pos]);
}

const std::optional<Eter::Tile>& Eter::Board::operator[](const Position& pos) const
{
	const auto& [line, column] = pos;
	if (line < m_board.size() && column < m_board[line].size()) {
		return m_board[line][column];
	}
	throw std::out_of_range("Invalid position");
}

void Eter::Board::IncreaseBoardSize(const Position& pos)
{
	const auto& [line, column] = pos;
	if (line >= m_board.size() && m_board.size() < m_maxSize)
	{
		m_board.resize(line + 1);
	}
	if (column >= m_board[line].size())
	{
		m_board[line].resize(column + 1);
	}
	if (line < 0 && m_board.size() < m_maxSize) {
		m_board.insert(m_board.begin(), std::vector<std::optional<Tile>>());
	}
	if (column < 0)
	{
		for (auto& row : m_board)
		{
			row.insert(row.begin(), std::optional<Tile>());
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
