#pragma once
#include "Game.h"
#include "Wizards.h"
#include <random>
#include <regex>

namespace Eter {
	class WizardDuelMode : public Eter::Game, public Eter::Wizards
	{
	public:
	#pragma region Constructors
		WizardDuelMode() : Game(), Wizards() {};
		WizardDuelMode(
			const Player& player1,
			const Player& player2,
			const Board& board,
			const GameType& gameType,
			const Wizards& wizardPlayer1,
			const Wizards& wizardPlayer2
		);
		~WizardDuelMode() = default;
		WizardDuelMode(WizardDuelMode&& other) noexcept;
		WizardDuelMode(const WizardDuelMode& other);
		WizardDuelMode& operator=(const WizardDuelMode& other);
	#pragma endregion Constructors

	#pragma region Getters
		Wizards GetWizardPlayer1() const;
		Wizards GetWizardPlayer2() const;
	#pragma endregion Getters

	#pragma region Setters
		void SetWizardPlayer1(const Wizards& wizard);
		void SetWizardPlayer2(const Wizards& wizard);
	#pragma endregion Setters

	#pragma region Methods
		void StartGame() override;
		void PlayGame() override;
		void Illusion(Player& player) override;
		void PlayEterCard(Player& Player);
	#pragma endregion Methods

	private:
	#pragma region Methods
		int Random(const std::pair<int, int>& distance);
	#pragma endregion Methods

	#pragma region Variables
		static const size_t kDECK_SIZE_DUEL{ 10 }; //define the size of the duel deck
		Wizards m_wizardPlayer1;
		Wizards m_wizardPlayer2;
		Wizards* m_currentWizard = nullptr;
		Player* m_currentPlayer = nullptr;
		size_t m_rounds = 1;
	#pragma endregion Variables
	};

}


