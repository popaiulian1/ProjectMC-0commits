#pragma once
#include <iostream>
#include "WizardDuelMode.h"
#include "Game.h"
#include "ElementalBattleMode.h"
class MainMenu
{
public:
	MainMenu() = default;
	~MainMenu() = default;
	void Start();
	void PrintMenu();
	void PrintGameTypeMenu();
	void CreateTheLoadedGame(const nlohmann::json& gameInfo);
	void StartPractice(const nlohmann::json& gameInfo);
	void StartWizardDuel(const nlohmann::json& gameInfo);
	void StartElementalDuel(const nlohmann::json& gameInfo);
};

