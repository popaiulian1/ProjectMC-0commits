#pragma once
#include "Player.h"
#include "Board.h"

namespace Eter
{
	class Game
	{
	public:

		//Constructors
		Game() = default;
		~Game() = default;
		Game(const Game&) = default;
		Game& operator=(const Game&) = default;
		Game(const Player& player1, const Player& player2, const Board& board, const GameType& gameType);

		//Getters
		Player GetPlayer1() const;
		Player GetPlayer2() const;
		Board GetBoard() const;

		//Setters
		void SetPlayer1(const Player& player);
		void SetPlayer2(const Player& player);
		void SetBoard(const Board& board);

		//Methods
		void StartGame();
		void PrintWinner(const Player& player) const;
		void PlayGame();
		bool CheckWinner();
		void TotalScore(Player& player, const Board& board);
		void Illusion(Player& player);
		bool CheckCompleteRowOrColumn() const;
		
		
	private:
		//Methods
		void addBorderToMatrix(Eter::BoardMatrix& board);
		bool checkAdjacent(const Eter::Board::Position& pos, const Eter::Piece& pieceToBeAdded);

		//Constants
		static const size_t kDECK_SIZE_PRACTICE{ 7 }; //define the size of the practice deck
		Player m_player1, m_player2;
		Player* m_currentPlayer = nullptr;
		Board m_board;
		GameType m_gameType;
		size_t m_rounds = 1;
	};
}

