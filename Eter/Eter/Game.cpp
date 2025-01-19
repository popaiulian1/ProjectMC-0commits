#include "Game.h"

Eter::Game::Game() : m_player1{ Player() }, m_player2{ Player() }, m_board{ Board(GameType::Practice) },
	m_currentPlayer{ &m_player1 }, m_gameType{ GameType::Practice }, m_rounds{ 0 }, m_bluePlayerName{ m_player1.GetUserName() }
{}

Eter::Game::Game(const Player& player1, const Player& player2, const Board& board, const GameType& gameType) : 
	m_board(board), m_player1(player1), m_player2(player2), m_gameType(gameType)
{}

void Eter::Game::StartGame()
{
	std::cout << "This is the Practice Mode\n";
	std::cout << "_____________________________\n";
	if (m_gameType == GameType::Practice) {
		InitializePracticeGame();
		PlayGame();
	}
}

void Eter::Game::InitializePracticeGame()
{
	m_board = Board(GameType::Practice);
	std::vector<char> Values = { '1', '1', '2', '2', '3', '3', '4' }; // Define the values of the cards in the practice deck
	std::vector<Eter::Piece> CardsPractice(kDECK_SIZE_PRACTICE); // Resize the practice deck to the size of the practice deck

	UsernameHandling();

	int index = 0;
	for (auto& card : CardsPractice) {
		card.SetValue(Values[index++]);
		card.SetIsPlaced(false);
		card.SetUserName("");
		card.SetIsIllusion(false);
	}

	firstMove = true;

	m_player1.SetPieces(CardsPractice);
	m_player2.SetPieces(CardsPractice);
	ResetPlayerData(m_player1);
	ResetPlayerData(m_player2);
}

void Eter::Game::UsernameHandling()
{
	std::string username;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	if (m_player1.GetUserName() == "") {
		std::cout << "Username of the first player is: ";
		std::getline(std::cin, username);
		m_player1.SetUserName(username);
		m_bluePlayerName = m_player1.GetUserName();
	}

	if (m_player2.GetUserName() == "") {
		std::cout << "Username of the second player is: ";
		std::getline(std::cin, username);
		m_player2.SetUserName(username);
	}
}

void Eter::Game::ResetPlayerData(Player& player)
{
	player.SetIllusionPlayed(false);
	player.SetScore(0);
	player.SetGamesWon(0);
}

void Eter::Game::PrintWinner(const Player& player) const
{
	std::cout << "\n\n<=============================================================>\n" << std::endl;
	std::cout << "Congratulations! The winner is " << player.GetUserName() << "!\n";
	std::cout << "\n<=============================================================>" << std::endl;
}

