#include "Wizards.h"
#include "Board.h"
#include "Tile.h"
#include "Piece.h"
#include <iostream>
#include <string>

//Constructors & Destructor
Eter::Wizards::Wizards() :
	m_name("Unknown"), m_mageType(MageType::FIRE), m_magicPowerUsed(false),
	m_etherCards(1), m_board(nullptr), m_username("Unknown") {}


Eter::Wizards::Wizards(std::string wizardName, MageType type, Board* gameBoard, std::string username) :
	m_name(wizardName), m_mageType(type), m_magicPowerUsed(false),
	m_etherCards(1), m_board(gameBoard), m_username(username) {}


Eter::Wizards::Wizards(const Wizards& other) :
	m_name(other.m_name), m_mageType(other.m_mageType), 
	m_magicPowerUsed(other.m_magicPowerUsed), m_etherCards(other.m_etherCards), 
	m_board(other.m_board) {}

const std::string& Eter::Wizards::GetUserName() const
{
	return m_username;
}

const Eter::MageType& Eter::Wizards::GetMageType() const
{
	return m_mageType;
}

const std::string Eter::Wizards::toStringMageType(MageType mageType) const
{
	switch (mageType) {
	case MageType::FIRE:  
		return "FIRE";
	case MageType::EARTH: 
		return "EARTH";
	case MageType::AIR:   
		return "AIR";
	case MageType::WATER: 
		return "WATER";
	default:              
		return "UNKNOWN";
	}
}

const Eter::Board* Eter::Wizards::GetBoardWizard() const
{
	return m_board;
}

const std::string& Eter::Wizards::GetName() const
{
	return m_name;
}

const int& Eter::Wizards::GetEtherCards() const
{
	return m_etherCards;
}

const bool& Eter::Wizards::GetMagicPowerUsed() const
{
	return m_magicPowerUsed;
}

void Eter::Wizards::SetMageType(const Eter::MageType& type)
{
	m_mageType = type;
}

void Eter::Wizards::SetUserName(const std::string& username)
{
	m_username = username;
}

void Eter::Wizards::SetBoardForMage(Board* board)
{
	m_board = board;
}

void Eter::Wizards::SetEtherCards(int etherCards)
{
	m_etherCards = etherCards;
}

void Eter::Wizards::SetMagicPowerUsed(bool magicPowerUsed)
{
	m_magicPowerUsed = magicPowerUsed;
}

// Determination of Power 
void Eter::Wizards::fireMasterPower(int powerIndex, int row, int col)
{
	if (powerIndex == 1)
		eliminateOpponentCard(row, col);

	else if (powerIndex == 2)
	{
		std::cout << "Would you like to eliminate a row or a column?";
		std::cout << "Type 'row' or 'column' depending on your choice.\n";
		std::string input;
		std::cin >> input;
		if (input == "row")
			eliminateRow(row);

		else if (input == "column")
			eliminateCol(col);
		else {
			std::cout << "Invalid input. Please type 'row' or 'column'.\n";
		    return;
		}
			


	}
}

void Eter::Wizards::earthMasterPower(int powerIndex, int row, int col, std::vector<Piece>& playerHand)
{
	if (powerIndex == 1)
		coverOpponentCard(row, col, playerHand);

	else if (powerIndex == 2)
		createPit(row, col);

}

void Eter::Wizards::airMasterPower(int powerIndex, int row, int col)
{
	if (powerIndex == 1) {

		int destrow, destcol;
		std::cout << "At what row and column would you like to place your card or deck of cards?\n";
		std::cout << "Row index: ";
		std::cin >> destrow;
		std::cout << "\n";
		std::cout << "Col index: ";
		std::cin>>destcol;
		std::cout << "\n";
		auto& gameBoard = m_board->GetBoardReference();

	if (destrow < 0 || destcol < 0) {
		m_board->IncreaseBoardForNegativeIndexes({ destrow, destcol });
		gameBoard = m_board->GetBoardReference();
	}
	if (destrow >= (int)gameBoard.size() - 1 && gameBoard.size() < m_board->GetMaxSize()) {
		gameBoard.insert(gameBoard.end(), std::vector<std::optional<Tile>>(gameBoard[0].size()));
	}
	if (destcol >= (int)gameBoard[0].size() - 1 && gameBoard[0].size() < m_board->GetMaxSize()) {
		for (auto& r : gameBoard) {
			r.insert(r.end(), std::optional<Tile>());
		}
	}

	int adjustedLine = destrow, adjustedColumn = destcol;
	adjustedLine < 0 ? adjustedLine += 1 : adjustedLine;
	adjustedColumn < 0 ? adjustedColumn += 1 : adjustedColumn;

	if (adjustedLine >= gameBoard.size() || adjustedColumn >= gameBoard[0].size() ||
		adjustedLine < 0 || adjustedColumn < 0) {
		std::cout << "Invalid move->Tile position is out of bounds\n";
		return;
	}
        moveOwnStack(row, col, adjustedLine, adjustedColumn);
	}
		
	else if (powerIndex == 2)
		gainExtraEtherCard(row,col);

}

