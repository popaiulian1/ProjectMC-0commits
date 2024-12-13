#pragma once
#include "Player.h"
#include "Board.h"

namespace Eter
{
	class Game
	{
	public:

		//Constructors
		Game();
		~Game() = default;
		Game(const Game&) = default;
		Game& operator=(const Game&) = default;
		Game(const Player& player1, const Player& player2, const Board& board, const GameType& gameType);

		//Getters
		Player& GetPlayer1Reference();
		Player GetPlayer1() const;
		Player& GetPlayer2Reference();
		Player GetPlayer2() const;
		Board GetBoard() const;
		Board& GetBoardReference();
		GameType GetGameType() const;
		const std::string& GetBluePlayerName() const;


		//Setters
		void SetPlayer1(const Player& player);
		void SetPlayer2(const Player& player);
		void SetBoard(const Board& board);
		void SetGameType(const GameType& gameType);
		void SetBluePlayerName(const std::string& name);

		//Methods
		virtual void StartGame();
		void InitializePracticeGame();
		void UsernameHandling();
		void ResetPlayerData(Player& player);
		void PrintWinner(const Player& player) const;
		virtual void PlayGame();
		bool CheckWinner();
		void TotalScore(Player& player, const Board& board);
		virtual void Illusion(Player& player);
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
		std::string m_bluePlayerName;
	};
}

