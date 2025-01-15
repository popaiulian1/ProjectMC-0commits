#include "Elemental.h"
#include <algorithm>
#include "Board.h"
#include "Tile.h"

Eter::Elemental::Elemental(const Board board, bool ElementalCardUsed, ElementalCardName nameCard, std::string username) : 
	m_board{ board }, 
	m_ElementalCardUsed{ ElementalCardUsed }, 
	m_nameCard{ nameCard },
	m_username{ username }
{}

Eter::Elemental::Elemental(const Elemental& other) : 
	m_board{ other.m_board }, 
	m_ElementalCardUsed{ other.m_ElementalCardUsed }, 
	m_nameCard{ other.m_nameCard },
	m_username{ other.m_username }
{}

#pragma region Getters and Setters
const bool Eter::Elemental::GetElementalCardUsed() const
{
	return m_ElementalCardUsed;
}

const Eter::ElementalCardName Eter::Elemental::GetNameCard() const
{
	return m_nameCard;
}

const std::string Eter::Elemental::GetUsername() const
{
	return m_username;
}

void Eter::Elemental::SetElementalCardUsed(const bool ElementalCardUsed)
{
	m_ElementalCardUsed = ElementalCardUsed;
}

void Eter::Elemental::SetNameCard(const ElementalCardName nameCard)
{
	m_nameCard = nameCard;
}

void Eter::Elemental::SetUsername(const std::string username)
{
	m_username = username;
}
#pragma endregion Getters and Setters

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

void Eter::Elemental::Spark(Board& board, Player& player)
{
	auto& gameBoard = board.GetBoardReference();
	const auto& playerName = player.GetUserName();

	std::vector<std::pair<int, int>> coveredCardsPositions;

	// We stack in a vector the cards that are ours and under the opponent's card
	for (int row = 0; row <board.GetCurrentSize(); ++row) {
		for (int col = 0; col <board.GetCurrentSize(); ++col) {
			auto& tileOptional = gameBoard[row][col];
			if (tileOptional.has_value() && tileOptional->GetValue().size() > 1 && tileOptional.value().GetTopValue().GetUserName()!=player.GetUserName()) {
				auto stack = tileOptional->GetValue();
				for (size_t i = 0; i < stack.size() - 1; ++i) 
					if (stack[i].GetUserName() == playerName) {
						coveredCardsPositions.emplace_back(row,col);
						break;
					}
				
			}
		}
	}
	if (coveredCardsPositions.empty()) {
		std::cout << "No covered cards belonging to you were found.\n";
		return;
	}

	std::vector <Piece> cards;
	std::vector<std::pair<int, int>> sourcePositions;

	for (const auto& pos : coveredCardsPositions) {
		auto& tileOptional = gameBoard[pos.first][pos.second];
		auto stack = tileOptional->GetValue();
		for (size_t i = 0; i < stack.size() - 1; ++i)
			if (stack[i].GetUserName() == playerName) {
				cards.emplace_back(stack[i]);
				sourcePositions.emplace_back(pos.first, pos.second);
				std::cout << cards.size() << ": Card '" << stack[i].GetValue()
					<< "' at (" << pos.first << ", " << pos.second << ")\n";
			}
	}

	int option;
	std::cout << "Choose a card to move by entering the corresponding number: ";
	std::cin >> option;
	int row, col;
	std::cout << "Choose the row and the column you whant to place the card at.";
	std::cout << "Row: ";
	std::cin >> row;
	std::cout << "Column: ";
	std::cin >> col;

	if (option < 1 || option>static_cast<int>(cards.size())) {
		std::cout << "Invalid choice. Operation canceled.\n";
		return;
	}
	if (row < 0 || row >= board.GetCurrentSize() || col < 0 || col >= board.GetCurrentSize() || gameBoard[row][col].has_value()) {
		std::cout << "Invalid position. Card placement failed.\n";
		return;
	}
    auto& destTileOptional = board.GetBoardReference()[row][col];
	if (destTileOptional && destTileOptional->IsPit()) {
		std::cout << "The chosen position is a pit. Card placement failed.\n";
		return;
	}

	Piece chosenCard = cards[option-1];
	auto [sourceRow, sourceCol] = sourcePositions[option - 1];
	
	auto& sourceTile = gameBoard[sourceRow][sourceCol];
	auto& sourceStack = sourceTile->GetValueRef();
	auto it = std::find_if(sourceStack.begin(), sourceStack.end(),
		[&chosenCard](const Piece& piece) {
		return piece.GetValue() == chosenCard.GetValue();
	});

	if (it != sourceStack.end()) {
		sourceStack.erase(it);
	}

	if (sourceStack.empty()) {
		sourceTile.reset();
	}


	destTileOptional->SetValue(chosenCard);
	std::cout << "Card successfully placed at (" << row << ", " << col << ").\n";

}

