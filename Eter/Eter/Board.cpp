#include "Board.h"
#include "Piece.h"
#include <stdexcept>;
#include <iostream>

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

Eter::Board& Eter::Board::operator=(const Board& other)
{
	if (this != &other)
	{
		m_board = other.m_board;
		m_maxSize = other.m_maxSize;
	}
	return *this;
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

void Eter::Board::SetTileValue(const Position& pos, const char& value, const std::string& playerName)
{

	const auto& [line, column] = pos;

	if (line < 0 || column < 0) {
		IncreaseBoardForNegativeIndexes({line, column});
		std::cout << "\n-------------------------------\n" << *this << "\n-------------------------------\n";
	}
	if (line > (int)m_board.size()-1 && m_board.size() < m_maxSize) {
		m_board.insert(m_board.end(), std::vector<std::optional<Tile>>(m_board.size()));
		std::cout << "\n-------------------------------\n"  << *this << "\n-------------------------------\n";
	}
	if (column > (int)m_board[0].size()-1 && m_board[0].size() < m_maxSize) {
		for (auto& row : m_board) {
			row.insert(row.end(), std::optional<Tile>());
		}
		std::cout << "\n-------------------------------\n" << *this << "\n-------------------------------\n";
	}

	int8_t adjustedLine = line, adjustedColumn = column;

	adjustedLine < 0 ? adjustedLine += 1 : adjustedLine;
	adjustedColumn < 0 ? adjustedColumn += 1 : adjustedColumn;

	if (adjustedLine > m_board.size() || adjustedColumn > m_board[0].size())
	{
		throw std::out_of_range("Invalid position");
	}
	else {
		if (!m_board[adjustedLine][adjustedColumn].has_value() || m_board[adjustedLine][adjustedColumn].value().GetTopValue().GetValue() < value)
		{
			m_board[adjustedLine][adjustedColumn] = Piece(value, true, playerName, false);
		}
		else {
			std::string border = "=======================================================================";
			std::cout << "\n" << border << "\nInvalid move->Tile value is bigger than card played\n" << border << "\n";
		}
	}
}

void Eter::Board::PrintBoardForFormatedOutput() const
{
	std::string border1 = "<=======================================================================>";
	std::string border2 = "<----------------------------------------------------------------------->";

	std::cout << std::endl << border1 << std::endl;
	std::cout << "\t\t\tCURRENT BOARD: \n";
	std::cout << border2 << std::endl;

	for (auto& row : m_board)
	{
		std::cout << "\t\t\t";
		for (auto& line : row)
		{
			if (line.has_value()) {
				if (line.value().GetTopValue().GetIsIllusion() == true)
					std::cout << "I" << " ";
				else
					std::cout << line.value().GetTopValue().GetValue() << " ";
			}
			else
			{
				std::cout << kEMPTY_BOARD_CELL << " ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << border1 << std::endl;
}

void Eter::Board::IncreaseBoardForNegativeIndexes(const Position& pos)
{
	auto& [line, column] = pos;

	if (line < 0 && m_board.size() < m_maxSize) {
		m_board.insert(m_board.begin(), std::vector<std::optional<Tile>>(m_board[0].size()));
		std::cout << "\n\n\n->->->->->->->->\n" << *this;
	}
	if (column < 0 && m_board[0].size() < m_maxSize) {
		for (auto& row : m_board)
		{
			row.insert(row.begin(), std::optional<Tile>());
		}
		std::cout << "\n\n\n->->->->->->->->\n" << *this;
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
				os << line.value().GetTopValue().GetValue() << " ";
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
