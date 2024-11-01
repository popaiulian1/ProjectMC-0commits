#include "Elemental.h"
#include <algorithm>
Eter::Elemental::Elemental() : m_board{ nullptr }, m_ElementalCardUsed{ false }, m_nameCard{ElementalCardName::NONE}
{}

Eter::Elemental::Elemental(const Board* board, bool ElementalCardUsed, ElementalCardName nameCard) : m_board{ board }, m_ElementalCardUsed{ ElementalCardUsed }, m_nameCard{ nameCard }
{}

Eter::Elemental::Elemental(const Elemental & other) : m_board{ other.m_board }, m_ElementalCardUsed{ other.m_ElementalCardUsed }, m_nameCard{ other.m_nameCard }
{}

//void Eter::Elemental::Tide(int row1, int column1, int row2, int column2) //Change positions of 2 different cards or stacks of cards.
//{
//
//	//row1, column1 -> coordinates of the first tile
//	//row2, column2 -> coordinates of the second tile
//	if (row1 < 0 || row1 >= m_board->getNumRows()) 
//	{
//		std::cout << "Invalid row index!" << "\n";
//		return;
//	}
//	else if (row2 < 0 || row2 >= m_board->getNumRows()) 
//	{
//		std::cout << "Invalid row index!" << "\n";
//		return;
//	}
//	else if (column1 < 0 || column1 >= m_board->getNumColumns()) {
//		std::cout << "Invalid column index!" << "\n";
//		return;
//	}
//	else if (column2 < 0 || column2 >= m_board->getNumColumns()) {
//		std::cout << "Invalid column index!" << "\n";
//		return;
//	}
//	std::swap(m_board->getBoard()[row1][column1], m_board->getBoard()[row2][column2]);
//}
//
//void Eter::Elemental::Storm(int row, int column) //Remove from play any stack of minimum 2 cards
//{ 
//	if (m_board->tileStack.size() >= 2) 
//	{
//		m_board->removeStack(row, column);
//		m_ElementalCardUsed = true;
//	}
//	else
//	{
//		std::cout << "The stack has less the 2 cards!";
//	}
//}


