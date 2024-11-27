#include "Wizards.h"
#include "Board.h"
#include "Tile.h"
#include "Piece.h"
#include <iostream>
#include <string>

//Constructors & Destructor
Eter::Wizards::Wizards() :
	m_name("Unknown"), m_mageType(MageType::FIRE), m_magicPowerUsed(false), m_etherCards(1), m_board(nullptr), m_username("Unknown") {}


Eter::Wizards::Wizards(std::string wizardName, MageType type, Board* gameBoard, std::string username) :
	m_name(wizardName), m_mageType(type), m_magicPowerUsed(false), m_etherCards(1), m_board(gameBoard), m_username(username) {}


Eter::Wizards::Wizards(const Wizards& other) :
	m_name(other.m_name), m_mageType(other.m_mageType), m_magicPowerUsed(other.m_magicPowerUsed), m_etherCards(other.m_etherCards), m_board(other.m_board) {}

const std::string& Eter::Wizards::GetUserName() const
{
	return m_username;
}

// Determination of Power 
void Eter::Wizards::fireMasterPower(int powerIndex, int row, int col)
{
	if (powerIndex == 1)
		eliminateOpponentCard(row, col);

	else if (powerIndex == 2)
	{
		std::cout << "Would you like to eliminate a row or a column?";
		std::cout << "Type 'row' or 'column' depending on your choice.";
		std::string input;
		std::cin >> input;
		if (input == "row")
			eliminateRow(row);


		else if (input == "column")
			eliminateCol(col);
		else
			std::cout << "Invalid input. Please type 'row' or 'column'.\n";


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
	/*if (powerIndex == 1)
		moveOwnStack();

	else if (powerIndex == 2)
		gainExtraEtherCard();*/

}

void Eter::Wizards::waterMasterPower(int powerIndex, int srcRow, int srcCol, int destRow)
{
	/*if (powerIndex == 1)
		moveOpponentStack();

	else if (powerIndex == 2)
		moveEdgeRow();*/

}

// Methods for Masters of fire
void Eter::Wizards::eliminateRow(int row)
{
	// Verify if the row is valid
	if (row < 0 || row >= m_board->GetCurrentSize()) {
		std::cout << "Invalid row index.\n";
		return;
	}

	// Verify if the row has at least 3 positions 
	if (m_board->GetCurrentSize() < 3) {
		std::cout << "Row must have at least 3 positions.\n";
		return;
	}

	bool hasOwnCard = false;
	auto& gameBoard = m_board->GetBoardReference();

	// Verify every column of the row
	for (int col = 0; col < m_board->GetCurrentSize(); ++col) {
		if (gameBoard[row][col].has_value()) { // Verify if we have at least one of our own card visibile in the row
			const Tile& tile = gameBoard[row][col].value();
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
	for (int col = 0; col < m_board->GetCurrentSize(); ++col) {
		if (gameBoard[row][col].has_value()) {

			Tile& tile = gameBoard[row][col].value();
			tile.RemoveStack();
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

			Tile& tile = gameBoard[row][col].value();
			tile.RemoveStack();
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
			tile.GetValue().pop(); // Remove the opponent's top card

			if (tile.GetTopValue().GetUserName() == this->GetUserName()) {
				std::cout << "The opponent's card at (" << row << ", " << col << ") has been removed.\n";
				return;
			}
			else {
				// Restore the opponent's card since the underlying card isn't the player's
				tile.GetValue().push(opponentCard);
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

	if (row < 0 || row >= m_board->GetCurrentSize() || col < 0 || col >= m_board->GetCurrentSize() ||
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
		if (it->GetValue() < opponentCardValue) {
			if (smallestCardIt == playerHand.end() || it->GetValue() < smallestCardIt->GetValue()) //Finding the smallest value that is in our hand and < opponent's card
				smallestCardIt = it;
		}
	}
	if (smallestCardIt != playerHand.end()) {
		// Place the player's card on top of the opponent's card
		tile.GetValue().push(*smallestCardIt);

		// Remove the card from the player's hand
		char placedCardValue = smallestCardIt->GetValue();
		playerHand.erase(smallestCardIt);

		std::cout << "You have successfully covered the opponent's card at (" << row << ", " << col
			<< ") with your card of value " << placedCardValue << ".\n";
	}
	else
		std::cout << "No suitable card of lower value was found in your hand.\n";
}

void Eter::Wizards::createPit(int row, int col)
{
	if (row < 0 || row >= m_board->GetCurrentSize() || col < 0 || col >= m_board->GetCurrentSize()) {
		std::cout << "Invalid position for creating a pit.\n";
		return;
	}

	auto& gameBoard = m_board->GetBoardReference();

	if (gameBoard[row][col].has_value()) {
		std::cout << "The position (" << row << ", " << col << ") is already occupied. Cannot create a pit here.\n";
		return;
	}

	Tile pitTile; // Creates a Tile as a pit
	pitTile.SetAsPit();
	gameBoard[row][col] = pitTile;

	std::cout << "A pit has been created at position (" << row << ", " << col << ").\n";

}


// Methods for Masters of air

void Eter::Wizards::moveOwnStack(int srcRow, int srcCol, int destRow, int destCol)
{
	if (srcRow < 0 || srcRow >= m_board->GetCurrentSize() || srcCol < 0 || srcCol >= m_board->GetCurrentSize()) {
		std::cout << "Invalid source position (" << srcRow << ", " << srcCol << ").\n";
		return;
	}
	if (destRow < 0 || destRow >= m_board->GetCurrentSize() || destCol < 0 || destCol >= m_board->GetCurrentSize()) {
		std::cout << "Invalid destination position (" << destRow << ", " << destCol << ").\n";
		return;
	}

	auto& gameBoard = m_board->GetBoardReference();

	if (!gameBoard[srcRow][srcCol].has_value()) {
		std::cout << "No stack found at source position (" << srcRow << ", " << srcCol << ").\n";
		return;
	}

	Tile& srcTile = gameBoard[srcRow][srcCol].value();
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

	std::stack<Piece> stackToMove = srcTile.GetValue();
	std::vector<Piece> cardsInOrder;

	while (!stackToMove.empty()) {
		cardsInOrder.push_back(stackToMove.top());
		stackToMove.pop();
	}

	for (auto it = cardsInOrder.rbegin(); it != cardsInOrder.rend(); ++it) {
		destTile.SetValue(*it);
	}

	srcTile.RemoveStack();

	std::cout << "The stack from (" << srcRow << ", " << srcCol << ") has been moved to (" << destRow << ", " << destCol << ").\n";

}

void Eter::Wizards::gainExtraEtherCard(int row, int col)
{
	if (row < 0 || row >= m_board->GetCurrentSize() || col < 0 || col >= m_board->GetCurrentSize()) {
		std::cout << "Invalid position (" << row << ", " << col << "). Please choose a valid position.\n";
		return;
	}
	auto& gameBoard = m_board->GetBoardReference();

	if (gameBoard[row][col].has_value()) {
		std::cout << "Position (" << row << ", " << col << ") is not empty. Please choose an empty position.\n";
		return;
	}

	Piece magePowerCard('E', false, this->GetUserName());

	// Placing the Eter card
	Tile newTile;
	newTile.SetValue(magePowerCard);
	gameBoard[row][col] = newTile;

	std::cout << "Mage Power card has been placed as an ETER card at (" << row << ", " << col << ").\n";
}
