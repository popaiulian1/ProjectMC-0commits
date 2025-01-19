#include "WizzardAndElementalMode.h"

Eter::WizzardAndElementalMode::WizzardAndElementalMode(const Player& player1, const Player& player2, Board& board, const GameType& gameType, Wizards& wizardPlayer1, Wizards& wizardPlayer2, Elemental& m_elementCard1, Elemental& m_elementCard2) : 
	Game(player1, player2, board, gameType),
	WizardDuelMode(player1, player2, board, gameType, wizardPlayer1, wizardPlayer2), 
	ElementalBattleMode(player1, player2, board, m_elementCard1, m_elementCard2, gameType)
{
}

Eter::WizzardAndElementalMode::WizzardAndElementalMode(WizzardAndElementalMode&& other) noexcept
{
	SetPlayer1(other.GetPlayer1());
	SetPlayer2(other.GetPlayer2());
	SetBoard(other.GetBoard());
	SetGameType(other.GetGameType());
	m_wizardPlayer1 = std::move(other.m_wizardPlayer1);
	m_wizardPlayer2 = std::move(other.m_wizardPlayer2);
	m_elementCard1 = std::move(other.m_elementCard1);
	m_elementCard2 = std::move(other.m_elementCard2);

	other.SetPlayer1(Player());
	other.SetPlayer2(Player());
	other.SetBoard(Board());
	other.SetGameType(GameType::Duel);
	other.m_wizardPlayer1 = Wizards();
	other.m_wizardPlayer2 = Wizards();
	other.m_elementCard1 = Elemental();
	other.m_elementCard2 = Elemental();
}

Eter::WizzardAndElementalMode::WizzardAndElementalMode(const WizzardAndElementalMode& other)
{
	SetPlayer1(other.GetPlayer1());
	SetPlayer2(other.GetPlayer2());
	SetBoard(other.GetBoard());
	SetGameType(other.GetGameType());
	m_wizardPlayer1 = other.m_wizardPlayer1;
	m_wizardPlayer2 = other.m_wizardPlayer2;
	m_elementCard1 = other.m_elementCard1;
	m_elementCard2 = other.m_elementCard2;
}

Eter::WizzardAndElementalMode& Eter::WizzardAndElementalMode::operator=(const WizzardAndElementalMode& other)
{
	if (this != &other)
	{
		SetPlayer1(other.GetPlayer1());
		SetPlayer2(other.GetPlayer2());
		SetBoard(other.GetBoard());
		SetGameType(other.GetGameType());
		m_wizardPlayer1 = other.m_wizardPlayer1;
		m_wizardPlayer2 = other.m_wizardPlayer2;
		m_elementCard1 = other.m_elementCard1;
		m_elementCard2 = other.m_elementCard2;
	}
	return *this;
}


void Eter::WizzardAndElementalMode::StartGame()
{
	std::cout << "This is the Mage and Elemental Duel Mode\n";
	std::cout << "_____________________________\n";

	if (GetGameType() != Eter::GameType::Duel)
		SetGameType(Eter::GameType::Duel);

	SetBoard(Board(Eter::GameType::Duel));

	auto GameBoard = this->GetBoardReference();
	auto& Player1 = this->GetPlayer1Reference();
	auto& Player2 = this->GetPlayer2Reference();

	WizardDuelMode::UsernameHandling();
	ElementalBattleMode::InitializeElementalBattleGame();
	SetElementalType();
	SetWizzardType();

	firstMove = true;
	PlayGame();
}

