#include "Elemental.h"

Eter::Elemental::Elemental() : m_board{ nullptr }, m_ElementalCardUsed{ false }, m_nameCard{ElementalCardName::NONE}
{}

Eter::Elemental::Elemental(const Board* board, bool ElementalCardUsed, ElementalCardName nameCard) : m_board{ board }, m_ElementalCardUsed{ ElementalCardUsed }, m_nameCard{ nameCard }
{}

Eter::Elemental::Elemental(const Elemental & other)
{
	m_board = other.m_board;
	m_ElementalCardUsed = other.m_ElementalCardUsed;
	m_nameCard = other.m_nameCard;
}


