#include "WizardDuelMode.h"

#pragma region Constructors
Eter::WizardDuelMode::WizardDuelMode(
	const Player& player1, 
	const Player& player2, 
	Board& board, 
	const GameType& gameType, 
	Wizards& wizardPlayer1,
	Wizards& wizardPlayer2) : Game(player1, player2, board, gameType), m_wizardPlayer1(wizardPlayer1), m_wizardPlayer2(wizardPlayer2)
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
	other.SetGameType(GameType::Duel);
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
	auto GameBoard = this->GetBoardReference();
	auto& Player1 = this->GetPlayer1Reference();
	auto& Player2 = this->GetPlayer2Reference();
	
	UsernameHandling();
	InitializeWizzardDuelGame();
	SetWizzardType();

	firstMove = true;
	PlayGame();
}

void Eter::WizardDuelMode::UsernameHandling()
{
	std::string UsernamePlayer1;
	std::string UsernamePlayer2;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

void Eter::WizardDuelMode::InitializeWizzardDuelGame()
{
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

void Eter::WizardDuelMode::SetWizzardType()
{
	auto& Player1 = this->GetPlayer1Reference();
	auto& Player2 = this->GetPlayer2Reference();

	int mageTypePlayer1 = Random(std::make_pair(0, 3));
	int mageTypePlayer2 = Random(std::make_pair(0, 3));

	while (mageTypePlayer2 == mageTypePlayer1)
		mageTypePlayer2 = Random(std::make_pair(0, 3));

	/*int mageTypePlayer1 = 1;
	int mageTypePlayer2 = 2;*/

	m_wizardPlayer1.SetUserName(Player1.GetUserName());
	m_wizardPlayer2.SetUserName(Player2.GetUserName());
	m_wizardPlayer1.SetMageType(static_cast<MageType>(mageTypePlayer1));
	m_wizardPlayer2.SetMageType(static_cast<MageType>(mageTypePlayer2));
}

int Eter::WizardDuelMode::Random(const std::pair<int, int>& distance)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(distance.first, distance.second);
	int random_number = dis(gen);
	return random_number;
}

void Eter::WizardDuelMode::CreateFromJsonWizard(const nlohmann::json& gameInfo)
{
	auto& m_board = this->GetBoardReference();
	auto& m_player1 = this->GetPlayer1Reference();
	auto& m_player2 = this->GetPlayer2Reference();

	//create board
	m_board = gameInfo.at("boardInfo").get<Board>();

	//create players
	nlohmann::json playerInfo = gameInfo.at("playerInfo");
	m_player1 = playerInfo.at("player1").get<Eter::Player>();
	m_player2 = playerInfo.at("player2").get<Eter::Player>();

	//create game info
	nlohmann::json gameInfoJson = gameInfo.at("gameInfo");
	SetGameType(gameInfoJson.at("gameType").get<GameType>());
	m_rounds = gameInfoJson.at("rounds").get<size_t>();
	SetBluePlayerName(gameInfoJson.at("bluePlayerName").get<std::string>());
	m_wizardPlayer1 = gameInfoJson.at("wizardPlayer1").get<Wizards>();
	m_wizardPlayer2 = gameInfoJson.at("wizardPlayer2").get<Wizards>();

	m_wizardPlayer1.SetBoardForMage(&m_board);
	m_wizardPlayer2.SetBoardForMage(&m_board);

	if (gameInfoJson.at("currentWizard").get<Wizards>().GetUserName() == m_player1.GetUserName())
	{
		m_currentPlayer = &m_player2;
	}
	else
	{
		m_currentPlayer = &m_player1;
	}

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

void Eter::WizardDuelMode::ExportToJsonWizard()
{
	std::string filename = Eter::GenerateSaveFilename("wizard");
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
			{"currentWizard", *m_currentWizard},
			{"firstMove", firstMove},
			{"wizardPlayer1", m_wizardPlayer1},
			{"wizardPlayer2", m_wizardPlayer2}
		};
		file << j_game.dump(4);
		file.close();
		std::cout << "Game saved to " << filename << std::endl;
	}
	else {
		std::cerr << "Error opening file " << filename << std::endl;
	}
}

