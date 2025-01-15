#pragma once
#include "Elemental.h"
#include "Game.h"

namespace Eter {
	class ElementalBattleMode : public Eter::Elemental, public Eter::Game
	{
	public:
	#pragma region Constructors
		ElementalBattleMode() : Elemental(), Game() {};
		ElementalBattleMode(
			const Player& player1,
			const Player& player2,
			Board& board, 
			Elemental& m_elementPlayer1,
			Elemental& m_elementPlayer2,
			const GameType& gameType
		);
		~ElementalBattleMode() = default;
		ElementalBattleMode(ElementalBattleMode&& other) noexcept;
		ElementalBattleMode(const ElementalBattleMode& other);
		ElementalBattleMode& operator=(const ElementalBattleMode& other);
	#pragma endregion Constructors


	#pragma region Getters
		Elemental GetElementPlayer1() const;
		Elemental GetElementPlayer2() const;
	#pragma endregion Getters


	#pragma region Setters
		void SetElementPlayer1(const Elemental& element);
		void SetElementPlayer2(const Elemental& element);
	#pragma endregion Setters

	#pragma region Methodes
		void StartGame() override;
		void UsernameHandling();
		void InitializeElementalBattleGame();
		void SetElementalType();
	#pragma endregion Methodes

	private:
	#pragma region Methodes
		int Random(const std::pair<int, int>& distance);
		void addBorderToMatrix(Eter::BoardMatrix& board);
		bool checkAdjacent(const Eter::Board::Position& pos, const Eter::Piece& pieceToBeAdded);
	#pragma region Methodes

	#pragma region Variables
		static const size_t kDECK_SIZE_DUEL{ 10 };
		Elemental m_elementPlayer1;
		Elemental m_elementPlayer2;
		Elemental* m_currentElement = nullptr;
		Player* m_currentPlayer = nullptr;
		size_t m_rounds = 1;
		bool firstMove = true;
	#pragma endregion Variables
	};
}


