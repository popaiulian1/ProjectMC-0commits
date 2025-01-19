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
	other.SetGameType(GameType::Elemental);
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

	if (GetGameType() != Eter::GameType::Elemental)
		SetGameType(Eter::GameType::Elemental);

	SetBoard(Board(Eter::GameType::Elemental));
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

		if (m_currentPlayer != nullptr)
			if (m_currentPlayer->GetPieces().size() == 0) {
				std::cout << "The game is over!\n" << m_currentPlayer->GetUserName() << " has no more pieces!";
				m_currentPlayer == &Player1 ? m_currentPlayer = &Player2 : m_currentPlayer = &Player1;
				m_currentPlayer->SetGamesWon(m_currentPlayer->GetGamesWon() + 1);
				++m_rounds;
				StartGame();
				break;
			}

		m_currentPlayer == &Player1 ? m_currentPlayer = &Player2 : m_currentPlayer = &Player1;
		GameBoard.PrintBoardForFormatedOutput(GetBluePlayerName()); // Print the board
		std::cout << m_currentPlayer->GetUserName() << ", it's your turn.\n";

		char option;
		std::cout << "                 OPTIONS:       \n";
		std::cout << "________________________________________________\n";
		std::cout << "a. Choose piece\n";
		std::cout << "b. Play illusion\n";
		std::cout << "c. Play explosion\n";
		std::cout << "d. Play elemental\n";
		std::cout << "e. Play eter card\n";
		std::cout << "s. Save Game\n";
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
		case 's': {
			ExportToJsonElemental();
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

	auto& GameBoard = this->GetBoardReference();
	auto& Player1 = this->GetPlayer1Reference();
	auto& Player2 = this->GetPlayer2Reference();
	elemental.SetBoardForElemental(GameBoard);

	switch (elemental.GetNameCard())
	{
	case Eter::ElementalCardName::CONTROLLED_EXPLOSION:
		std::cout << "CONTROLLED_EXPLOSION";
		break;

	case Eter::ElementalCardName::DESTRUCTION:
		std::cout << "DESTRUCTION: Remove from play the last card played by the opponent.\n";
		if(m_currentPlayer->GetUserName() == Player1.GetUserName())
			elemental.Destruction(Player2, GameBoard);
		else
			elemental.Destruction(Player1, GameBoard);
		break;

	case Eter::ElementalCardName::FLAME:
		std::cout << "FLAME: Reveal an opponent’s Illusion and next place your card on any space on the playing field.\n";
		if (m_currentPlayer->GetUserName() == Player1.GetUserName()) {
			elemental.Flame(Player2, GameBoard);
			GameBoard.PrintBoardForFormatedOutput(GetBluePlayerName());
			GameBoard.SetTileValue(m_currentPlayer->Play(firstMove), m_currentPlayer->ChoosePiece(), m_currentPlayer->GetUserName());
		}
		else
		{
			elemental.Flame(Player1, GameBoard);
			GameBoard.PrintBoardForFormatedOutput(GetBluePlayerName());
			GameBoard.SetTileValue(m_currentPlayer->Play(firstMove), m_currentPlayer->ChoosePiece(), m_currentPlayer->GetUserName());
		}
		break;

	case Eter::ElementalCardName::FIRE:
		std::cout << "FIRE: Return to their owners' hands all visible cards of the same value(at least 2 of them) chosen by you - also yours!In case of stacks remove only the top card.\n";
		elemental.Fire(GameBoard, Player1, Player2);
		break;

	case Eter::ElementalCardName::ASH:
		std::cout << "ASH: Rise like a Phoenix! If one of your cards was removed from play, you can immediately play it again.\n";
		if (m_currentPlayer->GetUserName() == Player1.GetUserName()) 
			elemental.Ash(GameBoard, Player1);
		else
			elemental.Ash(GameBoard, Player2);
		break;

	case Eter::ElementalCardName::SPARK:
		std::cout << "SPARK: Take any of your cards that is covered by an opponent's cards and play it onto a different space. In case of stacks, you can choose any of your covered cards.\n";
		if (m_currentPlayer->GetUserName() == Player1.GetUserName())
			elemental.Spark(GameBoard, Player1);
		else
			elemental.Spark(GameBoard, Player2);
		break;

	case Eter::ElementalCardName::SQUALL:
		std::cout << "SQUALL: Return to the opponent's hand any one of his visible cards on the playing field.\n";
		if (m_currentPlayer->GetUserName() == Player1.GetUserName())
			elemental.Squall(Player2,GameBoard);
		else
			elemental.Squall(Player1, GameBoard);
		break;

	case Eter::ElementalCardName::GALE:
		std::cout << "GALE: Remove any cards that are covered by others (yours as well) - they are returned to their owners' hands.\n";
		elemental.Gale(GameBoard, Player1, Player2);
		break;

	case Eter::ElementalCardName::HURRICANE:
		std::cout << "HURRICANE: Move any one full row / column by one card so that the first card / stack is moved off the playing field. Cards moved outside the playing field return to their owners' hands.\n";
		elemental.Hurricane(GameBoard, Player1, Player2);
		break;

	case Eter::ElementalCardName::GUST:
		std::cout << "GUST: Move any card on the playing field horizontally or vertically onto a neighboring card of a lower value. Affects individual cards not stacks.\n";
		elemental.Gust(GameBoard);
		break;

	case Eter::ElementalCardName::MIRAGE:
		std::cout << "MIRAGE: Exchange your Illusion (face-down card) with a different card from your hand (face - down).\n";
		if (m_currentPlayer->GetUserName() == Player1.GetUserName())
			elemental.Mirage(GameBoard, Player1);
		else
			elemental.Mirage(GameBoard,Player2);
		break; 

	case Eter::ElementalCardName::STORM:
		std::cout << "STORM: Remove from play any stack of minimum 2 cards.\n";
		elemental.Storm(GameBoard);
		break;

	case Eter::ElementalCardName::TIDE: {
		std::cout << "TIDE: Change positions of 2 different cards or stacks of cards. \n";
		std::cout << "Choose position for the first tile:\n";
		const std::pair<int, int>& PositionforTile1 = m_currentPlayer->Play(firstMove);

		std::cout << "Choose position for the second tile:\n";
		const std::pair<int, int>& PositionforTile2 = m_currentPlayer->Play(firstMove);
		elemental.Tide(PositionforTile1.first, PositionforTile1.second, PositionforTile2.first, PositionforTile2.second);

		auto elementBoard = elemental.GetBoardForElemental();
		GameBoard.SetBoard(elementBoard.GetBoard());
		break;
	}
	case Eter::ElementalCardName::MIST: {
		std::cout << "MIST: Play an Illusion again. You cannot have 2 Illusions at the same time.\n";
		elemental.Mist(*m_currentPlayer);
		if(!m_currentPlayer->GetIllusionPlayed())
			Illusion(*m_currentPlayer);
		break;
	}
	case Eter::ElementalCardName::WAVE:
		std::cout << "WAVE: Move any card/stack to the adjacent empty space, then play a card from your hand to this now empty space.\n";
		elemental.Wave(GameBoard, *m_currentPlayer);
		break;

	case Eter::ElementalCardName::WHIRLPOOL:
		std::cout << "WHIRLPOOL: Move onto empty space two cards from different adjacent spaces in a straight line.The card of lower value goes to the bottom of the stack.\n";
		elemental.Whirlpool(GameBoard);
		break;

	case Eter::ElementalCardName::BLIZZARD: 
		std::cout << "BLIZZARD: Place this card onto any space and choose a row or column that it will impact.The opponent cannot play any cards onto the chosen row / column during his next turn.Condition - your opponent must have a free space to play a card.Remove this card from play after the next opponent turn. \n";
		//elemental.Blizzard(GameBoard);
		break;

	case Eter::ElementalCardName::SUPPORT:
		std::cout << "SUPPORT: Value of a chosen card on the board is increased by +1 (cannot be used on a '4' card).\n";
		elemental.Support(GameBoard);
		break;

	case Eter::ElementalCardName::EARTHQUAKE:
		std::cout << "EARTHQUAKE: Remove from play all visible ‘1’ cards.\n";
		elemental.Earthquake(GameBoard);
		break;

	case Eter::ElementalCardName::CRUMBLE:
		std::cout << "CRUMBLE: Value of a card on the board is decreased by 1 (cannot be used on a ‘1’ card).\n";
		elemental.Crumble(GameBoard);
		break;

	case Eter::ElementalCardName::BORDER:
		std::cout << "BORDER: Place this card in any empty space on the playing field to establish the border of the play area.Next, play your normal card.Any player may replace the Border card with any of their cards(it does not block the space).Condition - when played, this card must define one of the borders of the playing area.\n";
		break;

	case Eter::ElementalCardName::WATERFALL:
		std::cout << "WATERFALL Move all cards in a chosen column into one stack at the bottom of that column, placing them on top of each other, regardless of their values.The card that was visible on the top of the chosen column stays at the top of the new stack.Condition - the chosen column must contain of minimum 3 cards.\n";
		break;

	case Eter::ElementalCardName::AVALANCHE:
		std::cout << "AVALANCHE: Move two neighboring cards / stacs by one space horizontally or vertically.The space that the first card moves onto must be empty.\n";
		break;

	case Eter::ElementalCardName::ROCK:
		std::cout << "Cover any Illusion card with your card, without revealing the value of the Illusion.\n";
		if (m_currentPlayer->GetUserName() == Player1.GetUserName())
			elemental.Rock(GameBoard, Player1, Player2);
		else
			elemental.Rock(GameBoard, Player2, Player1);
		break;
	default:
		std::cout << "Invalid option. Please choose a valid option.\n";
		break;
	}
}

