#include "Wizards.h"
#include "Board.h"
#include "Tile.h"
#include "Piece.h"
#include <iostream>
#include <string>
 
//Constructors & Destructor
Eter::Wizards::Wizards() :
	name("Unknown"), mageType(MageType::FIRE), magicPowerUsed(false), etherCards(1), board(nullptr), username("Unknown") {}


Eter::Wizards::Wizards(std::string wizardName, MageType type, Board* gameBoard, std::string username) :
	name(wizardName), mageType(type), magicPowerUsed(false), etherCards(1), board(gameBoard), username(username) {}


Eter::Wizards::Wizards(const Wizards& other) :
	name(other.name), mageType(other.mageType), magicPowerUsed(other.magicPowerUsed), etherCards(other.etherCards), board(other.board) {}

const std::string& Eter::Wizards::GetUserName() const
{
	return username;
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

void Eter::Wizards::earthMasterPower(int powerIndex, int row, int col, std::vector<int>& playerHand)
{
	if (powerIndex == 1) 
		coverOpponentCard();
	
	else if (powerIndex == 2) 
		createPit();
	
}

void Eter::Wizards::airMasterPower(int powerIndex, int row, int col)
{
	if (powerIndex == 1) 
		moveOwnStack();
	
	else if (powerIndex == 2) 
		gainExtraEtherCard();
	
}

void Eter::Wizards::waterMasterPower(int powerIndex, int srcRow, int srcCol, int destRow)
{
	if (powerIndex == 1) 
		moveOpponentStack();
	
	else if (powerIndex == 2) 
		moveEdgeRow();
	
}

// Methods for powers
void Eter::Wizards::eliminateRow(int row) 
{
	// Verify if the row is valid
	if (row < 0 || row >= board->GetCurrentSize()) {
		std::cout << "Invalid row index.\n";
		return;
	}

	// Verify if the row has at least 3 positions 
	if (board->GetCurrentSize() < 3) {
		std::cout << "Row must have at least 3 positions.\n";
		return;
	}

	bool hasOwnCard = false;
	auto &gameBoard = board->GetBoardReference();

	// Verify every column of the row
	for (int col = 0; col < board->GetCurrentSize(); ++col) {
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
	for (int col = 0; col < board->GetCurrentSize(); ++col) {
		if (gameBoard[row][col].has_value()){

		    Tile& tile = gameBoard[row][col].value();
			tile.RemoveStack();
		}
	}

	std::cout << "Row " << row << " has been eliminated.\n";
}

void Eter::Wizards::eliminateCol(int col)
{
	// Verify if the col is valid
	if (col < 0 || col >= board->GetCurrentSize()) {
		std::cout << "Invalid col index.\n";
		return;
	}

	// Verify if the col has at least 3 positions 
	if (board->GetCurrentSize() < 3) {
		std::cout << "Col must have at least 3 positions.\n";
		return;
	}

	bool hasOwnCard = false;
	auto& gameBoard = board->GetBoardReference();

	// Verify every row of the column
	for (int row = 0; row < board->GetCurrentSize(); ++row) {
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
	for (int row = 0; row < board->GetCurrentSize(); ++row) {
		if (gameBoard[row][col].has_value()) {

			Tile& tile = gameBoard[row][col].value();
			tile.RemoveStack();
		}
	}

	std::cout << "Column " << col << " has been eliminated.\n";
}

void Eter::Wizards::eliminateOpponentCard(int row, int col)
{
	auto &gameBoard = board->GetBoardReference();
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











