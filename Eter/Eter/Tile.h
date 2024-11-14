#pragma once
#include <stack>
#include <ostream>
#include <optional>
#include "Piece.h"
namespace Eter 
{
class Tile
{
public:
	Tile() = default;
	~Tile() = default;
	Tile(const Tile& tile) : m_value(tile.m_value){} // Copy constructor
	Tile(const Piece& piece); // // Constructor to initialize with a Piece
	Tile(const char& value); // Constructor to initialize with a char
	Tile& operator=(const Tile&) = default;
	std::stack<Piece> GetValue() const; // Returns the stack of pieces
	Piece GetTopValue() const; // Returns the top piece of the stack
	void SetValue(const Piece& piece);
	friend std::ostream& operator<<(std::ostream& os, const Tile& tile); // Print top piece detailes
	void RemoveStack();
private:
	std::stack<Piece> m_value; // Stack of pieces on the tile
};

}

