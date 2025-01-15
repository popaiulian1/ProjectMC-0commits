#include "ElementalBattleMode.h"
#include <random>


#pragma region Constructors
Eter::ElementalBattleMode::ElementalBattleMode(
	const Player& player1,
	const Player& player2,
	Board& board, 
	Elemental& m_elementPlayer1,
	Elemental& m_elementPlayer2,
	const GameType& gameType) : Game(player1, player2, board, gameType), m_elementPlayer1(m_elementPlayer1), m_elementPlayer2(m_elementPlayer2) 
{}

Eter::ElementalBattleMode::ElementalBattleMode(ElementalBattleMode && other) noexcept
{
	SetPlayer1(other.GetPlayer1());
	SetPlayer2(other.GetPlayer2());
	SetBoard(other.GetBoard());
	SetGameType(other.GetGameType());
	m_elementPlayer1 = std::move(other.m_elementPlayer1);
	m_elementPlayer2 = std::move(other.m_elementPlayer2);

	other.SetPlayer1(Player());
	other.SetPlayer2(Player());
	other.SetBoard(Board());
	other.SetGameType(GameType::Practice);
	other.m_elementPlayer1 = Elemental();
	other.m_elementPlayer2 = Elemental();
}

Eter::ElementalBattleMode::ElementalBattleMode(const ElementalBattleMode& other)
{
	SetPlayer1(other.GetPlayer1());
	SetPlayer2(other.GetPlayer2());
	SetBoard(other.GetBoard());
	SetGameType(other.GetGameType());
	m_elementPlayer1 = other.m_elementPlayer1;
	m_elementPlayer2 = other.m_elementPlayer2;
}

Eter::ElementalBattleMode& Eter::ElementalBattleMode::operator=(const ElementalBattleMode& other)
{
	if (this != &other)
	{
		SetPlayer1(other.GetPlayer1());
		SetPlayer2(other.GetPlayer2());
		SetBoard(other.GetBoard());
		SetGameType(other.GetGameType());
		m_elementPlayer1 = other.m_elementPlayer1;
		m_elementPlayer2 = other.m_elementPlayer2;
	}
	return *this;
}
#pragma endregion Constructors

#pragma region Getters
Eter::Elemental Eter::ElementalBattleMode::GetElementPlayer1() const
{
	return m_elementPlayer1;
}

Eter::Elemental Eter::ElementalBattleMode::GetElementPlayer2() const
{
	return m_elementPlayer2;
}
#pragma endregion Getters

#pragma region Setters
void Eter::ElementalBattleMode::SetElementPlayer1(const Elemental& element)
{
	m_elementPlayer1 = element;
}

void Eter::ElementalBattleMode::SetElementPlayer2(const Elemental& element)
{
	m_elementPlayer2 = element;
}
#pragma endregion Setters


#pragma region Methodes

void Eter::ElementalBattleMode::StartGame()
{
	std::cout << "This is Elemental Battle Mode" << std::endl;
	std::cout << "_____________________________\n";

	if (GetGameType() != Eter::GameType::Duel)
		SetGameType(Eter::GameType::Duel);

	SetBoard(Board(Eter::GameType::Duel));
	auto GameBoard = this->GetBoardReference();
	auto& Player1 = this->GetPlayer1Reference();
	auto& Player2 = this->GetPlayer2Reference();

	UsernameHandling();
	InitializeElementalBattleGame();
	SetElementalType();

	std::cout << "The Elemental Card of " << Player1.GetUserName() << " is: " << m_elementPlayer1.toSringElementalCardName(m_elementPlayer1.GetNameCard()) << std::endl;
	std::cout << "The Elemental Card of " << Player2.GetUserName() << " is: " << m_elementPlayer2.toSringElementalCardName(m_elementPlayer2.GetNameCard()) << std::endl;
}

void Eter::ElementalBattleMode::UsernameHandling()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::string UsernamePlayer1;
	std::string UsernamePlayer2;
	auto& Player1 = this->GetPlayer1Reference();
	auto& Player2 = this->GetPlayer2Reference();
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
}

void Eter::ElementalBattleMode::InitializeElementalBattleGame(){
	auto& Player1 = this->GetPlayer1Reference();
	auto& Player2 = this->GetPlayer2Reference();
	std::vector<char> Values = { '1', '1', '1', '2', '2', '2', '3', '3', '3', '4' };
	std::vector<Eter::Piece> CardsPractice;

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
}

void Eter::ElementalBattleMode::SetElementalType()
{
	auto& Player1 = this->GetPlayer1Reference();
	auto& Player2 = this->GetPlayer2Reference();

	int ElementalCardName1 = Random(std::make_pair(0, 23));
	int ElementalCardName2 = Random(std::make_pair(0, 23));

	while(ElementalCardName2 == ElementalCardName1)
		ElementalCardName2 = Random(std::make_pair(0, 23));

	m_elementPlayer1.SetUsername(Player1.GetUserName());
	m_elementPlayer2.SetUsername(Player2.GetUserName());
	m_elementPlayer1.SetNameCard(static_cast<ElementalCardName>(ElementalCardName1));
	m_elementPlayer2.SetNameCard(static_cast<ElementalCardName>(ElementalCardName2));
	
}

int Eter::ElementalBattleMode::Random(const std::pair<int, int>& distance) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(distance.first, distance.second);
	int random_number = dis(gen);
	return random_number;
}


#pragma endregion Methodes

