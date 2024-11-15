#pragma once
#include <cstdint>
#include <vector>;
#include <string>;
#include <ostream>
#include <optional>
#include "Tile.h"

namespace Eter {
	constexpr size_t kBOARD_SIZE_DUEL{ 4 }; // constexpr to define the size of the 4x4 board
	constexpr size_t kBOARD_SIZE_PRACTICE{ 3 }; // constexpr to define the size of the 3x3 board
	constexpr char kEMPTY_BOARD_CELL{ '_' }; // constexpr to define the empty cell of the board


	enum class GameType {
		Practice,
		Duel
	};

	class Board
	{
	public:
		using Position = std::pair<size_t, size_t>;
		Board() = default;
		~Board() = default;
		Board(const Board&) = default;
		Board(const GameType& gameType);
		Board& operator=(const Board&) = default;
		friend std::ostream& operator<<(std::ostream& os, const Board& board);
		std::vector<std::vector<std::optional<Tile>>> GetBoard() const;
		std::vector<std::vector<std::optional<Tile>>>& GetBoardReference();
		size_t GetMaxSize() const;
		size_t GetCurrentSize() const;
		void SetBoard(const std::vector<std::vector<std::optional<Tile>>>& board);
		void SetTileValue(uint8_t x, uint8_t y, Piece &piece);
		std::optional<Tile>& operator[](const Position& pos);
		const std::optional<Tile>& operator[](const Position& pos) const;

	private:
		void IncreaseBoardSize();
		bool CheckEmptyTiles(); // returns true if there are empty tiles on the board.
		std::vector<std::vector<std::optional<Tile>>> m_board;
		size_t m_maxSize;
	};
}




