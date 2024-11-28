#include "Game.h"
#include <iostream>

Eter::Game::Game(const Player& player1, const Player& player2, const Board& board, const GameType& gameType) : m_board(board)
{
	m_player1 = player1;
	m_player2 = player2;
	m_gameType = gameType;
}

void Eter::Game::StartGame()
{
	if (m_gameType == GameType::Practice) {

		m_board = Board(GameType::Practice);
		std::vector<char> Values = { '1', '1', '2', '2', '3', '3', '4' }; // Define the values of the cards in the practice deck
		std::vector<Eter::Piece> CardsPractice;

		std::string UsernamePlayer1;
		std::string UsernamePlayer2;

		if (m_player1.GetUserName() == "") {
			std::cout << "Username of the first player is: ";
			std::getline(std::cin, UsernamePlayer1);
			m_player1.SetUserName(UsernamePlayer1);
		}

		if (m_player2.GetUserName() == "") {
			std::cout << "Username of the second player is: ";
			std::getline(std::cin, UsernamePlayer2);
			m_player2.SetUserName(UsernamePlayer2);
		}

		CardsPractice.resize(kDECK_SIZE_PRACTICE); // Resize the practice deck to the size of the practice deck

		int index = 0;
		for (auto& card : CardsPractice) {
			card.SetValue(Values[index++]);
			card.SetIsPlaced(false);
			card.SetUserName("");
		}

		m_player1.SetPieces(CardsPractice);
		m_player2.SetPieces(CardsPractice);
		m_player1.SetIllusionPlayed(false);
		m_player2.SetIllusionPlayed(false);
		m_player1.SetScore(0);
		m_player2.SetScore(0);
		m_player1.SetGamesWon(0);
		m_player2.SetGamesWon(0);

		PlayGame();
	}
}

void Eter::Game::PrintWinner(const Player& player) const
{
	std::cout << "Congratulations! The winner is " << player.GetUserName() << "!\n";
}

void Eter::Game::PlayGame()
{
	while (m_rounds <= 3) {
		m_board.PrintBoardForFormatedOutput(); // Print the board
		m_currentPlayer == &m_player1 ? m_currentPlayer = &m_player2 : m_currentPlayer = &m_player1;
		std::cout << m_currentPlayer->GetUserName() << ", it's your turn.\n";

		m_board.SetTileValue(m_currentPlayer->Play(), m_currentPlayer->ChoosePiece(), m_currentPlayer->GetUserName());

		/*if (CheckWinner()) {
			++m_rounds;
			m_currentPlayer->SetGamesWon(m_currentPlayer->GetGamesWon() + 1);
			StartGame();
		}*/
	}
}

bool Eter::Game::CheckWinner()
{
	if (CheckDraw() == false) {
		if (m_board.GetCurrentSize() == m_board.GetMaxSize()) {
			if (m_player1.HasWon(m_board) == true) {
				PrintWinner(m_player1);
				return true;
			}
			else if (m_player2.HasWon(m_board) == true) {
				PrintWinner(m_player2);
				return true;
			}
		}
	}
	else if (CheckDraw() == true) {
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
			if (tile.value().GetTopValue().GetUserName() == player.GetUserName())
				score += tile.value().GetTopValue().GetValue() - '0';
		}
	}
	player.SetScore(score);
}


bool Eter::Game::CheckCompleteRowOrColumn() const
{
	BoardMatrix board = m_board.GetBoard();
	int maxSize = m_board.GetMaxSize();

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

bool Eter::Game::CheckDraw() const
{
	BoardMatrix board = m_board.GetBoard();
	for (int i = 0; i < board.size(); ++i) {
		if (board.size() == m_board.GetMaxSize()) {
			for (int j = 0; j < board[i].size(); ++j){
				if (board[i][j].has_value() && board[i].size() <= m_board.GetMaxSize())
					return true;
			}
		}	
	}
	return false;
}

void Eter::Game::Illusion(Player& player, Board& board)
{
	std::cout << player.GetUserName() << ", please enter the position of the card you want to play:\n"; // Ask the player to enter the position of the card they want to play
	int row, column;
	std::cout << "Row: "; std::cin >> row;
	std::cout << "Column: "; std::cin >> column;

	while ((row >= board.GetCurrentSize() || column >= board.GetCurrentSize()) &&
		!board.GetBoard()[row][column].has_value()) // Check if the position is valid
	{
		std::cout << "Invalid position. Please enter a valid position.\n";
		std::cout << "Row: "; std::cin >> row;
		std::cout << "Column: "; std::cin >> column;
	}

	std::cout << player.GetUserName() << ", choose a card to play: "; // Ask the player to choose a card to play
	char card;
	std::cin >> card;

	bool valid = false;
	while (valid == false) { // Check if the card is valid
		for (int cards = 0; cards < player.GetPieces().size(); ++cards)
			if (player.GetPieces()[cards].GetValue() == card)
			{
				valid = true;
				break;
			}
		if (valid == false) {
			std::cout << "Invalid card, please choose a valid card: ";
			std::cin >> card;
		}
	}
	std::cout << "The card " << card << " has been played at position (" << row << ", " << column << ").\n"; // Print the card that has been played at the position
	board.SetTileValue({ row, column }, card, player.GetUserName()); // Set the tile value of the board to the card that has been played
	player.SetIllusionPlayed(true); // Set the illusion card played to true
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

Eter::Player Eter::Game::GetPlayer1() const
{
	return m_player1;
}

Eter::Player Eter::Game::GetPlayer2() const
{
	return m_player2;
}

Eter::Board Eter::Game::GetBoard() const
{
	return m_board;
}
