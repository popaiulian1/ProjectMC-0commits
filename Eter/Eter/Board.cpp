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
		//std::cout << "\n-------------------------------\n" << *this << "\n-------------------------------\n";
	}
	if (line > (int)m_board.size()-1 && m_board.size() < m_maxSize) {
		m_board.insert(m_board.end(), std::vector<std::optional<Tile>>(m_board[0].size()));
		//std::cout << "\n-------------------------------\n"  << *this << "\n-------------------------------\n";
	}
	if (column > (int)m_board[0].size()-1 && m_board[0].size() < m_maxSize) {
		for (auto& row : m_board) {
			row.insert(row.end(), std::optional<Tile>());
		}
		//std::cout << "\n-------------------------------\n" << *this << "\n-------------------------------\n";
	}

	int8_t adjustedLine = line, adjustedColumn = column;

	adjustedLine < 0 ? adjustedLine += 1 : adjustedLine;
	adjustedColumn < 0 ? adjustedColumn += 1 : adjustedColumn;

	if (adjustedLine > m_board.size() || adjustedColumn > m_board[0].size())
	{
		std::cout << "Invalid move->Tile position is bigger than max size\n";
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

void Eter::Board::SetLastMove(const std::string& playerUsername, size_t row, size_t column)
{
	m_lastMove.playerUsername = playerUsername;
	m_lastMove.row = row;
	m_lastMove.column = column;
}

void Eter::Board::PrintBoardForFormatedOutput(const std::string& bluePlayerName) const
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
				if (line.value().GetTopValue().GetUserName() == bluePlayerName) {
					if (line.value().GetTopValue().GetIsIllusion() == true)
						std::cout << "\033[1;34m" << "I" << "\033[0m ";
					else {
						std::cout << "\033[1;34m" << line.value().GetTopValue().GetValue() << "\033[0m ";
					}
				}
				else {
					if (line.value().GetTopValue().GetIsIllusion() == true)
						std::cout << "\033[1;31m" << "I" << "\033[0m ";
					else {
						std::cout << "\033[1;31m" << line.value().GetTopValue().GetValue() << "\033[0m ";
					}
				}
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
		//std::cout << "\n\n\n->->->->->->->->\n" << *this;
	}
	if (column < 0 && m_board[0].size() < m_maxSize) {
		for (auto& row : m_board)
		{
			row.insert(row.begin(), std::optional<Tile>());
		}
		//std::cout << "\n\n\n->->->->->->->->\n" << *this;
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

bool Eter::Board::PowerExplosionAvailability() const
{
	size_t fullRows = 0;
	size_t fullColumns = 0;

	for (const auto& row : m_board) {
		bool isFull = true;

		for (const auto& tile : row) {
			if (!tile.has_value()) {
				isFull = false;
				break;
			}
		}

		if (isFull == true) {
			fullRows += 1;
		}
	}

	for (size_t col = 0; col < m_board.size(); ++col) {
		bool isFull = true;

		for (size_t row = 0; row < m_board.size(); ++row) {
			if (!m_board[row][col].has_value()) {
				isFull = false;
				break;
			}
		}

		if (isFull == true) {
			fullColumns += 1;
		}
	}

	if (fullRows >= 2 || fullColumns >= 2 || (fullRows >= 1 && fullColumns >= 1)) {
		return true;
	}

	/*if (m_lastMove.playerUsername == player1.GetUserName()) {
		player1.SetPowerExplosionAccess(true);
	}
	else if (m_lastMove.playerUsername == player2.GetUserName()) {
		player2.SetPowerExplosionAccess(true);
	}*/

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
