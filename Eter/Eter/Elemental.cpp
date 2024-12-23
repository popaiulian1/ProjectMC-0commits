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
				tile.value().GetValue().pop_back();
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

void Eter::Elemental::Flame(Player& opponent, Board& board, const Piece& playerCard)
{
	bool illusionRevealed = false;
	auto gameBoard = board.GetBoardReference();

	for (int row = 0; row < board.GetCurrentSize(); ++row) {
		for (int col = 0; col < board.GetCurrentSize(); ++col) {
			auto &tileOptional = gameBoard[row][col];

			// First we verify if the optional has any values
			if (tileOptional.has_value() && !tileOptional->GetValue().empty()) {
				Piece topPiece = tileOptional.value().GetTopValue();
				if (topPiece.GetIsIllusion() && topPiece.GetUserName()==opponent.GetUserName()) {
					illusionRevealed = true;
					std::cout << "Illusion revealed at position (" << row << ", " << col << ").\n";
					topPiece.SetIsIllusion(false); 
					break;
				}
			}
		}
		if (illusionRevealed) break;
	}

	if (!illusionRevealed) {
		std::cout << "No opponent's illusions found.\n";
	}

	std::cout << "Choose a position to place your card on the playing field (row, column):\n";
	int destRow, destCol;
	std::cin >> destRow >> destCol;

	if (destRow < 0 || destRow >= board.GetCurrentSize() || destCol < 0 || destCol >= board.GetCurrentSize()) {
		std::cout << "Invalid position. Card placement failed.\n";
		return;
	}

	auto& destTileOptional = board.GetBoardReference()[destRow][destCol];
	if (!destTileOptional || !destTileOptional->GetValue().empty() || destTileOptional->IsPit()) {
		std::cout << "The chosen position is occupied or a pit. Card placement failed.\n";
		return;
	}

	destTileOptional->SetValue(playerCard);
	std::cout << "Card successfully placed at (" << destRow << ", " << destCol << ").\n";

	m_ElementalCardUsed = true;
}

void Eter::Elemental::Fire(Board& board, Player& player1, Player& player2)
{
	auto gameBoard = board.GetBoardReference();
	std::unordered_map<char, int> cardCounts;

	// Counting the visible cards on the board
	for (int row = 0; row < board.GetCurrentSize(); ++row) {
		for (int col = 0; col < board.GetCurrentSize(); ++col) {
			auto& tileOptional = gameBoard[row][col];
			if (tileOptional.has_value() && !tileOptional->GetValue().empty()) {
				char topCardValue = tileOptional->GetTopValue().GetValue();
				++cardCounts[topCardValue];
			}
		}
	}

	char chosenValue;
	std::cout << "Choose a card value (with at least 2 visible cards on the board): ";
	std::cin >> chosenValue;

	if (cardCounts[chosenValue] < 2) {
		std::cout << "Not enough cards with value '" << chosenValue << "' on the board.\n";
		return;
	}
	// Eliminating cards witch chosen value and returning them to the owner
	for (int row = 0; row < board.GetCurrentSize(); ++row) {
		for (int col = 0; col < board.GetCurrentSize(); ++col) {
			auto& tileOptional = gameBoard[row][col];
			if (tileOptional.has_value() && !tileOptional->GetValue().empty()) {
				Piece topPiece = tileOptional.value().GetTopValue();
				if (topPiece.GetValue() == chosenValue) {
					// Verify the owner
					if (topPiece.GetUserName() == player1.GetUserName()) {
						// Returning the card
						player1.AddPiece(topPiece);
					}
					else if (topPiece.GetUserName() == player2.GetUserName()) {
						player2.AddPiece(topPiece);
					}

					// Eliminating the card from the board
					if (!tileOptional->GetValue().empty()) {
						tileOptional->GetValue().pop_back(); 
					}

				}
			}
		}
	}

	std::cout << "All cards with value '" << chosenValue << "' have been returned to their owners.\n";

}

void Eter::Elemental::Ash(Board& board, Player& player)
{
	auto& playerPieces = player.GetPiecesReference();
	auto& gameBoard = board.GetBoardReference();

	// Verify if the player has eliminated cards 
	auto it = std::find_if(playerPieces.begin(), playerPieces.end(), [](const Piece& piece) {
		return piece.GetIsEliminated();
	});

	if (it != playerPieces.end()) {
		Piece& eliminatedPiece = *it;
		std::cout << "Where yould you like to place your card(row, column)?\n";
		int row, col;
		std::cin >> row >> col;
		if (row < 0 || row >= board.GetCurrentSize() || col < 0 || col >= board.GetCurrentSize() || gameBoard[row][col].has_value()) {
			std::cout << "Invalid position. Card placement failed.\n";
			return;
		}
		gameBoard[row][col] = Tile(eliminatedPiece);

		eliminatedPiece.SetIsEliminated(false);
		eliminatedPiece.SetIsPlaced(true);

		std::cout << "Card '" << eliminatedPiece.GetValue() << "' placed at (" << row << ", " << col << ").\n";
	}
	else 
		std::cout << "No eliminated cards available to play.\n";
	
}

//void Eter::Elemental::Spark(Board& board, Player& player)
//{
//	auto& gameBoard = board.GetBoardReference();
//	const auto& playerName = player.GetUserName();
//
//	std::vector<std::pair<int, int>> coveredCardsPositions;
//
//	// We stack in a vector the cards that are ours and under the opponent's card
//	for (int row = 0; row <board.GetCurrentSize(); ++row) {
//		for (int col = 0; col <board.GetCurrentSize(); ++col) {
//			auto& tileOptional = gameBoard[row][col];
//			if (tileOptional.has_value() && tileOptional->GetValue().size() > 1 && tileOptional.value().GetTopValue().GetUserName()!=player.GetUserName()) {
//				auto stack = tileOptional->GetValue();
//				for (size_t i = 0; i < stack.size() - 1; ++i) 
//					if (stack[i].GetUserName() == playerName) {
//						coveredCardsPositions.emplace_back(stack[i]);
//						break;
//					}
//				
//			}
//		}
//	}
//	if (coveredCardsPositions.empty()) {
//		std::cout << "No covered cards belonging to you were found.\n";
//		return;
//	}
//	std::cout << "Covered cards found at the following positions:\n";
//	for (size_t i = 0; i < coveredCardsPositions.size(); ++i) {
//		std::cout << i + 1 << ": (" << coveredCardsPositions[i].first << ", " << coveredCardsPositions[i].second << ")\n";
//	}
//
//	std::cout << "Choose a card to move by entering the corresponding number: ";
//	int choice;
//	std::cin >> choice;
//
//	if (choice < 1 || choice > coveredCardsPositions.size()) {
//		std::cout << "Invalid choice. Operation canceled.\n";
//		return;
//	}
//	
//}

void Eter::Elemental::Destruction(const Player& opponent, const Board& board)
{
	auto GameBoard = board.GetBoard();

	for (auto& row : GameBoard) {
		for (auto& tile : row) {
			if (tile.value().GetTopValue().GetValue() == opponent.GetLastPlayedPiece().GetValue())
				tile.value().GetValue().pop_back();
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

					tile.value().GetValue().pop_back(); //remove the piece from the board
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
					std::deque<Piece> pieceStack = currentTile.GetValue();
					Piece topPiece = pieceStack.back();

					currentTile.RemoveStack();
					currentTile.SetValue(topPiece);

					//returning the other pieces to their owner
					while (!pieceStack.empty()) {
						Piece currentPiece = pieceStack.back();
						pieceStack.pop_back();
						
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


