#include "Tile.h"

Tile::Tile()
{
	m_value.emplace('_');
	m_isEmpty = true;

}

std::stack<char> Tile::getValue() const
{
	return m_value;
}

char Tile::getTopValue() const
{
	return m_value.top();
}

void Tile::setValue(char value)
{
	m_value.emplace(value);
}

bool Tile::isEmpty() const
{
	return m_isEmpty;
}

void Tile::setIsEmpty(bool isEmpty)
{
	m_isEmpty = isEmpty;
}

std::ostream& operator<<(std::ostream& os, const Tile& tile)
{
	os << tile.getTopValue();
	return os;
}
