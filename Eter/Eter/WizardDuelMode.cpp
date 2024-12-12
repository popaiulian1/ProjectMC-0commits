#include "WizardDuelMode.h"

#pragma region Constructors
Eter::WizardDuelMode::WizardDuelMode(
	const Player& player1, 
	const Player& player2, 
	const Board& board, 
	const GameType& gameType, 
	const Wizards& wizardPlayer1,
	const Wizards& wizardPlayer2) : Game(player1, player2, board, gameType), m_wizardPlayer1(wizardPlayer1), m_wizardPlayer2(wizardPlayer1)
{
}

Eter::WizardDuelMode::WizardDuelMode(WizardDuelMode&& other) noexcept
{
	SetPlayer1(other.GetPlayer1());
	SetPlayer2(other.GetPlayer2());
	SetBoard(other.GetBoard());
	SetGameType(other.GetGameType());
	m_wizardPlayer1 = std::move(other.m_wizardPlayer1);
	m_wizardPlayer2 = std::move(other.m_wizardPlayer2);

	other.SetPlayer1(Player());
	other.SetPlayer2(Player());
	other.SetBoard(Board());
	other.SetGameType(GameType::Practice);
	other.m_wizardPlayer1 = Wizards();
	other.m_wizardPlayer2 = Wizards();
}

Eter::WizardDuelMode::WizardDuelMode(const WizardDuelMode& other)
{
	SetPlayer1(other.GetPlayer1());
	SetPlayer2(other.GetPlayer2());
	SetBoard(other.GetBoard());
	SetGameType(other.GetGameType());
	m_wizardPlayer1 = other.m_wizardPlayer1;
	m_wizardPlayer2 = other.m_wizardPlayer2;
}

Eter::WizardDuelMode& Eter::WizardDuelMode::operator=(const WizardDuelMode& other)
{
	if (this != &other)
	{
		SetPlayer1(other.GetPlayer1());
		SetPlayer2(other.GetPlayer2());
		SetBoard(other.GetBoard());
		SetGameType(other.GetGameType());
		m_wizardPlayer1 = other.m_wizardPlayer1;
		m_wizardPlayer2 = other.m_wizardPlayer2;
	}
	return *this;
}
#pragma endregion Constructors

#pragma region Getters
Eter::Wizards Eter::WizardDuelMode::GetWizardPlayer1() const
{
	return m_wizardPlayer1;
}
Eter::Wizards Eter::WizardDuelMode::GetWizardPlayer2() const
{
	return m_wizardPlayer2;
}
#pragma endregion Getters

#pragma region Setters
void Eter::WizardDuelMode::SetWizardPlayer1(const Wizards& wizard)
{
	m_wizardPlayer1 = wizard;
}

void Eter::WizardDuelMode::SetWizardPlayer2(const Wizards& wizard)
{
	m_wizardPlayer2 = wizard;
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

	std::vector<char> Values = { '1', '1', '1', '2', '2', '2', '3', '3', '3', '4'};
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

	int mageTypePlayer1 = Random(std::make_pair(0, 3));
	int mageTypePlayer2 = Random(std::make_pair(0, 3));

	while(mageTypePlayer2 == mageTypePlayer1)
		mageTypePlayer2 = Random(std::make_pair(0, 3));

	m_wizardPlayer1.SetUserName(Player1.GetUserName());
	m_wizardPlayer2.SetUserName(Player2.GetUserName());
	m_wizardPlayer1.SetMageType(static_cast<MageType>(mageTypePlayer1));
	m_wizardPlayer2.SetMageType(static_cast<MageType>(mageTypePlayer2));

	PlayGame();
}

void Eter::WizardDuelMode::PlayGame()
{ 
	auto GameBoard = this->GetBoard();
	auto& Player1 = this->GetPlayer1Reference();
	auto& Player2 = this->GetPlayer2Reference();
	while (m_rounds <= 3) {
		m_currentPlayer == &Player1 ? m_currentPlayer = &Player2 : m_currentPlayer = &Player1;
		m_currentWizard == &m_wizardPlayer1 ? m_currentWizard = &m_wizardPlayer2 : m_currentWizard = &m_wizardPlayer1;
		GameBoard.PrintBoardForFormatedOutput(GetBluePlayerName()); // Print the board
		std::cout << m_currentPlayer->GetUserName() << ", it's your turn.\n";

		char option;
		std::cout << "                 OPTIONS:       \n";
		std::cout << "________________________________________________\n";
		std::cout << "a. Choose piece\n";
		std::cout << "b. Play illusion\n";
		std::cout << "c. Play explosion\n";
		std::cout << "d. Play wizard\n";
		std::cout << "________________________________________________\n";
		std::cout << "Choose your option: \n";
		std::cin >> option;

		switch (option) {
		case 'a': {
			GameBoard.SetTileValue(m_currentPlayer->Play(), m_currentPlayer->ChoosePiece(), m_currentPlayer->GetUserName());
			break;
		}
		case 'b': {
			if (m_currentPlayer->GetIllusionPlayed() == false)
				Illusion(*m_currentPlayer);
			else
				std::cout << "You have already played your illusion card.\n";
			break;
		}
		case 'c': {
			std::cout << "To implement";
			break;
		}
		case 'd': {
			std::cout << m_currentWizard->GetUserName() << " " << static_cast<int>(m_currentWizard->GetMageType()) << "\n";
			break;
		}
		default: {
			std::cout << "Invalid option. Please choose a valid option.\n";
			break;
		}
		}

		if (GameBoard.GetCurrentSize() == GameBoard.GetMaxSize() || CheckCompleteRowOrColumn()) {
			if (CheckWinner()) {
				++m_rounds;
				m_currentPlayer->SetGamesWon(m_currentPlayer->GetGamesWon() + 1);
				StartGame();
			}
		}
	}
}

//It does not display the illusion on this game mode (i'll check the problem tomorrow)... he never did.... :(
void Eter::WizardDuelMode::Illusion(Player& player)
{
	auto GameBoard = this->GetBoard();
	const std::pair<int, int>& Position = player.Play();
	int row = Position.first, column = Position.second;
	bool canPlace = false;

	if (row < 0 || column < 0 || row >= GameBoard.GetCurrentSize() || column >= GameBoard.GetBoard()[row].size())
	{
		canPlace = true;
	}
	else if (GameBoard.GetBoard()[row][column].has_value()) {
		canPlace = false;
	}
	else
		canPlace = true;

	if (canPlace) {
		player.SetIllusionPlayed(true);
		GameBoard.SetTileValue(Position, player.ChoosePiece(), player.GetUserName());
		row < 0 ? row = 0 : row;
		column < 0 ? column = 0 : column;
		GameBoard.GetBoardReference()[row][column] = Tile(Piece(player.GetLastPlayedPiece().GetValue(), true, player.GetUserName(), true, false));
	}
	else {
		std::cout << "You cannot place your illusion card there.\n";
	}
}

int Eter::WizardDuelMode::Random(const std::pair<int, int>& distance)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(distance.first, distance.second);
	int random_number = dis(gen);
	return random_number;
}
#pragma endregion Methods