void Eter::Elemental::shiftRowToLeft(Board& board, int index)
{
	auto& gameBoard = board.GetBoardReference();
	int size = board.GetCurrentSize();

	Player player1;
	Player player2;

	auto& firstTile = gameBoard[index][0];
	if (firstTile.has_value()) {
		auto& stack = firstTile->GetValueRef();
		for (auto& piece : stack) {
			if (piece.GetUserName() == player1.GetUserName())
				player1.AddPiece(piece);
			else
				player2.AddPiece(piece);
		}
		firstTile->RemoveStack(); 
	}

	for (int col = 0; col < size - 1; ++col) {
		//gameBoard[index][col] = gameBoard[index][col + 1];
	}

	gameBoard[index][size - 1].reset();
	std::cout << "Row successfully shifted to left.\n";
}

void Eter::Elemental::shiftRowToRight(Board& board, int index)
{
	auto& gameBoard = board.GetBoardReference();
	int size = board.GetCurrentSize();

	Player player1;
	Player player2;

	auto& lastTile = gameBoard[index][size - 1];
	if (lastTile.has_value()) {
		auto& stack = lastTile->GetValueRef();
		for (auto& piece : stack) {
			if (piece.GetUserName() == player1.GetUserName())
				player1.AddPiece(piece);
			else
				player2.AddPiece(piece);
		}
		lastTile->RemoveStack(); 
	}

	for (int col = size - 1; col > 0; --col) {
		//gameBoard[index][col] = gameBoard[index][col - 1];
	}

	gameBoard[index][0].reset();
	std::cout << "Row successfully shifted to right.\n";
}

void Eter::Elemental::shiftColUp(Board& board, int index)
{
	auto& gameBoard = board.GetBoardReference();
	int size = board.GetCurrentSize();
	Player player1, player2; 

	auto topTile = gameBoard[0][index];
	if (topTile.has_value()) {
		auto& stack = topTile->GetValueRef();
		for (auto& piece : stack) {
			if (piece.GetUserName() == player1.GetUserName())
				player1.AddPiece(piece); 
			else
				player2.AddPiece(piece); 
		}
	}

	for (int row = 1; row < size; ++row) {
		//gameBoard[row - 1][index] = gameBoard[row][index];
	}

	gameBoard[size - 1][index].reset();

}

void Eter::Elemental::shiftColDown(Board& board, int index)
{
	auto& gameBoard = board.GetBoardReference();
	int size = board.GetCurrentSize();
	Player player1, player2; 

	auto bottomTile = gameBoard[size - 1][index];
	if (bottomTile.has_value()) {
		auto& stack = bottomTile->GetValueRef();
		for (auto& piece : stack) {
			if (piece.GetUserName() == player1.GetUserName())
				player1.AddPiece(piece);  
			else
				player2.AddPiece(piece); 
		}
	}

	for (int row = size - 2; row >= 0; --row) {
		//gameBoard[row + 1][index] = gameBoard[row][index];
	}

	gameBoard[0][index].reset();
}

bool Eter::Elemental::isRowFull(const Board& board, int rowIndex)
{
    auto gameBoard = board.GetBoard();
	int size = board.GetCurrentSize();

	for (int col = 0; col < size; ++col) {
		if (!gameBoard[rowIndex][col].has_value()) {
			return false; 
		}
	}
	return true;
}

bool Eter::Elemental::isColumnFull(const Board& board, int colIndex)
{
    auto gameBoard = board.GetBoard();
	int size = board.GetCurrentSize();

	for (int row = 0; row < size; ++row) {
		if (!gameBoard[row][colIndex].has_value()) {
			return false; 
		}
	}
	return true;
}

const std::string Eter::Elemental::toSringElementalCardName(ElementalCardName nameCard)
{
	switch (nameCard) {
	case ElementalCardName::CONTROLLED_EXPLOSION:
		return "Controlled Explosion";
	case ElementalCardName::DESTRUCTION:
		return "Destruction";
	case ElementalCardName::FLAME:
		return "Flame";
	case ElementalCardName::FIRE:
		return "Fire";
	case ElementalCardName::ASH:
		return "Ash";
	case ElementalCardName::SPARK:
		return "Spark";
	case ElementalCardName::SQUALL:
		return "Squall";
	case ElementalCardName::GALE:
		return "Gale";
	case ElementalCardName::HURRICANE:
		return "Hurricane";
	case ElementalCardName::GUST:
		return "Gust";
	case ElementalCardName::MIRAGE:
		return "Mirage";
	case ElementalCardName::STORM:
		return "Storm";
	case ElementalCardName::TIDE:
		return "Tide";
	case ElementalCardName::MIST:
		return "Mist";
	case ElementalCardName::WAVE:
		return "Wave";
	case ElementalCardName::WHIRLPOOL:
		return "Whirlpool";
	case ElementalCardName::BLIZZARD:
		return "Blizzard";
	case ElementalCardName::WATERFALL:
		return "Waterfall";
	case ElementalCardName::SUPPORT:
		return "Support";
	case ElementalCardName::EARTHQUAKE:
		return "Earthquake";
	case ElementalCardName::CRUMBLE:
		return "Crumble";
	case ElementalCardName::BORDER:
		return "Border";
	case ElementalCardName::AVALANCHE:
		return "Avalanche";
	case ElementalCardName::ROCK:
		return "Rock";
	}
	

}

