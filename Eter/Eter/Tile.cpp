#include "Tile.h"

Tile::Tile()
{
	m_value = '_';
	m_isEmpty = true;

}

char Tile::getValue() const
{
	return m_value;
}

void Tile::setValue(char value)
{
	m_value = value;
}

bool Tile::isEmpty() const
{
	return m_isEmpty;
}

void Tile::setIsEmpty(bool isEmpty)
{
	m_isEmpty = isEmpty;
}