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
		Tile() : m_value{ std::deque<Piece>() }, m_isPit{ false } /*/m_isTileBlocked { false }*/ {};
		~Tile() = default;
		Tile(const Tile& tile) : m_value(tile.m_value), m_isPit{ tile.m_isPit } /*m_isTileBlocked{false}*/ {}
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
		//void SetTileBlocked(bool isBlocked);

		//Methods
		friend std::ostream& operator<<(std::ostream& os, const Tile& tile); // Print top piece value
		void RemoveStack();
		Tile& operator=(const Piece& piece);
		bool IsPit() const;
		//bool IsTileBlocked() const;

	private:
		std::deque<Piece> m_value;
		bool m_isPit = false;
		//bool m_isTileBlocked = false;
	};

	void to_json(nlohmann::json& j, const Tile& t);
	void from_json(const nlohmann::json& j, Tile& t);
}

