#pragma once
#include "WizardDuelMode.h"
#include "ElementalBattleMode.h"

namespace Eter {
	class WizzardAndElementalMode : public Eter::WizardDuelMode, public Eter::ElementalBattleMode
	{
	public:
		//Constructors
		WizzardAndElementalMode() : Game(), WizardDuelMode(), ElementalBattleMode() {};
		WizzardAndElementalMode(
			const Player& player1,
			const Player& player2,
			Board& board,
			const GameType& gameType,
			Wizards& wizardPlayer1,
			Wizards& wizardPlayer2,
			Elemental& m_elementCard1,
			Elemental& m_elementCard2
		);
		~WizzardAndElementalMode() = default;
		WizzardAndElementalMode(WizzardAndElementalMode&& other) noexcept;
		WizzardAndElementalMode(const WizzardAndElementalMode& other);
		WizzardAndElementalMode& operator=(const WizzardAndElementalMode& other);

		//Methods
		void StartGame() override;
		void PlayGame() override;
		void Illusion(Player& player) override;
		void PlayEterCard(Player& player);
		void HandleWizzardType() override;
		void SetWizzardType() override;

	private:
		size_t m_rounds = 1;
		Elemental m_elementCard1;
		Elemental m_elementCard2;
		Wizards m_wizardPlayer1;
		Wizards m_wizardPlayer2;
		Wizards* m_currentWizard = nullptr;
		Player* m_currentPlayer = nullptr;
		bool firstMove = true;
	};
}



