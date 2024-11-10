#include "Game.h"
#include <iostream>

Eter::Game::Game(const Player& player1, const Player& player2, const Board& board, const GameType& gameType)
{
	m_player1 = player1;
	m_player2 = player2;
	m_board = board;
	m_gameType = gameType;
}

void Eter::Game::StartGame()
{
	if (m_gameType == GameType::Practice) {
		std::vector<int> Values = { 1, 1, 2, 2, 3, 3, 4 };
		std::vector<Eter::Piece> CardsPractice;

		CardsPractice.resize(kDECK_SIZE_PRACTICE);

		int index = 0;
		for (auto& card : CardsPractice) 
			card.SetValue(Values[index++]);
		
		m_player1.setCards(CardsPractice);
		m_player2.setCards(CardsPractice);

		std::cout << "The initial board is: " << m_board << "\n";

		std::cout << m_player1.GetUserName() << " has the following deck: ";
		for (const auto& values : m_player1.GetCards())
			std::cout << values.GetValue() << " ";
		std::cout << "\n";

		std::cout << m_player2.GetUserName() << " has the following deck: ";
		for (const auto& values : m_player1.GetCards())
			std::cout << values.GetValue() << " ";
		std::cout << "\n";
	}
}

void Eter::Game::PrintBoard() const
{
	std::cout << "Current Board:\n";
	std::cout << m_board << std::endl;
}

void Eter::Game::PrintWinner() const
{
	if (CheckWinner()) {
		const Player& winner = m_player1.HasWon(m_board) ? m_player1 : m_player2;
	    std::cout << "Congratulations! The winner is " << winner.GetUserName() << "!\n";
	}
	else if (CheckDraw())
		std::cout << "The game is a draw.\n";

	else
		std::cout << "The game is ongoing. No winner yet.\n";

}

void Eter::Game::PlayGame()
{
}

bool Eter::Game::CheckWinner() const
{
	if (m_board.GetCurrentSize() < m_board.GetMaxSize()) {
		return false;
	}
	else {
		std::vector<std::vector<std::optional<Tile>>> board = m_board.GetBoard();

		//To edit to add check based on username.
		for (size_t i = 0; i < m_board.GetMaxSize(); i++)
		{
			if (board[i][0].has_value() && board[i][1].has_value() && board[i][2].has_value())
			{
				if (board[i][0].value().GetValue() == board[i][1].value().GetValue() && board[i][1].value().GetValue() == board[i][2].value().GetValue())
				{
					return true;
				}
			}
			if (board[0][i].has_value() && board[1][i].has_value() && board[2][i].has_value())
			{
				if (board[0][i].value().GetValue() == board[1][i].value().GetValue() && board[1][i].value().GetValue() == board[2][i].value().GetValue())
				{
					return true;
				}
			}
		}
		if (board[0][0].has_value() && board[1][1].has_value() && board[2][2].has_value())
		{
			if (board[0][0].value().GetValue() == board[1][1].value().GetValue() && board[1][1].value().GetValue() == board[2][2].value().GetValue())
			{
				return true;
			}
		}
		if (board[0][2].has_value() && board[1][1].has_value() && board[2][0].has_value())
		{
			if (board[0][2].value().GetValue() == board[1][1].value().GetValue() && board[1][1].value().GetValue() == board[2][0].value().GetValue())
			{
				return true;
			}
		}
		return false;

	}
}

bool Eter::Game::CheckDraw() const
{
	std::vector<std::vector<std::optional<Tile>>> board = m_board.GetBoard();

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