void Eter::Wizards::waterMasterPower(int powerIndex, int srcRow, int srcCol, int destRow, int destCol)
{
	if (powerIndex == 1)
		moveOpponentStack(srcRow,srcCol,destRow, destCol);

	else if (powerIndex == 2)
		moveEdgeRowCol();

}

// Methods for Masters of fire
void Eter::Wizards::eliminateRow(int row)
{
	auto rowSize = m_board->GetBoard()[row].size();

	// Verify if the row is valid
	if (row < 0 || row >= rowSize) {
		std::cout << "Invalid row index.\n";
		return;
	}

	// Verify if the row has at least 3 positions 
	if (rowSize < 3) {
		std::cout << "Row must have at least 3 positions.\n";
		return;
	}

	bool hasOwnCard = false;
	auto& gameBoard = m_board->GetBoardReference();

	// Verify every column of the row
	for (int col = 0; col < rowSize; ++col) {
		if (gameBoard[row][col].has_value()) { // Verify if we have at least one of our own card visibile in the row
			const Tile& tile = gameBoard[row][col].value();
			if (tile.GetTopValue().GetEterCard()) {
				std::cout << "An ETER card is present in the row. Cannot eliminate the row.\n";
				return;
			}

			if (tile.GetTopValue().GetUserName() == this->GetUserName()) {
				hasOwnCard = true;
				break;
			}
		}
	}

	// When the power can not be applied
	if (!hasOwnCard) {
		std::cout << "No own card found in row " << row << ". Cannot eliminate the row.\n";
		return;
	}

	// Applied power
	for (int col = 0; col < rowSize; ++col) {
		if (gameBoard[row][col].has_value()) {

			/*Tile& tile = gameBoard[row][col].value();
			tile.RemoveStack();*/
			gameBoard[row][col] = std::nullopt;
		}
	}

	std::cout << "Row " << row << " has been eliminated.\n";
}

void Eter::Wizards::eliminateCol(int col)
{
	// Verify if the col is valid
	if (col < 0 || col >= m_board->GetCurrentSize()) {
		std::cout << "Invalid col index.\n";
		return;
	}

	// Verify if the col has at least 3 positions 
	if (m_board->GetCurrentSize() < 3) {
		std::cout << "Col must have at least 3 positions.\n";
		return;
	}

	bool hasOwnCard = false;
	auto& gameBoard = m_board->GetBoardReference();

	// Verify every row of the column
	for (int row = 0; row < m_board->GetCurrentSize(); ++row) {
		if (gameBoard[row][col].has_value()) { // Verify if we have at least one of our own card visibile in the col
			const Tile& tile = gameBoard[row][col].value();
			if (tile.GetTopValue().GetEterCard()) {
				std::cout << "An ETER card is present in the column. Cannot eliminate the col.\n";
				return;
			}

			if (tile.GetTopValue().GetUserName() == this->GetUserName()) {
				hasOwnCard = true;
				break;
			}
		}
	}

	// When the power can not be applied
	if (!hasOwnCard) {
		std::cout << "No own card found in col " << col << ". Cannot eliminate the col.\n";
		return;
	}

	// Applied power
	for (int row = 0; row < m_board->GetCurrentSize(); ++row) {
		if (gameBoard[row][col].has_value()) {

			/*Tile& tile = gameBoard[row][col].value();
			tile.RemoveStack();*/
			gameBoard[row][col] = std::nullopt;
		}
	}

	std::cout << "Column " << col << " has been eliminated.\n";
}

