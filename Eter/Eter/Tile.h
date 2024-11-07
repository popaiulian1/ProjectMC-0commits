#pragma once
#include <stack>
#include <ostream>
#include <optional>

class Tile
{
public:
	Tile() = default;
	~Tile() = default;
	Tile(const Tile& tile) : m_value(tile.m_value){}// copy constructor (used in the board class to copy the tile value from one tile to another
	Tile(const char& value);
	Tile& operator=(const Tile&) = default;
	std::stack<char> GetValue() const; // returns the stack of tiles.
	char GetTopValue() const; // returns the top value of the stack.
	void SetValue(char value);
	friend std::ostream& operator<<(std::ostream& os, const Tile& tile); // overloading the << operator to print the top value of the stack.
private:
	std::stack<char> m_value; // tile value transformed into a stack to be able to add more values on top of eachother (ex. piece with value 2 over piece with value 1).
};

