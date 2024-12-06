#include "WizardDuelMode.h"

#pragma region Constructors
Eter::WizardDuelMode::WizardDuelMode(
	const Player& player1, 
	const Player& player2, 
	const Board& board, 
	const GameType& gameType, 
	const Wizards& wizard) : Game(player1, player2, board, gameType), m_wizard(wizard)
{
}

Eter::WizardDuelMode::WizardDuelMode(WizardDuelMode&& other) noexcept
{
	SetPlayer1(other.GetPlayer1());
	SetPlayer2(other.GetPlayer2());
	SetBoard(other.GetBoard());
	SetGameType(other.GetGameType());
	m_wizard = std::move(other.m_wizard);

	other.SetPlayer1(Player());
	other.SetPlayer2(Player());
	other.SetBoard(Board());
	other.SetGameType(GameType::Practice);
	other.m_wizard = Wizards();
}

Eter::WizardDuelMode::WizardDuelMode(const WizardDuelMode& other)
{
	SetPlayer1(other.GetPlayer1());
	SetPlayer2(other.GetPlayer2());
	SetBoard(other.GetBoard());
	SetGameType(other.GetGameType());
	m_wizard = other.m_wizard;
}

Eter::WizardDuelMode& Eter::WizardDuelMode::operator=(const WizardDuelMode& other)
{
	if (this != &other)
	{
		SetPlayer1(other.GetPlayer1());
		SetPlayer2(other.GetPlayer2());
		SetBoard(other.GetBoard());
		SetGameType(other.GetGameType());
		m_wizard = other.m_wizard;
	}
	return *this;
}
#pragma endregion Constructors

#pragma region Getters
Eter::Wizards Eter::WizardDuelMode::GetWizard() const
{
	return m_wizard;
}
#pragma endregion Getters

#pragma region Setters
void Eter::WizardDuelMode::SetWizard(const Wizards& wizard)
{
	m_wizard = wizard;
}
#pragma endregion Setters

#pragma region Methods
void Eter::WizardDuelMode::StartGame()
{

}
#pragma endregion Methods