void Eter::Wizards::eliminateOpponentCard(int row, int col)
{
	auto& gameBoard = m_board->GetBoardReference();
	Tile& tile = gameBoard[row][col].value();

	// Check if the specified position contains a tile
	if (!gameBoard[row][col].has_value()) {
		std::cout << "No tile found at (" << row << ", " << col << ").\n";
		return;
	}

	if (tile.GetTopValue().GetUserName() != this->GetUserName()) { // Verify if the top card is not ours

		if (tile.GetValue().size() > 1) { //Check to see if there are any cards below

			// Temporarily store the opponent's card to verify the card underneath
			Piece opponentCard = tile.GetTopValue();
			tile.GetValueRef().pop_back(); // Remove the opponent's top card

			if (tile.GetTopValue().GetUserName() == this->GetUserName()) {
				std::cout << "The opponent's card at (" << row << ", " << col << ") has been removed.\n";
				return;
			}
			else {
				// Restore the opponent's card since the underlying card isn't the player's
				tile.GetValue().push_back(opponentCard);
				std::cout << "The card underneath is not owned by you. Cannot remove the opponent's card.\n";
			}
		}

		else
			std::cout << "No card underneath to verify ownership. Cannot remove the opponent's card.\n";
	}
	else
		std::cout << "No opponent's card found at (" << row << ", " << col << ").\n";
}


// Methods for Masters of earth
void Eter::Wizards::coverOpponentCard(int row, int col, std::vector<Piece>& playerHand)
{
	auto& gameBoard = m_board->GetBoardReference();

	if (row < 0 || row >= m_board->GetCurrentSize() || col < 0 || col >= m_board->GetBoard()[row].size() ||
		!gameBoard[row][col].has_value())
	{
		std::cout << "Invalid position or no tile found at (" << row << ", " << col << ").\n";
		return;
	}

	Tile& tile = gameBoard[row][col].value();

	if (tile.GetTopValue().GetUserName() == this->GetUserName()) // If the top card is ours
	{
		std::cout << "You cannot cover your own card at (" << row << ", " << col << ").\n";
		return;

	}

	char opponentCardValue = tile.GetTopValue().GetValue();
	auto smallestCardIt = playerHand.end();

	for (auto it = playerHand.begin(); it != playerHand.end(); ++it) {
		if (it->GetValue() < opponentCardValue && it->GetEterCard() == false) {
			if (smallestCardIt == playerHand.end() || it->GetValue() < smallestCardIt->GetValue()) //Finding the smallest value that is in our hand and < opponent's card
				smallestCardIt = it;
		}
	}
	if (smallestCardIt != playerHand.end()) {
		// Place the player's card on top of the opponent's card
		char placedCardValue = smallestCardIt->GetValue();
		tile.GetValueRef().push_back(Piece(placedCardValue, true, this->GetUserName(), false, false));

		// Remove the card from the player's hand
		playerHand.erase(smallestCardIt);

		std::cout << "You have successfully covered the opponent's card at (" << row << ", " << col
			<< ") with your card of value " << placedCardValue << ".\n";
	}
	else
		std::cout << "No suitable card of lower value was found in your hand.\n";
}

void Eter::Wizards::createPit(int row, int col)
{
	auto& gameBoard = m_board->GetBoardReference();

	if (row < 0 || col < 0) {
		m_board->IncreaseBoardForNegativeIndexes({ row, col });
		gameBoard = m_board->GetBoardReference();
	}
	if (row >= (int)gameBoard.size() - 1 && gameBoard.size() < m_board->GetMaxSize()) {
		gameBoard.insert(gameBoard.end(), std::vector<std::optional<Tile>>(gameBoard[0].size()));
	}
	if (col >= (int)gameBoard[0].size() - 1 && gameBoard[0].size() < m_board->GetMaxSize()) {
		for (auto& r : gameBoard) {
			r.insert(r.end(), std::optional<Tile>());
		}
	}

	int adjustedLine = row, adjustedColumn = col;
	adjustedLine < 0 ? adjustedLine += 1 : adjustedLine;
	adjustedColumn < 0 ? adjustedColumn += 1 : adjustedColumn;

	if (adjustedLine >= gameBoard.size() || adjustedColumn >= gameBoard[0].size() ||
		adjustedLine < 0 || adjustedColumn < 0) {
		std::cout << "Invalid move->Tile position is out of bounds\n";
		return;
	}

	if (gameBoard[adjustedLine][adjustedColumn].has_value()) {
		std::cout << "The position (" << adjustedLine << ", " << adjustedColumn
			<< ") is already occupied. Cannot create a pit here.\n";
		return;
	}

	// Create the pit
	gameBoard[adjustedLine][adjustedColumn].emplace(Tile()); // Create an empty Tile in-place
	gameBoard[adjustedLine][adjustedColumn]->SetAsPit(); // Set it as a pit

	std::cout << "A pit has been created at position (" << adjustedLine << ", "<< adjustedColumn << ").\n";
}


