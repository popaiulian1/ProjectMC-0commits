#include "Game.h"
#include <iostream>

Eter::Game::Game(const Player& player1, const Player& player2, const Board& board, const GameType& gameType)
{
	m_player1 = player1;
	m_player2 = player2;
	m_board = board;
	m_gameType = gameType;
}

void Eter::Game::StartGame(Player& player1, Player& player2, Board& board)
{
	if (m_gameType == GameType::Practice) {

		board = Board(GameType::Practice); // Create a practice board
		std::vector<char> Values = { '1', '1', '2', '2', '3', '3', '4' }; // Define the values of the cards in the practice deck
		std::vector<Eter::Piece> CardsPractice;

		std::string UsernamePlayer1; // Define the username of the first player
		std::string UsernamePlayer2; // Define the username of the second player

		if (player1.GetUserName() == "") { // If the username of the first player is not set, ask the user to set it
			std::cout << "Username of the first player is: ";
			std::getline(std::cin, UsernamePlayer1);
			player1.setUserName(UsernamePlayer1);
		}

		if (player2.GetUserName() == "") { // If the username of the second player is not set, ask the user to set it
			std::cout << "Username of the second player is: ";
			std::getline(std::cin, UsernamePlayer2);
			player2.setUserName(UsernamePlayer2);
		}

		CardsPractice.resize(kDECK_SIZE_PRACTICE); // Resize the practice deck to the size of the practice deck

		int index = 0;
		for (auto& card : CardsPractice) 
			card.SetValue(Values[index++]); // Set the values of the cards in the practice deck
		
		player1.setCards(CardsPractice); // Set the cards of the first player to the cards in the practice deck
		player2.setCards(CardsPractice); // Set the cards of the second player to the cards in the practice deck

		std::cout << "The initial board is: " << m_board << "\n";

		std::cout << player1.GetUserName() << " has the following deck: ";
		for (const auto& values : player1.GetCards())
			std::cout << values.GetValue() << " ";
		std::cout << "\n";

		std::cout << player2.GetUserName() << " has the following deck: ";
		for (const auto& values : player1.GetCards())
			std::cout << values.GetValue() << " ";

		Game::SetPlayer1(player1); 
		Game::SetPlayer2(player2);
	}
}

void Eter::Game::PrintBoard() const
{
	std::cout << "Current Board:\n";
	std::cout << m_board << std::endl;
}

void Eter::Game::PrintWinner( const Player &player) const
{
	    std::cout << "Congratulations! The winner is " << player.GetUserName() << "!\n";

}

void Eter::Game::PlayGame()
{} 

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

int Eter::Game::TotalScore(Player& player, const Board& board) 
{
	auto GameBoard = board.GetBoard();
	for (auto& row : GameBoard)
	{
		for (auto& tile : row)
		{
			while (!tile.value().GetValue().empty()) {
				if (tile.value().GetTopValue().GetUserName() == player.GetUserName()) {
					int score = tile.value().GetTopValue().GetValue() - '0';
					player.setScore(score);
				}
				tile.value().GetValue().pop();
			}
		}
	}
}

bool Eter::Game::CheckDraw() const
{
	BoardMatrix board = m_board.GetBoard();

	for (auto& row : board)
	{
		for (auto& line : row)
		{
			if (!line.has_value())
			{
				return false;
			}
		}
	}
	return true;

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
		for (int cards = 0; cards < player.GetCards().size(); ++cards)
			if (player.GetCards()[cards].GetValue() == card)
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
	board.SetTileValue({ row, column }, card, player); // Set the tile value of the board to the card that has been played
	player.SetFaceDownCardPlayed(true); // Set the illusion card played to true
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
