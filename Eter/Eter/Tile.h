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
		Tile() : m_value{ std::deque<Piece>() }, m_isPit{false} {};
		~Tile() = default;
		Tile(const Tile& tile) : m_value(tile.m_value), m_isPit{tile.m_isPit} {}
		Tile(const Piece& piece); // Constructor to initialize with a Piece
		Tile(const char& value); // Constructor to initialize with a char no username provided add MANUALLY!!!
		Tile(Tile&&) noexcept = default;
		Tile& operator=(const Tile&) = default;
		Tile& operator=(Tile&&) noexcept = default; 

		// Getter
		std::deque<Piece> GetValue() const;
		std::deque<Piece>& GetValueRef();
		Piece GetTopValue() const;
		Piece& GetTopValueRef();

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
		bool m_isPit = false;
	};

	void to_json(nlohmann::json& j, const Tile& t);
}