void Eter::WizzardAndElementalMode::PlayGame()
{
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
		std::cout << "f. Play Elemental\n";
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
		case 'f': {
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
			ExportToJsonWizardElemental();
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

void Eter::WizzardAndElementalMode::Illusion(Player& player)
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

void Eter::WizzardAndElementalMode::PlayEterCard(Player& player)
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

void Eter::WizzardAndElementalMode::HandleWizzardType()
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

void Eter::WizzardAndElementalMode::SetWizzardType()
{
	auto& Player1 = this->GetPlayer1Reference();
	auto& Player2 = this->GetPlayer2Reference();

	int mageTypePlayer1 = WizardDuelMode::Random(std::make_pair(0, 3));
	int mageTypePlayer2 = WizardDuelMode::Random(std::make_pair(0, 3));

	while (mageTypePlayer2 == mageTypePlayer1)
		mageTypePlayer2 = WizardDuelMode::Random(std::make_pair(0, 3));

	/*int mageTypePlayer1 = 1;
	int mageTypePlayer2 = 2;*/

	m_wizardPlayer1.SetUserName(Player1.GetUserName());
	m_wizardPlayer2.SetUserName(Player2.GetUserName());
	m_wizardPlayer1.SetMageType(static_cast<MageType>(mageTypePlayer1));
	m_wizardPlayer2.SetMageType(static_cast<MageType>(mageTypePlayer2));
}

void Eter::WizzardAndElementalMode::HandleElementalType()
{
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

void Eter::WizzardAndElementalMode::SetElementalType()
{
	auto& Player1 = this->GetPlayer1Reference();
	auto& Player2 = this->GetPlayer2Reference();

	int ElementalCardName1 = Eter::WizardDuelMode::Random(std::make_pair(0, 23));
	int ElementalCardName2 = Eter::WizardDuelMode::Random(std::make_pair(0, 23));

	while(ElementalCardName2 == ElementalCardName1)
		ElementalCardName2 = Eter::WizardDuelMode::Random(std::make_pair(0, 23));

	/*int ElementalCardName1 = 4;
	int ElementalCardName2 = 6;*/

	m_elementCard1.SetNameCard(static_cast<ElementalCardName>(ElementalCardName1));
	m_elementCard2.SetNameCard(static_cast<ElementalCardName>(ElementalCardName2));
}

void Eter::WizzardAndElementalMode::ElementalSelection(Elemental element)
{
	auto& GameBoard = this->GetBoardReference();
	auto& Player1 = this->GetPlayer1Reference();
	auto& Player2 = this->GetPlayer2Reference();
	element.SetBoardForElemental(GameBoard);

	switch (element.GetNameCard())
	{
	case Eter::ElementalCardName::CONTROLLED_EXPLOSION:
		std::cout << "CONTROLLED_EXPLOSION";
		break;

	case Eter::ElementalCardName::DESTRUCTION:
		std::cout << "DESTRUCTION: Remove from play the last card played by the opponent.\n";
		if (m_currentPlayer->GetUserName() == Player1.GetUserName())
			element.Destruction(Player2, GameBoard);
		else
			element.Destruction(Player1, GameBoard);
		break;

	case Eter::ElementalCardName::FLAME:
		std::cout << "FLAME: Reveal an opponent’s Illusion and next place your card on any space on the playing field.\n";
		if (m_currentPlayer->GetUserName() == Player1.GetUserName()) {
			element.Flame(Player2, GameBoard);
			GameBoard.PrintBoardForFormatedOutput(GetBluePlayerName());
			GameBoard.SetTileValue(m_currentPlayer->Play(firstMove), m_currentPlayer->ChoosePiece(), m_currentPlayer->GetUserName());
		}
		else
		{
			element.Flame(Player1, GameBoard);
			GameBoard.PrintBoardForFormatedOutput(GetBluePlayerName());
			GameBoard.SetTileValue(m_currentPlayer->Play(firstMove), m_currentPlayer->ChoosePiece(), m_currentPlayer->GetUserName());
		}
		break;

	case Eter::ElementalCardName::FIRE:
		std::cout << "FIRE: Return to their owners' hands all visible cards of the same value(at least 2 of them) chosen by you - also yours!In case of stacks remove only the top card.\n";
		element.Fire(GameBoard, Player1, Player2);
		break;

	case Eter::ElementalCardName::ASH:
		std::cout << "ASH: Rise like a Phoenix! If one of your cards was removed from play, you can immediately play it again.\n";
		if (m_currentPlayer->GetUserName() == Player1.GetUserName())
			element.Ash(GameBoard, Player1);
		else
			element.Ash(GameBoard, Player2);
		break;

	case Eter::ElementalCardName::SPARK:
		std::cout << "SPARK: Take any of your cards that is covered by an opponent's cards and play it onto a different space. In case of stacks, you can choose any of your covered cards.\n";
		if (m_currentPlayer->GetUserName() == Player1.GetUserName())
			element.Spark(GameBoard, Player1);
		else
			element.Spark(GameBoard, Player2);
		break;

	case Eter::ElementalCardName::SQUALL:
		std::cout << "SQUALL: Return to the opponent's hand any one of his visible cards on the playing field.\n";
		if (m_currentPlayer->GetUserName() == Player1.GetUserName())
			element.Squall(Player2, GameBoard);
		else
			element.Squall(Player1, GameBoard);
		break;

	case Eter::ElementalCardName::GALE:
		std::cout << "GALE: Remove any cards that are covered by others (yours as well) - they are returned to their owners' hands.\n";
		element.Gale(GameBoard, Player1, Player2);
		break;

	case Eter::ElementalCardName::HURRICANE:
		std::cout << "HURRICANE: Move any one full row / column by one card so that the first card / stack is moved off the playing field. Cards moved outside the playing field return to their owners' hands.\n";
		element.Hurricane(GameBoard, Player1, Player2);
		break;

	case Eter::ElementalCardName::GUST:
		std::cout << "GUST: Move any card on the playing field horizontally or vertically onto a neighboring card of a lower value. Affects individual cards not stacks.\n";
		element.Gust(GameBoard);
		break;

	case Eter::ElementalCardName::MIRAGE:
		std::cout << "MIRAGE: Exchange your Illusion (face-down card) with a different card from your hand (face - down).\n";
		if (m_currentPlayer->GetUserName() == Player1.GetUserName())
			element.Mirage(GameBoard, Player1);
		else
			element.Mirage(GameBoard, Player2);
		break;

	case Eter::ElementalCardName::STORM:
		std::cout << "STORM: Remove from play any stack of minimum 2 cards.\n";
		element.Storm(GameBoard);
		break;

	case Eter::ElementalCardName::TIDE: {
		std::cout << "TIDE: Change positions of 2 different cards or stacks of cards. \n";
		std::cout << "Choose position for the first tile:\n";
		const std::pair<int, int>& PositionforTile1 = m_currentPlayer->Play(firstMove);

		std::cout << "Choose position for the second tile:\n";
		const std::pair<int, int>& PositionforTile2 = m_currentPlayer->Play(firstMove);
		element.Tide(PositionforTile1.first, PositionforTile1.second, PositionforTile2.first, PositionforTile2.second);

		auto elementBoard = element.GetBoardForElemental();
		GameBoard.SetBoard(elementBoard.GetBoard());
		break;
	}
	case Eter::ElementalCardName::MIST: {
		std::cout << "MIST: Play an Illusion again. You cannot have 2 Illusions at the same time.\n";
		element.Mist(*m_currentPlayer);
		if (!m_currentPlayer->GetIllusionPlayed())
			Illusion(*m_currentPlayer);
		break;
	}
	case Eter::ElementalCardName::WAVE:
		std::cout << "WAVE: Move any card/stack to the adjacent empty space, then play a card from your hand to this now empty space.\n";
		element.Wave(GameBoard, *m_currentPlayer);
		break;

	case Eter::ElementalCardName::WHIRLPOOL:
		std::cout << "WHIRLPOOL: Move onto empty space two cards from different adjacent spaces in a straight line.The card of lower value goes to the bottom of the stack.\n";
		element.Whirlpool(GameBoard);
		break;

	case Eter::ElementalCardName::BLIZZARD:
		std::cout << "BLIZZARD: Place this card onto any space and choose a row or column that it will impact.The opponent cannot play any cards onto the chosen row / column during his next turn.Condition - your opponent must have a free space to play a card.Remove this card from play after the next opponent turn. \n";
		//elemental.Blizzard(GameBoard);
		break;

	case Eter::ElementalCardName::SUPPORT:
		std::cout << "SUPPORT: Value of a chosen card on the board is increased by +1 (cannot be used on a '4' card).\n";
		element.Support(GameBoard);
		break;

	case Eter::ElementalCardName::EARTHQUAKE:
		std::cout << "EARTHQUAKE: Remove from play all visible ‘1’ cards.\n";
		element.Earthquake(GameBoard);
		break;

	case Eter::ElementalCardName::CRUMBLE:
		std::cout << "CRUMBLE: Value of a card on the board is decreased by 1 (cannot be used on a ‘1’ card).\n";
		element.Crumble(GameBoard);
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
			element.Rock(GameBoard, Player1, Player2);
		else
			element.Rock(GameBoard, Player2, Player1);
		break;
	default:
		std::cout << "Invalid option. Please choose a valid option.\n";
		break;
	}
}

void Eter::WizzardAndElementalMode::CreateFromJsonWizardElemental(const nlohmann::json& gameInfo)
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
	m_wizardPlayer1 = gameInfoJson.at("wizardPlayer1").get<Wizards>();
	m_wizardPlayer2 = gameInfoJson.at("wizardPlayer2").get<Wizards>();

	m_wizardPlayer1.SetBoardForMage(&m_board);
	m_wizardPlayer2.SetBoardForMage(&m_board);
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

void Eter::WizzardAndElementalMode::ExportToJsonWizardElemental()
{
	std::string filename = Eter::GenerateSaveFilename("wizardANDelemental");
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
			{"elementCard1", m_elementCard1},
			{"elementCard2", m_elementCard2},
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
