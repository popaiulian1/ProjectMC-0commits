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

	//Constructors
	Tile() = default;
	Tile() : isPit(false) {} // Default constructor to initialize isPit with false
	~Tile() = default;
	Tile(const Tile& tile) : m_value(tile.m_value){} // Copy constructor
	Tile(const Piece& piece); // // Constructor to initialize with a Piece
	Tile(const char& value); // Constructor to initialize with a char no username provided add manualy
	
	//Getters
	std::stack<Piece> GetValue() const; // Returns the stack of pieces
	Piece GetTopValue() const; // Returns the top piece of the stack

	//Setters
	void SetValue(const Piece& piece);
	void SetAsPit(); // Sets tile as a pit


	//Methods
	friend std::ostream& operator<<(std::ostream& os, const Tile& tile); // Print top piece detailes
	void RemoveStack();
	Tile& operator=(const Tile&) = default;
	bool IsPit() const; // Verify if Tile is pit

private:
	std::stack<Piece> m_value; // Stack of pieces on the tile
	bool isPit;
};

}

