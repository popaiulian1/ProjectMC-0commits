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
	void ChooseGameType(int input);
};

