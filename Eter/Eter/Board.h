#pragma once
#include <cstdint>
#include <vector>;
#include <string>;
#include <ostream>
#include "Tile.h"

namespace Eter {
	constexpr uint8_t BOARD_SIZE_DUEL = 4; // constexpr to define the size of the 4x4 board
	constexpr uint8_t BOARD_SIZE_PRACTICE = 3; // constexpr to define the size of the 3x3 board

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

		void setTileValue(uint8_t x, uint8_t y, char value);

	private:
		void increaseBoardSize();
		bool checkEmptyTiles(); // returns true if there are empty tiles on the board.
		std::vector<std::vector<Tile>> m_board;
		uint8_t m_maxSize;
	};
}




