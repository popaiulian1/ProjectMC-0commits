#include "Piece.h"

Eter::Piece::Piece()
{
	m_value = 0;
	m_isPlaced = false;
}

Eter::Piece::Piece(const int& value,const bool& isPlaced) : m_value{ value }, m_isPlaced { isPlaced } 
{}

int Eter::Piece::GetValue() const
{
	return m_value;
}

bool Eter::Piece::GetIsPlaced() const
{
	return m_isPlaced;
}

void Eter::Piece::SetValue(const int& value)
{
	m_value = value;
}

void Eter::Piece::SetIsPlaced(const bool& isPlaced)
{
	m_isPlaced = isPlaced;
}



