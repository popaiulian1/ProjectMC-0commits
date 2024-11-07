#include "Game.h"

Eter::Game::Game(const Player& player1, const Player& player2, const Board& board, const GameType& gameType)
{
	m_player1 = player1;
	m_player2 = player2;
	m_board = board;
	m_gameType = gameType;
}

void Eter::Game::StartGame()
{
}

void Eter::Game::PrintBoard() const
{
}

void Eter::Game::PrintWinner() const
{
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
