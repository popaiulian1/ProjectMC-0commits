#pragma once
#include "Game.h"
#include "Wizards.h"
#include <random>
#include <regex>

namespace Eter {
	class WizardDuelMode : virtual public Eter::Game, public Eter::Wizards
	{
	public:
		// Constructors
		WizardDuelMode() : Game(), Wizards() {};
		WizardDuelMode(
			const Player& player1,
			const Player& player2,
			Board& board,
			const GameType& gameType,
			Wizards& wizardPlayer1,
			Wizards& wizardPlayer2
		);
		~WizardDuelMode() = default;
		WizardDuelMode(WizardDuelMode&& other) noexcept;
		WizardDuelMode(const WizardDuelMode& other);
		WizardDuelMode& operator=(const WizardDuelMode& other);
	

		// Getters
		Wizards GetWizardPlayer1() const;
		Wizards GetWizardPlayer2() const;

		// Setters
		void SetWizardPlayer1(const Wizards& wizard);
		void SetWizardPlayer2(const Wizards& wizard);
	

		// Methods
		void StartGame() override;
		void PlayGame() override;
		void Illusion(Player& player) override;
		void UsernameHandling();
		void InitializeWizzardDuelGame();
		virtual void SetWizzardType();
		void PlayEterCard(Player& Player);
		virtual void HandleWizzardType();
		void CreateFromJsonWizard(const nlohmann::json& gameInfo);
		void ExportToJsonWizard();
		int Random(const std::pair<int, int>& distance);
	

	private:
		// Methods
		void addBorderToMatrix(Eter::BoardMatrix& board);
		bool checkAdjacent(const Eter::Board::Position& pos, const Eter::Piece& pieceToBeAdded);
	

		// Variables
		static const size_t kDECK_SIZE_DUEL{ 10 }; //define the size of the duel deck
		Wizards m_wizardPlayer1;
		Wizards m_wizardPlayer2;
		Wizards* m_currentWizard = nullptr;
		Player* m_currentPlayer = nullptr;
		size_t m_rounds = 1;
		bool firstMove = true;
	
	};

}


