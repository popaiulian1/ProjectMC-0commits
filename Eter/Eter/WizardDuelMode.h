#pragma once
#include "Game.h"
#include "Wizards.h"

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
			const Wizards& wizard
		);
		~WizardDuelMode() = default;
		WizardDuelMode(WizardDuelMode&& other) noexcept;
		WizardDuelMode(const WizardDuelMode& other);
		WizardDuelMode& operator=(const WizardDuelMode& other);
	#pragma endregion Constructors

	#pragma region Getters
		Wizards GetWizard() const;
	#pragma endregion Getters

	#pragma region Setters
		void SetWizard(const Wizards& wizard);
	#pragma endregion Setters

	#pragma region Methods
		void StartGame() override;
		
	#pragma endregion Methods

	private:
		Wizards m_wizard;
	};

}