void Eter::Game::PlayGame()
{
	while (m_rounds <= 3) {

		if (m_currentPlayer != nullptr)
			if (m_currentPlayer->GetPieces().size() == 0) {
				std::cout << "The game is over!\n" << m_currentPlayer->GetUserName() << " has no more pieces!";
				m_currentPlayer == &m_player1 ? m_currentPlayer = &m_player2 : m_currentPlayer = &m_player1;
				m_currentPlayer->SetGamesWon(m_currentPlayer->GetGamesWon() + 1);
				++m_rounds;
				StartGame();
				break;
			}

		//switch players
		m_currentPlayer == &m_player1 ? m_currentPlayer = &m_player2 : m_currentPlayer = &m_player1;

		m_board.PrintBoardForFormatedOutput(m_bluePlayerName); // Print the board
		std::cout << m_currentPlayer->GetUserName() << ", it's your turn.\n";

		char option;
		std::cout << "                 OPTIONS:       \n";
		std::cout << "________________________________________________\n";
		std::cout << "a. Choose piece\n";
		std::cout << "b. Play illusion\n";
		std::cout << "c. Play explosion\n";
		std::cout << "s. Save Game\n";
		std::cout << "________________________________________________\n";
		std::cout << "Choose your option: \n";
		std::cin >> option;

		switch (option) {
		case 'a': {
			m_board.SetTileValue(m_currentPlayer->Play(firstMove), m_currentPlayer->ChoosePiece(), m_currentPlayer->GetUserName());
			break;
		}
		case 'b': {
			/*std::regex YesPattern("yes|Yes|YES");
			std::regex NoPattern("no|No|NO");*/
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
		case 's': {
			ExportToJson();
			break;
		}
		default: {
			std::cout << "Invalid option. Please choose a valid option.\n";
			break;
		}
		}

		if (m_board.GetCurrentSize() == m_board.GetMaxSize() || CheckCompleteRowOrColumn()) {
			if (CheckWinner()) {
				++m_rounds;
				m_currentPlayer->SetGamesWon(m_currentPlayer->GetGamesWon() + 1);
				StartGame();
			}
		}
	}
}

bool Eter::Game::CheckWinner()
{
	if (m_currentPlayer->HasWon(m_board) == true) {
		PrintWinner(*m_currentPlayer);
		return true;
	}
	else if (m_board.CheckEmptyTiles() == true) {
		std::unique_ptr<Player> otherPlayer = std::make_unique<Player>(m_currentPlayer == &m_player1 ? m_player2 : m_player1);

		if (otherPlayer->HasWon(m_board) == true) {
			PrintWinner(*m_currentPlayer);
			return true;
		}
	}
	else if (m_board.CheckEmptyTiles() == false && m_board.GetBoard()[0].size() == m_board.GetMaxSize() && m_board.GetCurrentSize() == m_board.GetMaxSize()) {
		TotalScore(m_player1, m_board);
		TotalScore(m_player2, m_board);
		if (m_player1.GetScore() > m_player2.GetScore()) {
			PrintWinner(m_player1);
			return true;
		}
		else {
			PrintWinner(m_player2);
			return true;
		}
	}
	return false;
}

void Eter::Game::TotalScore(Player& player, const Board& board)
{
	int score = 0;
	auto GameBoard = board.GetBoard();
	for (auto& row : GameBoard)
	{
		for (auto& tile : row)
		{
			if (tile.value().GetTopValue().GetUserName() == player.GetUserName() && tile.value().GetTopValue().GetIsIllusion())
				score += 1;
			else if(tile.value().GetTopValue().GetUserName() == player.GetUserName())
				score += tile.value().GetTopValue().GetValue() - '0';
		}
	}
	player.SetScore(score);
}

bool Eter::Game::CheckCompleteRowOrColumn() const
{
	BoardMatrix board = m_board.GetBoard();
	size_t maxSize = m_board.GetMaxSize();

	// Check rows
	for (const auto& row : board) {
		int filledTiles = 0;
		for (const auto& tile : row) {
			if (tile.has_value()) {
				++filledTiles;
			}
		}
		if (filledTiles == maxSize) {
			return true;
		}
	}

	// Check columns
	for (int col = 0; col < board[0].size(); ++col) {
		int filledTiles = 0;
		for (int row = 0; row < board.size(); ++row) {
			if (board[row][col].has_value()) {
				++filledTiles;
			}
		}
		if (filledTiles == maxSize) {
			return true;
		}
	}

	return false;
}

void Eter::Game::ExportToJson()
{
	std::string filename = Eter::GenerateSaveFilename("practice");
	std::ofstream file("./SaveGames/"+filename);

	if (file.is_open()) {
		nlohmann::json j_game;
		j_game["boardInfo"] = m_board;
		j_game["playerInfo"] = { {"player1", m_player1}, {"player2", m_player2}};
		j_game["gameInfo"] = {
			{"gameType", m_gameType},
			{"rounds", m_rounds},
			{"bluePlayerName", m_bluePlayerName},
			{"currentPlayer", *m_currentPlayer},
			{"firstMove", firstMove},
		};
		file << j_game.dump(4);
		file.close();
		std::cout << "Game saved to " << filename << std::endl;
	}
	else {
		std::cerr << "Error opening file " << filename << std::endl;
	}
}

void Eter::Game::CreateFromJson(const nlohmann::json& gameInfo)
{
	//create board
	m_board = gameInfo.at("boardInfo").get<Board>();

	//create players
	nlohmann::json playerInfo = gameInfo.at("playerInfo");
	m_player1 = playerInfo.at("player1").get<Eter::Player>();
	m_player2 = playerInfo.at("player2").get<Eter::Player>();
	
	//create game info
	nlohmann::json gameInfoJson = gameInfo.at("gameInfo");
	m_gameType = gameInfoJson.at("gameType").get<GameType>();
	m_rounds = gameInfoJson.at("rounds").get<size_t>();
	m_bluePlayerName = gameInfoJson.at("bluePlayerName").get<std::string>();

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

void Eter::Game::addBorderToMatrix(Eter::BoardMatrix& board)
{
	board.insert(board.begin(), std::vector<std::optional<Tile>>(board[0].size()));
	board.push_back(std::vector<std::optional<Tile>>(board[0].size()));

	for (auto& row : board) {
		row.insert(row.begin(), std::optional<Tile>());
		row.push_back(std::optional<Tile>());
	}
}

bool Eter::Game::checkAdjacent(const Eter::Board::Position& pos, const Eter::Piece& pieceToBeAdded)
{
	Eter::BoardMatrix board = m_board.GetBoard();

	auto& [row, col] = pos;

	addBorderToMatrix(board);

	board[row][col].value().SetValue(pieceToBeAdded);

	addBorderToMatrix(board);

	if (board[row - 1][col].value().GetTopValue().GetValue() == pieceToBeAdded.GetValue() ||
		board[row + 1][col].value().GetTopValue().GetValue() == pieceToBeAdded.GetValue() ||
		board[row][col - 1].value().GetTopValue().GetValue() == pieceToBeAdded.GetValue() ||
		board[row][col + 1].value().GetTopValue().GetValue() == pieceToBeAdded.GetValue())
	{
		return true;
	}

	return false;
}

void Eter::Game::Illusion(Player& player)
{
	const std::pair<int, int>& Position = player.Play(firstMove);
	int row = Position.first, column = Position.second;
	bool canPlace = false;

	if (row < 0 || column < 0 || row >= m_board.GetCurrentSize() || column >= m_board.GetBoard()[row].size())
	{
		canPlace = true;
	}else if (m_board.GetBoard()[row][column].has_value()) {
		canPlace = false;
	}
	else
		canPlace = true;
	
	if (canPlace) {
		player.SetIllusionPlayed(true);
		m_board.SetTileValue(Position, player.ChoosePiece(), player.GetUserName());
		row < 0 ? row = 0 : row;
		column < 0 ? column = 0 : column;
		m_board.GetBoardReference()[row][column] = Tile(Piece(player.GetLastPlayedPiece().GetValue(), true, player.GetUserName(), true, false));
	}
	else {
		std::cout << "You cannot place your illusion card there.\n";
	}

}

void Eter::Game::SetPlayer1(const Player& player)
{
	m_player1 = player;
}

void Eter::Game::SetPlayer2(const Player& player)
{
	m_player2 = player;
}

void Eter::Game::SetBoard(const Board& board)
{
	m_board = board;
}

Eter::Player& Eter::Game::GetPlayer1Reference() 
{
	return m_player1;
}

Eter::Player Eter::Game::GetPlayer1() const
{
	return m_player1;
}

Eter::Player& Eter::Game::GetPlayer2Reference()
{
	return m_player2;
}

Eter::Player Eter::Game::GetPlayer2() const
{
	return m_player2;
}

Eter::Board Eter::Game::GetBoard() const
{
	return m_board;
}

Eter::Board& Eter::Game::GetBoardReference()	
{
	return m_board;
}

Eter::GameType Eter::Game::GetGameType() const
{
	return m_gameType;
}

const std::string& Eter::Game::GetBluePlayerName() const
{
	return m_bluePlayerName;
}

void Eter::Game::SetGameType(const GameType& gameType)
{
	m_gameType = gameType;
}

void Eter::Game::SetBluePlayerName(const std::string& name)
{
	m_bluePlayerName = name;
}