// Methods for Masters of air

void Eter::Wizards::moveOwnStack(int srcRow, int srcCol, int destRow, int destCol)
{
	if (srcRow < 0 || srcRow >= m_board->GetCurrentSize() || srcCol < 0 || srcCol >= m_board->GetCurrentSize()) {
		std::cout << "Invalid source position (" << srcRow << ", " << srcCol << ").\n";
		return;
	}
	
	auto& gameBoard = m_board->GetBoardReference();

	if (!gameBoard[srcRow][srcCol].has_value()) {
		std::cout << "No stack found at source position (" << srcRow << ", " << srcCol << ").\n";
		return;
	}

	Tile& srcTile = gameBoard[srcRow][srcCol].value();

	if (srcTile.GetTopValue().GetEterCard()) {
		std::cout << "The stack at source position (" << srcRow << ", " << srcCol << ") contains an ETER card. Cannot move it.\n";
		return;
	}

	//carete a new tile at the destination
	gameBoard[destRow][destCol] = Tile();
	Tile& destTile = gameBoard[destRow][destCol].value();

	if (srcTile.GetTopValue().GetUserName() != this->GetUserName()) {
		std::cout << "The stack at source position (" << srcRow << ", " << srcCol << ") does not belong to you.\n";
		return;
	}

	if (destTile.GetValue().size() > 0 || destTile.IsPit()) {
		std::cout << "The destination position (" << destRow << ", " << destCol << ") is not empty or is a pit.\n";
		return;
	}


	//Moving the stack of cards

	std::deque<Piece> stackToMove = srcTile.GetValue();
	std::vector<Piece> cardsInOrder;

	while (!stackToMove.empty()) {
		cardsInOrder.push_back(stackToMove.back());
		stackToMove.pop_back();
	}

	for (auto it = cardsInOrder.rbegin(); it != cardsInOrder.rend(); ++it) {
		destTile.SetValue(*it);
	}

	/*srcTile.RemoveStack();*/
	gameBoard[srcRow][srcCol] = std::nullopt;

	std::cout << "The stack from (" << srcRow << ", " << srcCol << ") has been moved to (" << destRow << ", " << destCol << ").\n";

}

void Eter::Wizards::gainExtraEtherCard(int row, int col)
{
	auto& gameBoard = m_board->GetBoardReference();

	if (row < 0 || col < 0) {
		m_board->IncreaseBoardForNegativeIndexes({ row, col });
		gameBoard = m_board->GetBoardReference();
	}

	if (row >= (int)gameBoard.size() - 1 && gameBoard.size() < m_board->GetMaxSize()) {
		gameBoard.insert(gameBoard.end(), std::vector<std::optional<Tile>>(gameBoard[0].size()));
	}
	if (col >= (int)gameBoard[0].size() - 1 && gameBoard[0].size() < m_board->GetMaxSize()) {
		for (auto& r : gameBoard) {
			r.insert(r.end(), std::optional<Tile>());
		}
	}

	int adjustedLine = row, adjustedColumn = col;
	adjustedLine < 0 ? adjustedLine += 1 : adjustedLine;
	adjustedColumn < 0 ? adjustedColumn += 1 : adjustedColumn;

	if (adjustedLine >= gameBoard.size() || adjustedColumn >= gameBoard[0].size() ||
		adjustedLine < 0 || adjustedColumn < 0) {
		std::cout << "Invalid move->Tile position is out of bounds\n";
		return;
	}

	if (gameBoard[adjustedLine][adjustedColumn].has_value()) {
		std::cout << "The position (" << adjustedLine << ", " << adjustedColumn
			<< ") is already occupied. Cannot place eter card here.\n";
		return;
	}

	Piece magePowerCard('E', false, GetUserName(), false, true);

	// Placing the Eter card
	gameBoard[adjustedLine][adjustedColumn].emplace();
	gameBoard[adjustedLine][adjustedColumn]->SetValue(magePowerCard);

	std::cout << "Mage Power card has been placed as an ETER card at (" << row << ", " << col << ").\n";
}


// Methods for Masters of water

