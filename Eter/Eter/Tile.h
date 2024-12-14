#pragma once
#include <deque>
#include <ostream>
#include <optional>
#include "Piece.h"
namespace Eter
{
	class Tile
	{
	public:
		
		//Constructors
		Tile() : m_isPit{ false } {};
		~Tile() = default;
		Tile(const Tile& tile) : m_value(tile.m_value), m_isPit{false} {}
		Tile(const Piece& piece); // Constructor to initialize with a Piece
		Tile(const char& value); // Constructor to initialize with a char no username provided add MANUALLY!!!
		Tile& operator=(const Tile&) = default;

		// Getter
		std::deque<Piece> GetValue() const;
		Piece GetTopValue()const;

		//Setter
		void SetValue(const Piece& piece);
		void SetAsPit();

		//Methods
		friend std::ostream& operator<<(std::ostream& os, const Tile& tile); // Print top piece value
		void RemoveStack();
		Tile& operator=(const Piece& piece);
		bool IsPit() const;

	private:
		std::deque<Piece> m_value;
		bool m_isPit;
	};

}

