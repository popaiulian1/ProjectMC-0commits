#include "Board.h"
#include "Piece.h"
#include <stdexcept>
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
		if (!m_board[adjustedLine][adjustedColumn].has_value() || m_board[adjustedLine][adjustedColumn].value().GetTopValue().GetValue() < value && 
			!m_board[adjustedLine][adjustedColumn].value().GetTopValue().GetEterCard() && !m_board[adjustedLine][adjustedColumn].value().GetTopValue().GetIsIllusion())
		{
			m_board[adjustedLine][adjustedColumn] = Piece(value, true, playerName, false, false);
		}
		else if (m_board[adjustedLine][adjustedColumn].value().GetTopValue().GetEterCard()) {
			std::string border = "=======================================================================";
			std::cout << "\n" << border << "\nInvalid move->Eter card cannot be covered\n" << border << "\n";
			throw std::invalid_argument("Eter card cannot be covered");
		}
		else if (m_board[adjustedLine][adjustedColumn].value().GetTopValue().GetIsIllusion() && m_board[adjustedLine][adjustedColumn].value().GetTopValue().GetValue() >= value) {
			auto& topValue = m_board[adjustedLine][adjustedColumn]->GetTopValueRef();
			topValue.SetIsIllusion(false);
			std::string border = "=======================================================================";
			std::cout << "\n" << border << "\n" << topValue.GetValue() << " is greater than or equal to " << value << "\n" << border << "\n";
		}
		else if (m_board[adjustedLine][adjustedColumn].value().GetTopValue().GetIsIllusion() && m_board[adjustedLine][adjustedColumn].value().GetTopValue().GetValue() < value) {
			auto& topValue = m_board[adjustedLine][adjustedColumn]->GetTopValueRef();
			topValue.SetIsIllusion(false);
			m_board[adjustedLine][adjustedColumn] = Piece(value, true, playerName, false, false);
			std::string border = "=======================================================================";
			std::cout << "\n" << border << "\n" << topValue.GetValue() << " is not greater than " << value << "\n" << border << "\n";
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
					else if (line.value().GetTopValue().GetEterCard() == true) {
						std::cout << "\033[1;34m" << "E" << "\033[0m ";
					}
					else {
						std::cout << "\033[1;34m" << line.value().GetTopValue().GetValue() << "\033[0m ";
					}
				}
				else {
					if (line.value().GetTopValue().GetIsIllusion() == true)
						std::cout << "\033[1;31m" << "I" << "\033[0m ";
					else if (line.value().GetTopValue().GetEterCard() == true) {
						std::cout << "\033[1;31m" << "E" << "\033[0m ";
					}
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
	size_t fullCols = 0;

	for (const auto& row : m_board) {
		bool isFull = true;

		for (const auto& tile : row) {
			if (!tile.has_value()) {
				isFull = false;
				break;
			}
		}

		if (isFull == true) {
			fullRows++;
		}
	}

	for (const auto& col : m_board) {
		bool isFull = true;

		for (const auto& tile : col) {
			if (!tile.has_value()) {
				isFull = false;
				break;
			}
		}

		if (isFull == true) {
			fullCols++;
		}
	}

	if (fullRows == 2 || fullCols == 2 || (fullRows == 1 && fullCols == 1)) {
		return true;
	}

	return false;
}

void Eter::Board::exportBoardToJson(const std::string& filename) const
{
	nlohmann::json j_board;

	j_board["maxSize"] = m_maxSize;
	j_board["currentSize"] = m_board.size();
	j_board["lastMove"] = {
		{"playerUsername", m_lastMove.playerUsername },
		{ "row", m_lastMove.row },
		{ "column", m_lastMove.column}
	};

	j_board["board"] = nlohmann::json::array();

	for (const auto& row : m_board)
	{
		nlohmann::json j_row = nlohmann::json::array();
		for (const auto& tile : row) {
			if (tile.has_value()) {
				j_row.push_back(tile.value());
			}
			else {
				j_row.push_back(nullptr);
			}
		}
		j_board["board"].push_back(j_row);
	}

	//Write to file here
	std::ofstream file(filename);
	if (file.is_open()) {
		file << j_board.dump(4);
	}
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
