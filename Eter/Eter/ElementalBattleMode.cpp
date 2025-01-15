#include "ElementalBattleMode.h"
#include <random>


#pragma region Constructors
Eter::ElementalBattleMode::ElementalBattleMode(
	const Player& player1,
	const Player& player2,
	Board& board, 
	Elemental& m_elementCrad1,
	Elemental& m_elementCard2,
	const GameType& gameType) : Game(player1, player2, board, gameType), m_elementCard1(m_elementCrad1), m_elementCard2(m_elementCard2)
{}

Eter::ElementalBattleMode::ElementalBattleMode(ElementalBattleMode && other) noexcept
{
	SetPlayer1(other.GetPlayer1());
	SetPlayer2(other.GetPlayer2());
	SetBoard(other.GetBoard());
	SetGameType(other.GetGameType());
	m_elementCard1 = std::move(other.m_elementCard1);
	m_elementCard2 = std::move(other.m_elementCard2);

	other.SetPlayer1(Player());
	other.SetPlayer2(Player());
	other.SetBoard(Board());
	other.SetGameType(GameType::Practice);
	other.m_elementCard1 = Elemental();
	other.m_elementCard2 = Elemental();
}

Eter::ElementalBattleMode::ElementalBattleMode(const ElementalBattleMode& other)
{
	SetPlayer1(other.GetPlayer1());
	SetPlayer2(other.GetPlayer2());
	SetBoard(other.GetBoard());
	SetGameType(other.GetGameType());
	m_elementCard1 = other.m_elementCard1;
	m_elementCard2 = other.m_elementCard2;
}

Eter::ElementalBattleMode& Eter::ElementalBattleMode::operator=(const ElementalBattleMode& other)
{
	if (this != &other)
	{
		SetPlayer1(other.GetPlayer1());
		SetPlayer2(other.GetPlayer2());
		SetBoard(other.GetBoard());
		SetGameType(other.GetGameType());
		m_elementCard1 = other.m_elementCard1;
		m_elementCard2 = other.m_elementCard2;
	}
	return *this;
}
#pragma endregion Constructors

#pragma region Getters
Eter::Elemental Eter::ElementalBattleMode::GetElementPlayer1() const
{
	return m_elementCard1;
}

Eter::Elemental Eter::ElementalBattleMode::GetElementPlayer2() const
{
	return m_elementCard2;
}
#pragma endregion Getters

#pragma region Setters
void Eter::ElementalBattleMode::SetElementCard1(const Elemental& element)
{
	m_elementCard1 = element;
}

void Eter::ElementalBattleMode::SetElementCard2(const Elemental& element)
{
	m_elementCard2 = element;
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

	PlayGame();
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

	m_elementCard1.SetNameCard(static_cast<ElementalCardName>(ElementalCardName1));
	m_elementCard2.SetNameCard(static_cast<ElementalCardName>(ElementalCardName2));
}

int Eter::ElementalBattleMode::Random(const std::pair<int, int>& distance) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(distance.first, distance.second);
	int random_number = dis(gen);
	return random_number;
}