void Eter::Wizards::moveOpponentStack(int srcRow, int srcCol, int destRow, int destCol)
{
	if (srcRow < 0 || srcRow >= m_board->GetCurrentSize() || srcCol < 0 || srcCol >= m_board->GetCurrentSize()) {
		std::cout << "Invalid source position (" << srcRow << ", " << srcCol << ").\n";
		return;
	}
	auto& gameBoard = m_board->GetBoardReference();
	if (destRow < 0 || destCol < 0) {
		m_board->IncreaseBoardForNegativeIndexes({ destRow, destCol });
		gameBoard = m_board->GetBoardReference();
	}
	if (destRow >= (int)gameBoard.size() - 1 && gameBoard.size() < m_board->GetMaxSize()) {
		gameBoard.insert(gameBoard.end(), std::vector<std::optional<Tile>>(gameBoard[0].size()));
	}
	if (destCol >= (int)gameBoard[0].size() - 1 && gameBoard[0].size() < m_board->GetMaxSize()) {
		for (auto& r : gameBoard) {
			r.insert(r.end(), std::optional<Tile>());
		}
	}

	int adjustedLine = destRow, adjustedColumn = destCol;
	adjustedLine < 0 ? adjustedLine += 1 : adjustedLine;
	adjustedColumn < 0 ? adjustedColumn += 1 : adjustedColumn;

	if (adjustedLine >= gameBoard.size() || adjustedColumn >= gameBoard[0].size() ||
		adjustedLine < 0 || adjustedColumn < 0) {
		std::cout << "Invalid move->Tile position is out of bounds\n";
		return;
	}
	if (!gameBoard[srcRow][srcCol].has_value()) {
		std::cout << "No stack found at source position (" << srcRow << ", " << srcCol << ").\n";
		return;
	}
	destRow = adjustedLine;
	destCol = adjustedColumn;

	Tile& srcTile = gameBoard[srcRow][srcCol].value();

	gameBoard[destRow][destCol] = Tile();
	Tile& destTile = gameBoard[destRow][destCol].value();

	if (srcTile.GetTopValue().GetUserName() == this->GetUserName()) {
		std::cout << "The stack at source position (" << srcRow << ", " << srcCol << ") does belong to you.\n";
		return;
	}

	if (srcTile.GetTopValue().GetEterCard()) {
		std::cout << "The stack at source position (" << srcRow << ", " << srcCol << ") contains an ETER card. Cannot move it.\n";
		return;
	}

	if (destTile.GetValue().size() > 0 || destTile.IsPit()) {
		std::cout << "The destination position (" << destRow << ", " << destCol << ") is not empty or is a pit.\n";
		return;
	}

	//Moving the stack of cards

	std::deque<Piece> stackToMove = srcTile.GetValue();
	std::vector<Piece> cardsInOrder;

	while (!stackToMove.empty()) {
		cardsInOrder.push_back(stackToMove.back());
		stackToMove.pop_back();
	}

	for (auto it = cardsInOrder.rbegin(); it != cardsInOrder.rend(); ++it) {
		destTile.SetValue(*it);
	}

	//srcTile.RemoveStack();
	gameBoard[srcRow][srcCol] = std::nullopt;

	std::cout << "The stack from (" << srcRow << ", " << srcCol << ") has been moved to (" << destRow << ", " << destCol << ").\n";

}