void Eter::ElementalBattleMode::CreateFromJsonElemental(const nlohmann::json& gameInfo)
{
	auto& m_board = this->GetBoardReference();
	auto& m_player1 = this->GetPlayer1Reference();
	auto& m_player2 = this->GetPlayer2Reference();

	//create board
	m_board = gameInfo.at("boardInfo").get<Board>();

	//create players
	nlohmann::json playerInfo = gameInfo.at("playerInfo");
	m_player1 = playerInfo.at("player1").get<Player>();
	m_player2 = playerInfo.at("player2").get<Player>();

	//create game info
	nlohmann::json gameInfoJson = gameInfo.at("gameInfo");
	SetGameType(gameInfoJson.at("gameType").get<GameType>());
	m_rounds = gameInfoJson.at("rounds").get<size_t>();
	SetBluePlayerName(gameInfoJson.at("bluePlayerName").get<std::string>());
	m_elementCard1 = gameInfoJson.at("elementCard1").get<Elemental>();
	m_elementCard2 = gameInfoJson.at("elementCard2").get<Elemental>();

	m_elementCard1.SetBoardForElemental(m_board);
	m_elementCard2.SetBoardForElemental(m_board);

	if (gameInfoJson.at("currentPlayer").get<Player>().GetUserName() == m_player1.GetUserName())
	{
		m_currentPlayer = &m_player2;
	}
	else
	{
		m_currentPlayer = &m_player1;
	}
	firstMove = gameInfoJson.at("firstMove").get<bool>();
	PlayGame();
}

void Eter::ElementalBattleMode::ExportToJsonElemental()
{
	std::string filename = Eter::GenerateSaveFilename("elemental");
	std::ofstream file("./SaveGames/" + filename);

	if (file.is_open()) {
		nlohmann::json j_game;
		j_game["boardInfo"] = this->GetBoardReference();
		j_game["playerInfo"] = { {"player1", this->GetPlayer1()}, {"player2", this->GetPlayer2()} };
		j_game["gameInfo"] = {
			{"gameType", GetGameType()},
			{"rounds", m_rounds},
			{"bluePlayerName", GetBluePlayerName()},
			{"currentPlayer", *m_currentPlayer},
			{"firstMove", firstMove},
			{"elementCard1", m_elementCard1},
			{"elementCard2", m_elementCard2}
		};
		file << j_game.dump(4);
		file.close();
		std::cout << "Game saved to " << filename << std::endl;
	}
	else {
		std::cerr << "Error opening file " << filename << std::endl;
	}
}

#pragma endregion Methodes

