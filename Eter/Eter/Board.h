#pragma once
#include <cstdint>
#include <vector>;
#include <string>;
#include <ostream>

namespace Eter {
	constexpr uint8_t BOARD_SIZE_DUEL = 4;;
	constexpr uint8_t BOARD_SIZE_PRACTICE = 3;

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
		
	private:
		std::vector<std::vector<char>> m_board;
	};
}




