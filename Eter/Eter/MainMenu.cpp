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
		std::cout << "\n ========== LOAD/SAVE GAME ========== \n";
		std::string path = "./SaveGames/";
		int number = 0;
		std::vector<std::string> fileNames;
		try {
			for (const auto& entry : std::filesystem::directory_iterator(path)) {
				std::cout << std::to_string(number) + ". " + entry.path().filename().string() << std::endl;
				fileNames.emplace_back(entry.path().filename().string());
				number++;
			}
		}
		catch (std::filesystem::filesystem_error& e){
			std::cerr << "Error: " << e.what() << std::endl;
		}

		int chooseSaveGame;
		std::cout << "\n -> Enter one of the numbers to select the savegame that you want: ";
		std::cin >> chooseSaveGame;
		nlohmann::json gameInfo = Eter::LoadSaveFile(fileNames[chooseSaveGame]);

		CreateTheLoadedGame(gameInfo);
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

void MainMenu::CreateTheLoadedGame(const nlohmann::json& gameInfo)
{
	int gameTypeSelect;
	gameInfo["gameInfo"].at("gameType").get_to(gameTypeSelect);

	switch (gameTypeSelect)
	{
	case 0:
		StartPractice(gameInfo);
		break;
	case 1:
		StartWizardDuel(gameInfo);
		break;
	case 2:
		StartElementalDuel(gameInfo);
		break;
	default:
		break;
	}
}

void MainMenu::StartPractice(const nlohmann::json& gameInfo)
{
	Eter::Game game;
	game.CreateFromJson(gameInfo);
}

void MainMenu::StartWizardDuel(const nlohmann::json& gameInfo)
{
	Eter::WizardDuelMode game;
	game.CreateFromJsonWizard(gameInfo);
}

void MainMenu::StartElementalDuel(const nlohmann::json& gameInfo)
{
	Eter::ElementalBattleMode game;
	game.CreateFromJsonElemental(gameInfo);
}
