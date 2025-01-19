#pragma once
#include "Elemental.h"
#include "Game.h"

namespace Eter {
	class ElementalBattleMode : virtual public Eter::Game, public Eter::Elemental
	{
	public:
		// Constructors
		ElementalBattleMode() : Elemental(), Game() {};
		ElementalBattleMode(
			const Player& player1,
			const Player& player2,
			Board& board, 
			Elemental& m_elementCard1,
			Elemental& m_elementCard2,
			const GameType& gameType
		);
		~ElementalBattleMode() = default;
		ElementalBattleMode(ElementalBattleMode&& other) noexcept;
		ElementalBattleMode(const ElementalBattleMode& other);
		ElementalBattleMode& operator=(const ElementalBattleMode& other);
	
		// Getters
		Elemental GetElementPlayer1() const;
		Elemental GetElementPlayer2() const;

		// Setters
		void SetElementCard1(const Elemental& element);
		void SetElementCard2(const Elemental& element);


		// Methods
		void StartGame() override;
		void PlayGame() override;
		void Illusion(Player& player) override;
		void PlayEterCard(Player& player);
		void UsernameHandling();
		void InitializeElementalBattleGame();
		void SetElementalType();
		void HandleElementalType();
		void ElementalSelection(Elemental element);

		void CreateFromJsonElemental(const nlohmann::json& gameInfo);
		void ExportToJsonElemental();



	private:
		// Methods
		int Random(const std::pair<int, int>& distance);
		void addBorderToMatrix(Eter::BoardMatrix& board);
		bool checkAdjacent(const Eter::Board::Position& pos, const Eter::Piece& pieceToBeAdded);

		// Variables
		static const size_t kDECK_SIZE_DUEL{ 10 };
		Elemental m_elementCard1;
		Elemental m_elementCard2;
		Player* m_currentPlayer = nullptr;
		size_t m_rounds = 1;
		bool firstMove = true;
	};
}