void Eter::ElementalBattleMode::PlayGame(){
	auto& GameBoard = this->GetBoardReference();
	auto& Player1 = this->GetPlayer1Reference();
	auto& Player2 = this->GetPlayer2Reference();
	while (m_rounds <= 3) {
		m_currentPlayer == &Player1 ? m_currentPlayer = &Player2 : m_currentPlayer = &Player1;
		GameBoard.PrintBoardForFormatedOutput(GetBluePlayerName()); // Print the board
		std::cout << m_currentPlayer->GetUserName() << ", it's your turn.\n";

		char option;
		std::cout << "                 OPTIONS:       \n";
		std::cout << "________________________________________________\n";
		std::cout << "a. Choose piece\n";
		std::cout << "b. Play illusion\n";
		std::cout << "c. Play explosion\n";
		std::cout << "d. Play mage\n";
		std::cout << "e. Play eter card\n";
		std::cout << "________________________________________________\n";
		std::cout << "Choose your option: \n";
		std::cin >> option;

		switch (option) {
		case 'a': {
			try {
				GameBoard.SetTileValue(m_currentPlayer->Play(firstMove), m_currentPlayer->ChoosePiece(), m_currentPlayer->GetUserName());
			}
			catch (const std::invalid_argument& e) {
				size_t deckSize = m_currentPlayer->GetPiecesReference().size();
				m_currentPlayer->GetPiecesReference().resize(deckSize + 1);
				m_currentPlayer->GetPiecesReference()[deckSize].SetValue(m_currentPlayer->GetLastPlayedPiece().GetValue());
			}
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
			HandleElementalType();
			break;
		}
		case 'e': {
			if (m_currentPlayer->GetEterCardPlayed() == false)
				PlayEterCard(*m_currentPlayer);
			else
				std::cout << "You have already played your eter card.\n";

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

void Eter::ElementalBattleMode::Illusion(Player& player)
{
	auto& GameBoard = this->GetBoardReference();
	const std::pair<int, int>& Position = player.Play(firstMove);
	int row = Position.first, column = Position.second;
	bool canPlace = false;

	if (row < 0 || column < 0 || row >= GameBoard.GetCurrentSize() || column >= GameBoard.GetBoardReference()[row].size())
	{
		canPlace = true;
	}
	else if (GameBoard.GetBoardReference()[row][column].has_value()) {
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

void Eter::ElementalBattleMode::PlayEterCard(Player& player)
{
	auto& pieces = player.GetPiecesReference();
	auto& GameBoard = this->GetBoardReference();
	const std::pair<int, int>& Position = player.Play(firstMove);
	int row = Position.first, column = Position.second;
	bool canPlace = false;

	if (row < 0 || column < 0 || row >= GameBoard.GetCurrentSize() || column >= GameBoard.GetBoardReference()[row].size())
	{
		canPlace = true;
	}
	else if (GameBoard.GetBoardReference()[row][column].has_value()) {
		canPlace = false;
	}
	else
		canPlace = true;

	if (canPlace) {
		player.SetEterCardPlayed(true);
		GameBoard.SetTileValue(Position, pieces[0].GetValue(), player.GetUserName());
		pieces.erase(pieces.begin());
		row < 0 ? row = 0 : row;
		column < 0 ? column = 0 : column;
		GameBoard.GetBoardReference()[row][column] = Tile(Piece('1', true, player.GetUserName(), false, true));
		GameBoard.GetBoardReference()[row][column].value().GetTopValueRef().SetEterCard(true);
	}
	else
		std::cout << "You cannot place your eter card there.\n";
}

void Eter::ElementalBattleMode::HandleElementalType(){

	static bool element1used = false;
	static bool element2used = false;

	if (element1used && element2used)
	{
		std::cout << "Both elements have been played.\n";
		return;
	}

	auto& GameBoard = this->GetBoardReference();
	m_elementCard1.SetBoardForElemental(GameBoard);
	m_elementCard2.SetBoardForElemental(GameBoard);
	
	std::cout << "What element would you like to use?\n";
	std::cout << "1." << m_elementCard1.toSringElementalCardName(m_elementCard1.GetNameCard()) << std::endl;
	std::cout << "2." << m_elementCard2.toSringElementalCardName(m_elementCard2.GetNameCard()) << std::endl;

	int choice;
	std::cin >> choice;

	if ((choice == 1 && element1used) || (choice == 2 && element2used)) {
		std::cout << "This element was played.\n";
		return;
	}

	if (choice == 1)
	{
		ElementalSelection(m_elementCard1);
		element1used = true;
	}
	else if (choice == 2)
	{
		ElementalSelection(m_elementCard2);
		element2used = true;
	}
	
}

void Eter::ElementalBattleMode::ElementalSelection(Elemental elemental)
{
	switch (elemental.GetNameCard())
	{
	case Eter::ElementalCardName::CONTROLLED_EXPLOSION:
		std::cout << "CONTROLLED_EXPLOSION";
		break;
	case Eter::ElementalCardName::DESTRUCTION:
		std::cout << "DESTRUCTION";
		break;
	case Eter::ElementalCardName::FLAME:
		std::cout << "FLAME";
		break;
	case Eter::ElementalCardName::FIRE:
		std::cout << "FIRE";
		break;
	case Eter::ElementalCardName::ASH:
		std::cout << "ASH";
		break;
	case Eter::ElementalCardName::SPARK:
		std::cout << "SPARK";
		break;
	case Eter::ElementalCardName::SQUALL:
		std::cout << "SQUALL";
		break;
	case Eter::ElementalCardName::GALE:
		std::cout << "GALE";
		break;
	case Eter::ElementalCardName::HURRICANE:
		std::cout << "HURRICANE";
		break;
	case Eter::ElementalCardName::GUST:
		std::cout << "GUST";
		break;
	case Eter::ElementalCardName::MIRAGE:
		std::cout << "MIRAGE";
		break;
	case Eter::ElementalCardName::STORM:
		std::cout << "STORM";
		break;
	case Eter::ElementalCardName::TIDE:
		std::cout << "TIDE";
		break;
	case Eter::ElementalCardName::MIST:
		std::cout << "MIST";
		break;
	case Eter::ElementalCardName::WAVE:
		std::cout << "WAVE";
		break;
	case Eter::ElementalCardName::WHIRLPOOL:
		std::cout << "WHIRLPOOL";
		break;
	case Eter::ElementalCardName::BLIZZARD:
		std::cout << "BLIZZARD";
		break;
	case Eter::ElementalCardName::WATERFALL:
		std::cout << "WATERFALL";
		break;
	case Eter::ElementalCardName::SUPPORT:
		std::cout << "SUPPORT";
		break;
	case Eter::ElementalCardName::EARTHQUAKE:
		std::cout << "EARTHQUAKE";
		break;
	case Eter::ElementalCardName::CRUMBLE:
		std::cout << "CRUMBLE";
		break;
	case Eter::ElementalCardName::BORDER:
		std::cout << "BORDER";
		break;
	case Eter::ElementalCardName::AVALANCHE:
		std::cout << "AVALANCHE";
		break;
	case Eter::ElementalCardName::ROCK:
		std::cout << "ROCK";
		break;
	default:
		std::cout << "Invalid option. Please choose a valid option.\n";
		break;
	}
}

#pragma endregion Methodes

