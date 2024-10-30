#include "Wizards.h"
#include "Board.h"
#include <iostream>
 
//Constructors & Destructor
Eter::Wizards::Wizards() :
	name("Unknown"), mageType(MageType::FIRE), magicPowerUsed(false), etherCards(1), board(nullptr) {}


Eter::Wizards::Wizards(std::string wizardName, MageType type, const Board* gameBoard) : 
	name(wizardName), mageType(type), magicPowerUsed(false), etherCards(1), board(gameBoard) {}


Eter::Wizards::Wizards(const Wizards& other) :
	name(other.name), mageType(other.mageType), magicPowerUsed(other.magicPowerUsed), etherCards(other.etherCards), board(other.board) {}

// Determination of Power 
void Eter::Wizards::fireMasterPower(int powerIndex, int row, int col)
{
	if (powerIndex == 1) 
		eliminateOpponentCard(row, col);
	
	else if (powerIndex == 2) 
		eliminateRow(row);
	
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
/*
void Eter::Wizards::eliminateOpponentCard(int row, int col)
{
	if (board->isOpponentCard(row, col) && board->)
	{ // We verify if the card at (row, col) is the opponent's card & the card under it is ours
		board->removeCard(row, col);       // We eliminate the card that is at (row, col) on the board
		std::cout << "The opponent's card at (" << row << ", " << col << ") has been removed.\n";
	}
}
*/








