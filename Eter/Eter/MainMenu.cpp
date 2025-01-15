#include "MainMenu.h"

void MainMenu::Start()
{
	int chooseStart;

	PrintMenu();
	std::cin >> chooseStart;
	
	std::cout << "\n";

	if (chooseStart == 1) {
		PrintGameTypeMenu();
		int chooseGameType;
		std::cin >> chooseGameType;
		if (chooseGameType == 1) {
			Eter::Game game;
			game.StartGame();
		}
		else if (chooseGameType == 2) {
			Eter::WizardDuelMode game;
			game.StartGame();
		}
		else if (chooseGameType == 3) {
			Eter::ElementalBattleMode game;
			game.StartGame();
		}
		else {
			std::cout << "\n";
			Start();
		}
	}
	else if (chooseStart == 2) {
		std::cout << "\n ========== TO FINISH LOAD/SAVE GAME ========== \n";
	}
	else {
		return;
	}
	
}

void MainMenu::PrintMenu()
{
	std::cout << "1. Start New Game\n";
	std::cout << "2. Load Game\n";
	std::cout << "0. Exit\n";
}

void MainMenu::PrintGameTypeMenu()
{
	std::cout << "1. Practice Mode\n";
	std::cout << "2. Wizard Duel Mode\n";
	std::cout << "3. Elemental Duel Mode\n";
	std::cout << "0. Back\n";
}
