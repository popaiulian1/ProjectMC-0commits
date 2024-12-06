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
	std::cout << "This is the Mage Duel Mode\n";
	std::cout << "_____________________________\n";

	if(GetGameType() != Eter::GameType::Duel)
		SetGameType(Eter::GameType::Duel);
	
	SetBoard(Board(Eter::GameType::Duel));
	auto GameBoard = this->GetBoard().GetBoardReference();
	auto& Player1 = this->GetPlayer1Reference();
	auto& Player2 = this->GetPlayer2Reference();

	std::vector<char> Values = { '1', '1', '1', '2', '2', '2', '3', '3', '3', '4'}; // Define the values of the cards in the practice deck
	std::vector<Eter::Piece> CardsPractice;

	std::string UsernamePlayer1;
	std::string UsernamePlayer2;

	if (Player1.GetUserName() == "") {
		std::cout << "Username of the first player is: ";
		std::getline(std::cin, UsernamePlayer1);
		Player1.SetUserName(UsernamePlayer1);
		this->SetBluePlayerName(Player1.GetUserName());
	}

	if (Player2.GetUserName() == "") {
		std::cout << "Username of the second player is: ";
		std::getline(std::cin, UsernamePlayer2);
		Player2.SetUserName(UsernamePlayer2);
	}

	CardsPractice.resize(kDECK_SIZE_DUEL);

	int index = 0;
	bool EterCard = false;

	for (auto& card : CardsPractice) {
		card.SetValue(Values[index++]);
		card.SetIsPlaced(false);
		card.SetUserName("");
		card.SetIsIllusion(false);
		if (!EterCard) {
			card.SetEterCard(true);
			EterCard = true;
		}
		else
			card.SetEterCard(false);
	}

	Player1.SetPieces(CardsPractice);
	Player2.SetPieces(CardsPractice);
	Player1.SetIllusionPlayed(false);
	Player2.SetIllusionPlayed(false);
	Player1.SetScore(0);
	Player2.SetScore(0);
	Player1.SetGamesWon(0);
	Player2.SetGamesWon(0);

	PlayGame();
}
#pragma endregion Methods