void Eter::WizardDuelMode::PlayGame()
{ 
	auto& GameBoard = this->GetBoardReference();
	auto& Player1 = this->GetPlayer1Reference();
	auto& Player2 = this->GetPlayer2Reference();
	while (m_rounds <= 3) {

		if(m_currentPlayer != nullptr)
			if (m_currentPlayer->GetPieces().size() == 0){
				std::cout << "The game is over!\n" << m_currentPlayer->GetUserName() << " has no more pieces!";
				m_currentPlayer == &Player1 ? m_currentPlayer = &Player2 : m_currentPlayer = &Player1;
				m_currentPlayer->SetGamesWon(m_currentPlayer->GetGamesWon() + 1);
				++m_rounds;
				StartGame();
				break;
			}

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
		std::cout << "d. Play mage\n";
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
			HandleWizzardType();
			break;
		}
		case 'e':{
			if (m_currentPlayer->GetEterCardPlayed() == false)
				PlayEterCard(*m_currentPlayer);
			else
				std::cout << "You have already played your eter card.\n";
			break;
		}
		case 's': {
			ExportToJsonWizard();
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

//It does not display the illusion on this game mode (i'll check the problem tomorrow)... he never did.... :( but i did it now 
void Eter::WizardDuelMode::Illusion(Player& player)
{
	auto& GameBoard = this->GetBoardReference();
	const std::pair<int, int>& Position = player.Play(firstMove);
	int row = Position.first, column = Position.second;
	bool canPlace = false;

	if (row < 0 || column < 0 || row >= GameBoard.GetCurrentSize()|| column >= GameBoard.GetBoardReference()[row].size())
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

//Eter card is not impacted by Mage or Elemental Powers 
void Eter::WizardDuelMode::PlayEterCard(Player& player)
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

void Eter::WizardDuelMode::HandleWizzardType()
{
	auto& GameBoard = this->GetBoardReference();
	m_currentWizard->SetBoardForMage(&GameBoard);

	std::cout << m_currentWizard->GetUserName() << "'s mage type is: " << m_currentWizard->toStringMageType(m_currentWizard->GetMageType()) << "\n";
	switch (m_currentWizard->GetMageType()) {
	case MageType::FIRE: {

		std::cout << "Choose your power: \n";
		std::cout << "1. Remove from play an opponent card that covers one of your cards.\n";
		std::cout << "2. Remove from play a row or column of 3 or more cards. The removed row or column must contain at least one of your cards. The power impacts single cards and stacks.\n";
		static std::pair<bool, bool> firePower1used = { false, false };
		static std::pair<bool, bool> firePower2used = { false, false };

		int power;
		std::cin >> power;

		const std::pair<int, int>& Position = m_currentPlayer->Play(firstMove);
		int row = Position.first, column = Position.second;
		if (power == 1) {

			if (firePower1used.first && m_currentPlayer == &this->GetPlayer1Reference()) {
				std::cout << "You have already used this power.\n";
				break;
			}
			else if (firePower1used.second && m_currentPlayer == &this->GetPlayer2Reference()) {
				std::cout << "You have already used this power.\n";
				break;
			}

			m_currentWizard->fireMasterPower(power, row, column);
			if (m_currentWizard->GetUserName() == m_wizardPlayer1.GetUserName())
				firePower1used.first = true;
			else
				firePower1used.second = true;
		}
		else if (power == 2) {

			if (firePower1used.first && m_currentPlayer == &this->GetPlayer1Reference()) {
				std::cout << "You have already used this power.\n";
				break;
			}
			else if (firePower1used.second && m_currentPlayer == &this->GetPlayer2Reference()) {
				std::cout << "You have already used this power.\n";
				break;
			}

			m_currentWizard->fireMasterPower(power, row, column);
			if (m_currentWizard->GetUserName() == m_wizardPlayer1.GetUserName())
				firePower2used.first = true;
			else
				firePower2used.second = true;
		}

		auto wizardBoard = m_currentWizard->GetBoardWizard();
		GameBoard.SetBoard(wizardBoard->GetBoard());

		break;
	}
	case MageType::EARTH: {
		std::cout << "Choose your power: \n";
		std::cout << "1. Cover an opponent card with your card of a lower value.\n";
		std::cout << "2. The chosen empty space on the playing field becomes a pit.\n";
		static std::pair<bool, bool> earthPower1used = { false, false };
		static std::pair<bool, bool> earthPower2used = { false, false };

		int power;
		std::cin >> power;

		const std::pair<int, int>& Position = m_currentPlayer->Play(firstMove);
		int row = Position.first, column = Position.second;
		if (power == 1) {

			if (earthPower1used.first && m_currentPlayer == &this->GetPlayer1Reference()) {
				std::cout << "You have already used this power.\n";
				break;
			}
			else if (earthPower1used.second && m_currentPlayer == &this->GetPlayer2Reference()) {
				std::cout << "You have already used this power.\n";
				break;
			}

			m_currentWizard->earthMasterPower(power, row, column, m_currentPlayer->GetPiecesReference());
			if (m_currentWizard->GetUserName() == m_wizardPlayer1.GetUserName())
				earthPower1used.first = true;
			else
				earthPower1used.second = true;
		}
		else if (power == 2) {

			if (earthPower2used.first && m_currentPlayer == &this->GetPlayer1Reference()) {
				std::cout << "You have already used this power.\n";
				break;
			}
			else if (earthPower2used.second && m_currentPlayer == &this->GetPlayer2Reference()) {
				std::cout << "You have already used this power.\n";
				break;
			}

			m_currentWizard->earthMasterPower(power, row, column, m_currentPlayer->GetPiecesReference());
			if (m_currentWizard->GetUserName() == m_wizardPlayer1.GetUserName())
				earthPower2used.first = true;
			else
				earthPower2used.second = true;
		}

		auto wizardBoard = m_currentWizard->GetBoardWizard();
		GameBoard.SetBoard(wizardBoard->GetBoard());

		break;
	}
	case MageType::AIR: {

		std::cout << "Choose your power: \n";
		std::cout << "1. On his turn, the player may move his card (or a stack of cards with his card on top) to a different, empty space.\n";
		std::cout << "2. Gain an extra ETER card.\n";
		static std::pair<bool, bool> airPower1used = { false, false };
		static std::pair<bool, bool> airPower2used = { false, false };

		int power;
		std::cin >> power;

		if (power == 1)
		{
			if (airPower1used.first && m_currentPlayer == &this->GetPlayer1Reference()) {
				std::cout << "You have already used this power.\n";
				break;
			}
			else if (airPower1used.second && m_currentPlayer == &this->GetPlayer2Reference()) {
				std::cout << "You have already used this power.\n";
				break;
			}
			std::cout << "Enter the positions of your own card or stack you plan to move.\n";
			const std::pair<int, int>& Position = m_currentPlayer->Play(firstMove);
			int row = Position.first, column = Position.second;
			m_currentWizard->airMasterPower(power, row, column);

			if (m_currentWizard->GetUserName() == m_wizardPlayer1.GetUserName())
				airPower1used.first = true;
			else
				airPower1used.second = true;
		}
		else if (power == 2) {
			if (airPower2used.first && m_currentPlayer == &this->GetPlayer1Reference()) {
				std::cout << "You have already used this power.\n";
				break;
			}
			else if (airPower2used.second && m_currentPlayer == &this->GetPlayer2Reference()) {
				std::cout << "You have already used this power.\n";
				break;
			}
			std::cout << "Enter the positions you want to place the Eter card on.\n";
			const std::pair<int, int>& Position = m_currentPlayer->Play(firstMove);
			int row = Position.first, column = Position.second;
			m_currentWizard->airMasterPower(power, row, column);

			if (m_currentWizard->GetUserName() == m_wizardPlayer1.GetUserName())
				airPower2used.first = true;
			else
				airPower2used.second = true;
		}

		auto wizardBoard = m_currentWizard->GetBoardWizard();
		GameBoard.SetBoard(wizardBoard->GetBoard());

		break;
	}
	case MageType::WATER: {

		std::cout << "Choose your power: \n";
		std::cout << "1. Move opponent stack or card to an empty space.\n";
		std::cout << "2. Take any row or column of 3 or more cards at the edge of the playing field and move it to a different edge.This redefines the shape of the playing field.\n";

		static std::pair<bool, bool> waterPower1used = { false, false };
		static std::pair<bool, bool> waterPower2used = { false, false };

		int power;
		std::cin >> power;

		if (power == 1)
		{
			if (waterPower1used.first && m_currentPlayer == &this->GetPlayer1Reference()) {
				std::cout << "You have already used this power.\n";
				break;
			}
			else if (waterPower1used.second && m_currentPlayer == &this->GetPlayer2Reference()) {
				std::cout << "You have already used this power.\n";
				break;
			}


			std::cout << "Enter the positions of the opponent card or stack you want to move.\n";
			const std::pair<int, int>& Position1 = m_currentPlayer->Play(firstMove);
			int srcRow = Position1.first, srcColumn = Position1.second;

			std::cout << "Enter the positions of the empty space you want the card or the stack to be moved..\n";
			const std::pair<uint8_t, uint8_t>& Position2 = m_currentPlayer->Play(firstMove);
			int destRow = Position2.first, destColumn = Position2.second;
			m_currentWizard->waterMasterPower(power, srcRow, srcColumn, destRow, destColumn);

			if (m_currentWizard->GetUserName() == m_wizardPlayer1.GetUserName())
				waterPower1used.first = true;
			else
				waterPower1used.second = true;
		}
		else if (power == 2) {

			if (waterPower2used.first && m_currentPlayer == &this->GetPlayer1Reference()) {
				std::cout << "You have already used this power.\n";
				break;
			}
			else if (waterPower2used.second && m_currentPlayer == &this->GetPlayer2Reference()) {
				std::cout << "You have already used this power.\n";
				break;
			}

			m_currentWizard->waterMasterPower(power, 0, 0, 0, 0);
			if (m_currentWizard->GetUserName() == m_wizardPlayer1.GetUserName())
				waterPower2used.first = true;
			else
				waterPower2used.second = true;
		}

		auto wizardBoard = m_currentWizard->GetBoardWizard();
		GameBoard.SetBoard(wizardBoard->GetBoard());

		break;
	}
	case MageType::UNKNOWN: {
		std::cout << "Unknown mage";
		break;
	}
	}
}

#pragma endregion Methods