void Eter::Elemental::Hurricane(Board& board)
{
	std::cout << "What would you like to shift? (column or row)\n";
	std::string option;
	int src;
	std::cin >> option;
	
	if (option == "row")
	{
		std::cout << "Enter the positions of the full row you want to shift: \n";
		std::cin >> src;
		if (src < 0 || src >= board.GetCurrentSize() || !isRowFull(board,src)) {
			std::cout << "Invalid position or not a full row.\n";
			return;
		}

		std::cout << "Wold you like to shift the row to the left or to the right? (left/ right)\n";
		std::cin >> option;
		if (option == "right")
			shiftRowToRight(board, src);
		else if (option == "left")
			shiftRowToLeft(board, src);
		else
			std::cout << "Invalid option.";
		

	}
	else if (option == "col")
	{
		std::cout << "Enter the positions of the full column you want to shift: \n";
		std::cin >> src;
		if ( src < 0 || src >= board.GetCurrentSize() || !isColumnFull(board,src)) {
			std::cout << "Invalid position or not a full column.\n";
			return;
		}

		std::cout << "Wold you like to shift the column upwards or downwards? (up/ down)\n";
		std::cin >> option;
		if (option == "up")
			shiftColUp(board, src);
		else if (option == "down")
			shiftColDown(board, src);
		else
			std::cout << "Invalid option.";

	}
	else
		std::cout << "Invalid option.\n";

}

void Eter::Elemental::Gust(Board& board)
{
	auto& gameBoard = board.GetBoardReference();

	std::vector<std::pair<int, int>> cardsPositions;

	// We stack the single cards position in cardsPositions
	for (int row = 0; row < board.GetCurrentSize(); ++row) {
		for (int col = 0; col < board.GetCurrentSize(); ++col) {
			auto& tileOptional = gameBoard[row][col];
			if (tileOptional.has_value() && tileOptional->GetValue().size() ==1) {
				Piece card = tileOptional->GetTopValue();
				cardsPositions.emplace_back(row, col);
				std::cout << "Option " << cardsPositions.size() << ": " << card.GetValue() << " at row '" << row << "' and column '" << col << "'.\n";
			}
		}
	}

	if (cardsPositions.empty()) {
		std::cout << "No single cards placed on tiles were found.\n";
		return;
	}

	std::cout << "What card would you like to move? (select from the options)\n";
	int option;
	std::cin >> option;

	if (option < 1 || option>static_cast<int>(cardsPositions.size())) {
		std::cout << "Invalid choice. Operation canceled.\n";
		return;
	}

	auto [currentRow, currentCol] = cardsPositions[option - 1];

	std::cout << "In what direction would you like to move the card(right, left, up, down)? The card must have a higher value than the one already placed.\n";
	std::string move;
	std::cin >> move;

	int newRow = currentRow, newCol = currentCol;

	if (move == "right") {
		newCol++;
	}
	else if (move == "left") {
		newCol--;
	}
	else if (move == "up") {
		newRow--;
	}
	else if (move == "down") {
		newRow++;
	}
	else {
		std::cout << "Invalid direction. Operation canceled.\n";
		return;
	}

	if (newRow < 0 || newRow >= board.GetCurrentSize() || newCol < 0 || newCol >= board.GetCurrentSize()) {
		std::cout << "Invalid move. The card would move out of bounds. Operation canceled.\n";
		return;
	}

	auto& destTileOptional = gameBoard[newRow][newCol];

	if (destTileOptional.has_value()) {
		Piece destCard = destTileOptional->GetTopValue();
		Piece movingCard = gameBoard[currentRow][currentCol]->GetTopValue();

		if (destCard.GetValue() >= movingCard.GetValue()) {
			std::cout << "Invalid move. The destination card does not have a lower value. Operation canceled.\n";
			return;
		}
	}
	else {
		std::cout << "Invalid move. The destination must contain a card. Operation canceled.\n";
		return;
	}

	destTileOptional->SetValue(gameBoard[currentRow][currentCol]->GetTopValue());
	gameBoard[currentRow][currentCol].reset();

	std::cout << "Card successfully moved to (" << newRow << ", " << newCol << ").\n";

}

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


