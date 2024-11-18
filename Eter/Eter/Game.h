#pragma once
#include "Player.h"
#include "Board.h"

namespace Eter
{
	class Game
	{
	public:
		Game() = default;
		~Game() = default;
		Game(const Game&) = default;
		Game& operator=(const Game&) = default;
		Game(const Player& player1, const Player& player2, const Board& board, const GameType& gameType);

		void StartGame(Player& player1, Player& player2, Board& board);
		void PrintBoard() const;
		void PrintWinner(const Player &player) const;
		void PlayGame();
		bool CheckWinner();
		int TotalScore(Player& player, const Board& board);
		bool CheckDraw() const;
		void Illusion(Player& player, Board& board);
		void SetPlayer1(const Player& player);
		void SetPlayer2(const Player& player);
		void SetBoard(const Board& board);
		Player GetPlayer1() const;
		Player GetPlayer2() const;
		Board GetBoard() const;
	private:
		static const size_t kDECK_SIZE_PRACTICE{ 7 }; //define the size of the practice deck
		Player m_player1, m_player2;
		Board m_board;
		GameType m_gameType;
	};
}

