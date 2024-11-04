#pragma once
#include <stack>
#include <ostream>

class Tile
{
public:
	Tile();
	~Tile() = default;
	Tile(const Tile&) = default;
	Tile& operator=(const Tile&) = default;
	std::stack<char> getValue() const; // returns the stack of tiles.
	char getTopValue() const; // returns the top value of the stack.
	void setValue(char value); 
	bool isEmpty() const; 
	void setIsEmpty(bool isEmpty); // sets the value of m_isEmpty.
	friend std::ostream& operator<<(std::ostream& os, const Tile& tile); // overloading the << operator to print the top value of the stack.
private:
	std::stack<char> m_value; // tile value transformed into a stack to be able to add more values on top of eachother (ex. piece with value 2 over piece with value 1).
	bool m_isEmpty;
};

