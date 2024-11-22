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

		m_board = Board(GameType::Practice); // Create a practice board
		std::vector<char> Values = { '1', '1', '2', '2', '3', '3', '4' }; // Define the values of the cards in the practice deck
		std::vector<Eter::Piece> CardsPractice;

		std::string UsernamePlayer1; // Define the username of the first player
		std::string UsernamePlayer2; // Define the username of the second player

		if (m_player1.GetUserName() == "") { // If the username of the first player is not set, ask the user to set it
			std::cout << "Username of the first player is: ";
			std::getline(std::cin, UsernamePlayer1);
			m_player1.SetUserName(UsernamePlayer1);
		}

		if (m_player2.GetUserName() == "") { // If the username of the second player is not set, ask the user to set it
			std::cout << "Username of the second player is: ";
			std::getline(std::cin, UsernamePlayer2);
			m_player2.SetUserName(UsernamePlayer2);
		}

		CardsPractice.resize(kDECK_SIZE_PRACTICE); // Resize the practice deck to the size of the practice deck

		int index = 0;
		for (auto& card : CardsPractice)
			card.SetValue(Values[index++]); // Set the values of the cards in the practice deck

		m_player1.SetPieces(CardsPractice); // Set the cards of the first player to the cards in the practice deck
		m_player2.SetPieces(CardsPractice); // Set the cards of the second player to the cards in the practice deck

		PlayGame();
	}
}

void Eter::Game::PrintWinner(const Player& player) const
{
	std::cout << "Congratulations! The winner is " << player.GetUserName() << "!\n";
}

void Eter::Game::PlayGame()
{
	while (true) {
		m_board.PrintBoardForFormatedOutput(); // Print the board
		m_currentPlayer == &m_player1 ? m_currentPlayer = &m_player2 : m_currentPlayer = &m_player1;
		std::cout << m_currentPlayer->GetUserName() << ", it's your turn.\n";

		m_board.SetTileValue(m_currentPlayer->Play(), m_currentPlayer->ChoosePiece(), m_currentPlayer->GetUserName());
	}
}

bool Eter::Game::CheckWinner()
{
	if (CheckDraw() == false) {
		if (m_player1.HasWon(m_board) == true) {
			PrintWinner(m_player1);
			return true;
		}
		else if (m_player2.HasWon(m_board) == true) {
			PrintWinner(m_player2);
			return true;
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
			while (!tile.value().GetValue().empty()) {
				if (tile.value().GetTopValue().GetUserName() == player.GetUserName()) {
					 score += tile.value().GetTopValue().GetValue() - '0';
					player.SetScore(score);
				}
				tile.value().GetValue().pop();
			}
		}
	}
}

bool Eter::Game::CheckDraw() const
{
	BoardMatrix board = m_board.GetBoard();
	for (int i = 0; i < board.size(); ++i) {
		if (board.size() == m_board.GetMaxSize()) {
			for (int j = 0; j < board[i].size(); ++j){
				if (board[i][j].value().GetValue().empty() && board[i].size() <= m_board.GetMaxSize())
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
