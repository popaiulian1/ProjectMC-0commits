#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include <ostream>
#include <optional>
#include "Tile.h"
#include "Player.h"

namespace Eter {
	constexpr size_t kBOARD_SIZE_DUEL{ 4 }; // constexpr to define the size of the 4x4 board
	constexpr size_t kBOARD_SIZE_PRACTICE{ 3 }; // constexpr to define the size of the 3x3 board
	constexpr char kEMPTY_BOARD_CELL{ '_' }; // constexpr to define the empty cell of the board

	using BoardVector = std::vector<std::optional<Tile>>;
	using BoardMatrix = std::vector<BoardVector>;

	enum class GameType {
		Practice,
		Duel
	};

	class Board
	{
	public:
		using Position = std::pair<int8_t, int8_t>;

		Board() = default;
		~Board() = default;
		Board(const Board&) = default;
		Board(const GameType& gameType);
		Board& operator=(const Board&) = default;
		friend std::ostream& operator<<(std::ostream& os, const Board& board);
		BoardMatrix GetBoard() const;
		BoardMatrix& GetBoardReference();
		size_t GetMaxSize() const;
		size_t GetCurrentSize() const;
		void SetBoard(const BoardMatrix& board);
		void SetTileValue(const Position& pos, const char& value, const Player& player);
		std::optional<Tile>& operator[](const Position& pos);
		const std::optional<Tile>& operator[](const Position& pos) const;

	private:
		void IncreaseBoardSize(const Position& pos);
		bool CheckEmptyTiles(); // returns true if there are empty tiles on the board.
		BoardMatrix m_board;
		size_t m_maxSize;
	};
}




