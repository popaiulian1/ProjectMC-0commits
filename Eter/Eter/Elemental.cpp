#include "Elemental.h"
#include <algorithm>
#include "Board.h"
#include "Tile.h"

Eter::Elemental::Elemental(const Board board, bool ElementalCardUsed, ElementalCardName nameCard) : m_board{ board }, m_ElementalCardUsed{ ElementalCardUsed }, m_nameCard{ nameCard }
{}

Eter::Elemental::Elemental(const Elemental& other) : m_board{ other.m_board }, m_ElementalCardUsed{ other.m_ElementalCardUsed }, m_nameCard{ other.m_nameCard }
{}

void Eter::Elemental::Tide(int row1, int column1, int row2, int column2) //Change positions of 2 different cards or stacks of cards.
{
	//row1, column1 -> coordinates of the first tile
	//row2, column2 -> coordinates of the second tile
	if (row1 < 0 || row1 >= m_board.GetCurrentSize())
	{
		throw std::out_of_range{ "Invalid row index!" };
	}
	else if (row2 < 0 || row2 >= m_board.GetCurrentSize())
	{
		throw std::out_of_range{ "Invalid row index!" };
	}
	else if (column1 < 0 || column1 >= m_board.GetCurrentSize()) {
		throw std::out_of_range{ "Invalid column index!" };
	}
	else if (column2 < 0 || column2 >= m_board.GetCurrentSize()) {
		throw std::out_of_range{ "Invalid column index!" };
	}

	//swap between card / stack of cards.
	std::swap(m_board.GetBoardReference()[row1][column1], m_board.GetBoardReference()[row2][column2]);
}

void Eter::Elemental::Mist(Player& player)
{
	player.SetIllusionPlayed(false);
}

void Eter::Elemental::Earthquake(const Board& board)
{
	auto GameBoard = board.GetBoard();
	for (auto& row : GameBoard)
	{
		for (auto& tile : row)
		{
			if (tile.value().GetTopValue().GetValue() == '1')
				tile.value().GetValue().pop();
		}
	}

}

void Eter::Elemental::Rock(Board& board, Player& player, Player& opponent)
{
	auto gameBoard = board.GetBoardReference();

	if (opponent.GetIllusionPlayed() == NULL) {
		std::cerr << "ROCK: No illusion to be covered!";
		return;
	}
	else {
		Piece illusionCheckPiece;
		
		int row, column;
		while (true) {
			std::cout << "ROCK: Enter row index for illusion to be covered: ";
			std::cin >> row;
			std::cout << "ROCK: Enter column index for illusion to be covered: ";
			std::cin >> column;

			if (row < 0 || column < 0 || row >= board.GetCurrentSize() || column >= board.GetCurrentSize()) {
				std::cerr << "ROCK: Invalid position! Please enter valid indices." << std::endl;
				continue;
			}

			auto& currentTile = gameBoard[row][column];
			if (currentTile.value().GetTopValue().GetIsIllusion() == true && currentTile.value().GetTopValue().GetUserName() == opponent.GetUserName()) {
				auto& targetTile = gameBoard[row][column].value();
				//TO DO-> GEORGE: put the chosen piece on board over the illusion one

			}
		}
	}
}

void Eter::Elemental::Destruction(const Player& opponent, const Board& board)
{
	auto GameBoard = board.GetBoard();

	for (auto& row : GameBoard) {
		for (auto& tile : row) {
			if (tile.value().GetTopValue().GetValue() == opponent.GetLastPlayedPiece().GetValue())
				tile.value().GetValue().pop();
		}
	}
}

void Eter::Elemental::Squall(Player& opponent, Board& board)
{
	auto gameBoard = board.GetBoard();

	for (auto& row : gameBoard) {
		for (auto& tile : row) {
			if (tile.has_value()) {
				if (tile.value().GetTopValue().GetUserName() == opponent.GetUserName()) {
					Piece removedPiece(tile.value().GetTopValue()); //add the future removed piece back in the opponents deck
					opponent.AddPiece(removedPiece);

					tile.value().GetValue().pop(); //remove the piece from the board
				}
			}
		}
	}
}

void Eter::Elemental::Gale(Board& board, Player& player1, Player& player2)
{
	auto& gameBoard = board.GetBoardReference();

	for (auto& row : gameBoard) {
		for (auto& tile : row) {
			if (tile.has_value()) {
				Tile& currentTile = tile.value();

				if (currentTile.GetValue().size() > 1) {
					std::stack<Piece> pieceStack = currentTile.GetValue();
					Piece topPiece = pieceStack.top();

					currentTile.RemoveStack();
					currentTile.SetValue(topPiece);

					//returning the other pieces to their owner
					while (!pieceStack.empty()) {
						Piece currentPiece = pieceStack.top();
						pieceStack.pop();
						
						if (currentPiece.GetUserName() == player1.GetUserName()) {
							player1.AddPiece(currentPiece);
						}
						else if (currentPiece.GetUserName() == player2.GetUserName()) {
							player2.AddPiece(currentPiece);
						}
					}
				}
			}
		}
	}

}

void Eter::Elemental::Storm(int row, int column) //Remove from play any stack of minimum 2 cards
{
	uint8_t StackSize = m_board.GetBoardReference()[row][column].value().GetValue().size();
	if (StackSize >= 2)
	{
		while (!m_board.GetBoard().empty())
			m_board.GetBoardReference().pop_back();
		m_ElementalCardUsed = true;
	}
	else
	{
		throw std::out_of_range{ "The stack has less then 2 cards!" };
	}
}