void Eter::Wizards::moveEdgeRowCol() {
	auto& gameBoard = m_board->GetBoardReference();
	std::cout << "Would you like to move a row or a column?\n";
	std::cout << "Enter 'row' / 'column'.\n";
	std::string option;
	std::cin >> option;

	if (option == "row") {
		std::cout << "Which row would you like to move? (Must be an edge row: 0 or " << m_board->GetMaxSize()-1 << ")\n";
		int srcRow;
		std::cin >> srcRow;

		if (srcRow != 0 || srcRow != m_board->GetMaxSize()-1) {
			std::cout << "Invalid row. Only edge rows can be moved.\n";
			return;
		}

		std::cout << "Where would you like to move it? (0 for top, " << m_board->GetMaxSize()-1 << " for bottom)\n";
		int destRow;
		std::cin >> destRow;

		if (destRow != 0 || destRow != m_board->GetMaxSize()-1 || m_board->GetMaxSize()-1!= m_board->GetCurrentSize()-1) {
			std::cout << "Invalid destination row. You can only move to the edges.\n";
			return;
		}

		if (srcRow == destRow) {
			std::cout << "Source and destination rows are the same. No movement performed.\n";
			return;
		}

		// Check for pits in destination row before moving
		for (int col = 0; col < m_board->GetCurrentSize(); ++col) {
			if (gameBoard[destRow][col].has_value() && gameBoard[destRow][col]->IsPit()) {
				std::cout << "Destination row contains a pit. Cannot move row.\n";
				return;
			}
		}

		// Store the source row temporarily
		std::vector<std::optional<Tile>> tempRow;
		for (int col = 0; col < m_board->GetCurrentSize(); ++col) {
			if (gameBoard[srcRow][col].has_value()) {
				tempRow.push_back(std::move(gameBoard[srcRow][col]));
			}
			else {
				tempRow.push_back(std::nullopt);
			}
		}

		// Move destination row to source if it has any pieces
		for (int col = 0; col < m_board->GetCurrentSize(); ++col) {
			if (gameBoard[destRow][col].has_value()) {
				gameBoard[srcRow][col] = std::move(gameBoard[destRow][col]);
			}
			else {
				gameBoard[srcRow][col] = std::nullopt;
			}
		}

		// Move stored source row to destination
		for (int col = 0; col < m_board->GetCurrentSize(); ++col) {
			gameBoard[destRow][col] = std::move(tempRow[col]);
		}

		std::cout << "Row " << srcRow << " successfully moved to " << destRow << ".\n";
	}
	else if (option == "column") {
		std::cout << "Which column would you like to move? (Must be an edge column: 0 or " << m_board->GetMaxSize()-1 << ")\n";
		int srcCol;
		std::cin >> srcCol;

		if (srcCol != 0 || srcCol != m_board->GetMaxSize()-1) {
			std::cout << "Invalid column. Only edge columns can be moved.\n";
			return;
		}

		std::cout << "Where would you like to move it? (0 for left, " << m_board->GetMaxSize()-1 << " for right)\n";
		int destCol;
		std::cin >> destCol;

		if (destCol != 0 || destCol != m_board->GetMaxSize()-1) {
			std::cout << "Invalid destination column. You can only move to the edges.\n";
			return;
		}

		if (srcCol == destCol) {
			std::cout << "Source and destination columns are the same. No movement performed.\n";
			return;
		}

		// Check for pits in destination column before moving
		for (int row = 0; row < m_board->GetCurrentSize(); ++row) {
			if (gameBoard[row][destCol].has_value() && gameBoard[row][destCol]->IsPit()) {
				std::cout << "Destination column contains a pit. Cannot move column.\n";
				return;
			}
		}

		// Store the source column temporarily
		std::vector<std::optional<Tile>> tempCol;
		for (int row = 0; row < m_board->GetCurrentSize(); ++row) {
			if (gameBoard[row][srcCol].has_value()) {
				tempCol.push_back(std::move(gameBoard[row][srcCol]));
			}
			else {
				tempCol.push_back(std::nullopt);
			}
		}

		// Move destination column to source if it has any pieces
		for (int row = 0; row < m_board->GetCurrentSize(); ++row) {
			if (gameBoard[row][destCol].has_value()) {
				gameBoard[row][srcCol] = std::move(gameBoard[row][destCol]);
			}
			else {
				gameBoard[row][srcCol] = std::nullopt;
			}
		}

		// Move stored source column to destination
		for (int row = 0; row < m_board->GetCurrentSize(); ++row) {
			gameBoard[row][destCol] = std::move(tempCol[row]);
		}

		std::cout << "Column " << srcCol << " successfully moved to " << destCol << ".\n";
	}
	else {
		std::cout << "Invalid option. Please choose 'row' or 'column'.\n";
	}
}

void Eter::to_json(nlohmann::json& j, const Wizards& w)
{
	j = nlohmann::json{
		{"name", w.GetName()},
		{"mageType", w.toStringMageType(w.GetMageType())},
		{"magicPowerUsed", w.GetMagicPowerUsed()},
		{"etherCards", w.GetEtherCards()},
		{"username", w.GetUserName()}
	};
}

void Eter::from_json(const nlohmann::json& j, Wizards& w)
{
	std::string mageType = j.at("mageType").get<std::string>();
	MageType type;
	if (mageType == "FIRE")
		type = MageType::FIRE;
	else if (mageType == "EARTH")
		type = MageType::EARTH;
	else if (mageType == "AIR")
		type = MageType::AIR;
	else if (mageType == "WATER")
		type = MageType::WATER;
	else
		type = MageType::FIRE;


	w = Wizards(j.at("name").get<std::string>(), type, nullptr, j.at("username").get<std::string>());
	w.SetMagicPowerUsed(j.at("magicPowerUsed").get<bool>());
	w.SetEtherCards(j.at("etherCards").get<int>());
}
