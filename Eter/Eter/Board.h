#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include <ostream>
#include <optional>
#include "Tile.h"

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

	struct lastMove {
		std::string playerUsername;
		size_t row;
		size_t column;
	};

	class Board
	{
	public:
		using Position = std::pair<int8_t, int8_t>;

		//Constructors
		Board() = default;
		~Board() = default;
		Board(const Board&) = default;
		Board(const GameType& gameType);
		Board& operator=(const Board& other);
		
		//Getters
		BoardMatrix GetBoard() const;
		BoardMatrix& GetBoardReference();
		size_t GetMaxSize() const;
		size_t GetCurrentSize() const;

		//Setters
		void SetBoard(const BoardMatrix& board);
		void SetTileValue(const Position& pos, const char& value, const std::string& playerName);
		void SetLastMove(const std::string& playerUsername, size_t row, size_t column);

		//Methods
		friend std::ostream& operator<<(std::ostream& os, const Board& board);
		void PrintBoardForFormatedOutput(const std::string& bluePlayerName) const;
		bool CheckEmptyTiles(); // returns true if there is atleast one empty tile on the board.
		bool PowerExplosionAvailability() const; //Checks if a Power Explosion can be played

	private:
		void IncreaseBoardForNegativeIndexes(const Position& pos);
		BoardMatrix m_board;
		size_t m_maxSize;
		lastMove m_lastMove;
	};
}




