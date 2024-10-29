#pragma once
#include <cstdint>
#include <vector>;
#include <string>;
#include <ostream>
#include "Tile.h"

namespace Eter {
	constexpr uint8_t BOARD_SIZE_DUEL = 4; // constexpr pentru a defini dimensiunea tablei 4x4
	constexpr uint8_t BOARD_SIZE_PRACTICE = 3; // constexpr pentru a defini dimensiunea tablei 3x3

	enum class GameType {
		Practice,
		Duel
	};

	class Board
	{
	public:
		Board() = default;
		~Board() = default;
		Board(const Board&) = default;
		Board(const GameType& gameType);
		Board& operator=(const Board&) = default;
		friend std::ostream& operator<<(std::ostream& os, const Board& board);
		std::vector<std::vector<Tile>> getBoard() const;
		void setBoard(const std::vector<std::vector<Tile>>& board);
	private:
		std::vector<std::vector<Tile>> m_board;
	};
}




