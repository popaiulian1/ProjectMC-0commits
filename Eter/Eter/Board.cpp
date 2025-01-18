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

Eter::lastMove Eter::Board::GetLastMove() const
{
	return m_lastMove;
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
		if (m_board[adjustedLine][adjustedColumn].has_value() && m_board[adjustedLine][adjustedColumn].value().IsPit()) {
			std::string border = "=======================================================================";
			std::cout << "\n" << border << "\nInvalid move->Tile is a pit\n" << border << "\n";
			throw std::invalid_argument("Tile is a pit");
		}
		else if (!m_board[adjustedLine][adjustedColumn].has_value() || m_board[adjustedLine][adjustedColumn].value().GetValue().size() == 0)
		{
			m_board[adjustedLine][adjustedColumn] = Piece(value, true, playerName, false, false);
		}
		else if (m_board[adjustedLine][adjustedColumn].value().GetTopValue().GetValue() < value && !m_board[adjustedLine][adjustedColumn].value().GetTopValue().GetEterCard() && !m_board[adjustedLine][adjustedColumn].value().GetTopValue().GetIsIllusion()) {
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
	SetLastMove(playerName, adjustedLine, adjustedColumn);
}

void Eter::Board::SetLastMove(const std::string& playerUsername, size_t row, size_t column)
{
	m_lastMove.m_playerUsername = playerUsername;
	m_lastMove.m_row = row;
	m_lastMove.m_column = column;
}

void Eter::Board::SetMaxSize(const size_t& size)
{
	m_maxSize = size;
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
			if (line.has_value() && line.value().GetValue().size() != 0) {
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
			else if (line.has_value() && line.value().IsPit())
			{
				std::cout << "P ";
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
		if (row.size() < GetMaxSize()) // to jump the for if the column is not full meaning that there is at least 1 empty tile since the board is still to get to max size
			return true;

		for (auto& line : row)
		{
			if (!line.has_value() || line.value().IsPit())
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

//void Eter::Board::exportBoardToJson(const std::string& filename) const
//{
//	nlohmann::json j_board;
//
//	j_board["maxSize"] = m_maxSize;
//	j_board["currentSize"] = m_board.size();
//	j_board["lastMove"] = {
//		{"playerUsername", m_lastMove.m_playerUsername },
//		{ "row", m_lastMove.m_row },
//		{ "column", m_lastMove.m_column}
//	};
//
//	j_board["board"] = nlohmann::json::array();
//
//	for (const auto& row : m_board)
//	{
//		nlohmann::json j_row = nlohmann::json::array();
//		for (const auto& tile : row) {
//			if (tile.has_value()) {
//				j_row.push_back(tile.value());
//			}
//			else {
//				j_row.push_back(nullptr);
//			}
//		}
//		j_board["board"].push_back(j_row);
//	}
//
//	//Write to file here
//	std::ofstream file(filename);
//	if (file.is_open()) {
//		file << j_board.dump(4);
//	}
//}

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

void Eter::to_json(nlohmann::json& j, const Board& b)
{
	j = nlohmann::json{
		{"maxSize", b.GetMaxSize()},
		{"currentSize", b.GetCurrentSize()},
		{"lastMove", {
			{"playerUsername", b.GetLastMove().m_playerUsername},
			{"row", b.GetLastMove().m_row},
			{"column", b.GetLastMove().m_column}
		}},
		{"board", nlohmann::json::array()}
	};

	for (const auto& row : b.GetBoard())
	{
		nlohmann::json j_row = nlohmann::json::array();
		for (const auto& tile : row)
		{
			if (tile.has_value())
			{
				j_row.push_back(tile.value());
			}
			else
			{
				j_row.push_back(nullptr);
			}
		}
		j["board"].push_back(j_row);
	}
}

void Eter::from_json(const nlohmann::json& j, Board& b)
{
	try {
		BoardMatrix boardMatrix;

		for (const auto& row : j.at("board")) {
			if (!row.is_array()) {
				throw std::runtime_error("Row is not an array");
			}

			BoardVector boardRow;
			for (const auto& tile : row) {
				if (tile.is_null()) {
					boardRow.push_back(Tile()); // Handle null tiles
				}
				else if (tile.is_object()) {
					std::cout << "Parsing Tile: " << tile.dump(4) << std::endl;
					Tile newTile(tile.get<Eter::Tile>());
					boardRow.push_back(newTile); // Convert to Tile object
				}
				else {
					throw std::runtime_error("Unexpected tile format");
				}
			}
			boardMatrix.push_back(boardRow);
		}

		b.SetBoard(boardMatrix);

		b.SetLastMove(
			j.at("lastMove").at("playerUsername").get<std::string>(),
			j.at("lastMove").at("row").get<size_t>(),
			j.at("lastMove").at("column").get<size_t>()
		);

		b.SetMaxSize(j.at("maxSize").get<size_t>());

	}
	catch (const std::exception& e) {
		throw std::runtime_error(std::string("Error in from_json: ") + e.what());
	}
}
