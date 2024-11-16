#include "Elemental.h"
#include <algorithm>
#include "Board.h"
#include "Tile.h"

Eter::Elemental::Elemental(const Board board, bool ElementalCardUsed, ElementalCardName nameCard) : m_board{ board }, m_ElementalCardUsed{ ElementalCardUsed }, m_nameCard{ nameCard }
{}

Eter::Elemental::Elemental(const Elemental & other) : m_board{ other.m_board }, m_ElementalCardUsed{ other.m_ElementalCardUsed }, m_nameCard{ other.m_nameCard }
{}

void Eter::Elemental::Tide(int row1, int column1, int row2, int column2) //Change positions of 2 different cards or stacks of cards.
{
	//row1, column1 -> coordinates of the first tile
	//row2, column2 -> coordinates of the second tile
	if (row1 < 0 || row1 >= m_board.GetCurrentSize())
	{
		throw std::out_of_range{ "Invalid row index!" };
	}
	else if (row2 < 0 || row2 >= m_board.GetCurrentSize())
	{
		throw std::out_of_range{ "Invalid row index!" };
	}
	else if (column1 < 0 || column1 >= m_board.GetCurrentSize()) {
		throw std::out_of_range{ "Invalid column index!" };
	}
	else if (column2 < 0 || column2 >= m_board.GetCurrentSize()) {
		throw std::out_of_range{ "Invalid column index!" };
	}

	//swap between card / stack of cards.
	std::swap(m_board[{row1, column1}], m_board[{row2, column2}]);
}

void Eter::Elemental::Earthquake(const Board& board)
{
	auto GameBoard = board.GetBoard();
	for (auto& row : GameBoard)
	{
		for (auto& tile : row)
		{
			if (tile.value().GetTopValue().GetValue() == '1')
				tile.value().GetValue().pop();
		}
	}
	
}

void Eter::Elemental::Destruction(const Player& opponent)
{
	Piece lastCardPlayed = opponent.GetLastPlayedCard();

}

void Eter::Elemental::Storm(int row, int column) //Remove from play any stack of minimum 2 cards
{ 
	uint8_t StackSize = m_board[{row, column}].value().GetValue().size();
	if (StackSize >= 2)
	{
		while (!m_board.GetBoard().empty())
			m_board.GetBoard().pop_back();
		m_ElementalCardUsed = true;
	}
	else
	{
		throw std::out_of_range{"The stack has less then 2 cards!"};
	}
}


