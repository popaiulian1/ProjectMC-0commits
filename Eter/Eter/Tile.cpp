#include "Tile.h"

Tile::Tile(const char& value)
{
	m_value.emplace(value);
}

std::stack<char> Tile::GetValue() const
{
	return m_value;
}

char Tile::GetTopValue() const
{
	return m_value.top();
}

void Tile::SetValue(char value)
{
	m_value.emplace(value);
}

std::ostream& operator<<(std::ostream& os, const Tile& tile)
{
	os << tile.GetTopValue();
	return os;
}
