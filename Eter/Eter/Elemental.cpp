#include "Elemental.h"
#include <algorithm>
#include "Board.h"
#include "Tile.h"
#include <cmath>

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

const Eter::Board Eter::Elemental::GetBoardForElemental() const
{
	return m_board;
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
void Eter::Elemental::SetBoardForElemental(const Board& board)
{
	m_board = board;
}
#pragma endregion Getters and Setters

void Eter::Elemental::Tide(int row1, int column1, int row2, int column2) //Change positions of 2 different cards or stacks of cards.
{
	auto& GameBoard = m_board.GetBoardReference();

	//row1, column1 -> coordinates of the first tile
	//row2, column2 -> coordinates of the second tile
	if (row1 < 0 || row1 >= m_board.GetCurrentSize())
	{
		std::cout << "Invalid row index!\n";
	}
	else if (row2 < 0 || row2 >= m_board.GetCurrentSize())
	{
		std::cout << "Invalid row index!\n";
	}
	else if (column1 < 0 || column1 >= m_board.GetCurrentSize()) {
		std::cout << "Invalid row index!\n";
	}
	else if (column2 < 0 || column2 >= m_board.GetCurrentSize()) {
		std::cout << "Invalid row index!\n";
	}

	if (!GameBoard[row1][column1].has_value() || !GameBoard[row2][column2].has_value()) {
		std::cout << "Empty tile!";
		return;
	}

	if (!GameBoard[row1][column1].value().GetTopValue().GetEterCard() || !GameBoard[row2][column2].value().GetTopValue().GetEterCard()) {
		std::cout << "You cannot move the eter card!";
		return;
	}

	//swap between card / stack of cards.
	std::swap(GameBoard[row1][column1], GameBoard[row2][column2]);
}

void Eter::Elemental::Mist(Player& player)
{
	for (auto row : m_board.GetBoard()) {
		for (auto tile : row) {
			if (tile.has_value()) {
				if (tile.value().GetTopValue().GetIsIllusion()) {
					std::cout << "There an illusion on the board";
					return;
				}
			}
		}
	}
	player.SetIllusionPlayed(false);
}

void Eter::Elemental::Earthquake(Board& board)
{
	auto& GameBoard = board.GetBoardReference();
	for (auto& row : GameBoard)
	{
		for (auto& tile : row)
		{	
			if (tile.has_value()) {
				if (tile.value().IsPit())
					continue;
				Piece TopValue = tile.value().GetTopValue();
				if (TopValue.GetValue() == '1')
					if(!TopValue.GetEterCard())
						tile.value().GetValueRef().pop_back();
			}
		}
	}
}

//void Eter::Elemental::Avalanche(Board& board)
//{
//	int rowIndex1, columnIndex1, rowIndex2, columnIndex2;
//	while (!neighboringCardsStacs(rowIndex1, columnIndex1, rowIndex2, columnIndex2)) {
//
//		std::cout << "Choose by indices 2 neighboring cards/stacs\n\n";
//		std::cout << "First card/stack row index: ";
//		std::cin >> rowIndex1;
//		std::cout << "First card/stack column index: ";
//		std::cin >> columnIndex1;
//		std::cout << "Second card/stack row index: ";
//		std::cin >> rowIndex2;
//		std::cout << "Second card/stack column index: ";
//		std::cin >> columnIndex2;
//
//		if (neighboringCardsStacs(rowIndex1, columnIndex1, rowIndex2, columnIndex2) == false) {
//			std::cout << "Error: Non-neighboars Tiles!";
//		}
//	}
//
//	// Shift cards/stacs horizontally/vertically
//}

void Eter::Elemental::Rock(Board& board, Player& player, Player& opponent)
{
	auto& gameBoard = board.GetBoardReference();

	if (opponent.GetIllusionPlayed() == false) {
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

				char cardValue = player.ChoosePiece();
				targetTile.GetValueRef().push_back(Piece(cardValue, false, player.GetUserName(), false, false, false));
				break;
			}
		}
	}
}

void Eter::Elemental::Flame(Player& opponent, Board& board)
{
	bool illusionRevealed = false;
	auto& gameBoard = board.GetBoardReference();

	for (int row = 0; row < gameBoard.size(); ++row) {
		for (int col = 0; col < gameBoard[row].size(); ++col) {
			auto& tileOptional = gameBoard[row][col];

			// First we verify if the optional has any values
			if (tileOptional.has_value() && !tileOptional->GetValue().empty()) {
				Piece& topPiece = tileOptional.value().GetTopValueRef();
				if (topPiece.GetIsIllusion() && topPiece.GetUserName() == opponent.GetUserName()) {
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

	m_ElementalCardUsed = true;
}

void Eter::Elemental::Fire(Board& board, Player& player1, Player& player2)
{
	auto& gameBoard = board.GetBoardReference();
	std::unordered_map<char, int> cardCounts;

	// Counting the visible cards on the board
	for (int row = 0; row < board.GetCurrentSize(); ++row) {
		for (int col = 0; col < board.GetCurrentSize(); ++col) {
			auto& tileOptional = gameBoard[row][col];
			if (tileOptional.has_value() && !tileOptional->GetValue().empty()) {
				char topCardValue = tileOptional->GetTopValue().GetValue();
				if (!tileOptional->GetTopValue().GetEterCard())
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
				Piece& topPiece = tileOptional.value().GetTopValueRef();
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
						if (!tileOptional->GetTopValue().GetEterCard())
							tileOptional->GetValueRef().pop_back();
						else {
							std::cout << "Eter card is not removed\n";
						}
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

	std::vector<Piece> eliminatedPieces;
	for (auto& piece : playerPieces) {
		if (piece.GetIsEliminated()==true) {
			eliminatedPieces.push_back(piece);
		}
	}

	if (eliminatedPieces.empty()) {
		std::cout << "No eliminated cards available to play.\n";
		return;
	}

	std::cout << "Choose a card to place on the board:\n";
	for (size_t i = 0; i < eliminatedPieces.size(); ++i) {
		std::cout << i + 1 << ": '" << eliminatedPieces[i].GetValue() << "'\n";
	}

	std::cout << "Enter the option of the card you want to place.\n";
	std::cout << "Choice: ";
	int choice;
	std::cin >> choice;
	if (choice<0 || choice> eliminatedPieces.size())
	{
		std::cout << "Invalid option.\n";
		return;
	}

	Piece& chosenPiece = eliminatedPieces[choice - 1];

		std::cout << "Where yould you like to place your card(row, column)?\n";
		int row, col;
		std::cin >> row >> col;
		if (row < 0 || col < 0) {
			m_board.IncreaseBoardForNegativeIndexes({ row, col });
			gameBoard = m_board.GetBoardReference();
		}
		if (row >= (int)gameBoard.size() - 1 && gameBoard.size() < m_board.GetMaxSize()) {
			gameBoard.insert(gameBoard.end(), std::vector<std::optional<Tile>>(gameBoard[0].size()));
		}
		if (col >= (int)gameBoard[0].size() - 1 && gameBoard[0].size() < m_board.GetMaxSize()) {
			for (auto& r : gameBoard) {
				r.insert(r.end(), std::optional<Tile>());
			}
		}

		int adjustedLine = row, adjustedColumn = col;
		adjustedLine < 0 ? adjustedLine += 1 : adjustedLine;
		adjustedColumn < 0 ? adjustedColumn += 1 : adjustedColumn;

		if (adjustedLine >= gameBoard.size() || adjustedColumn >= gameBoard[0].size() ||
			adjustedLine < 0 || adjustedColumn < 0) {
			std::cout << "Invalid move->Tile position is out of bounds\n";
			return;
		}

		gameBoard[adjustedLine][adjustedColumn] = Tile(chosenPiece);

		chosenPiece.SetIsEliminated(false);
		chosenPiece.SetIsPlaced(true);

		std::cout << "Card '" << chosenPiece.GetValue() << "' placed at (" << adjustedLine << ", " << adjustedColumn << ").\n";
	
	
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
	std::cout << "Choose the row and the column you whant to place the card at.\n";
	std::cout << "Row: ";
	std::cin >> row;
	std::cout << "Column: ";
	std::cin >> col;
	std::cout << "\n";

	if (option < 1 || option>static_cast<int>(cards.size())) {
		std::cout << "Invalid choice. Operation canceled.\n";
		return;
	}

	//Validation rows and cols
	if (row < 0 || col < 0) {
		m_board.IncreaseBoardForNegativeIndexes({ row, col });
		gameBoard = m_board.GetBoardReference();
	}

	if (row >= (int)gameBoard.size() - 1 && gameBoard.size() < m_board.GetMaxSize()) {
		gameBoard.insert(gameBoard.end(), std::vector<std::optional<Tile>>(gameBoard[0].size()));
	}
	if (col >= (int)gameBoard[0].size() - 1 && gameBoard[0].size() < m_board.GetMaxSize()) {
		for (auto& r : gameBoard) {
			r.insert(r.end(), std::optional<Tile>());
		}
	}

	int adjustedLine = row, adjustedColumn = col;
	adjustedLine < 0 ? adjustedLine += 1 : adjustedLine;
	adjustedColumn < 0 ? adjustedColumn += 1 : adjustedColumn;

	if (adjustedLine >= gameBoard.size() || adjustedColumn >= gameBoard[0].size() ||
		adjustedLine < 0 || adjustedColumn < 0) {
		std::cout << "Invalid move->Tile position is out of bounds\n";
		return;
	}
    auto& destTileOptional = board.GetBoardReference()[adjustedLine][adjustedColumn];
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

	destTileOptional = Tile();
	destTileOptional->SetValue(chosenCard);
	std::cout << "Card successfully placed at (" << row << ", " << col << ").\n";

}

void Eter::Elemental::shiftRowToLeft(Board& board, int index, Player& player1, Player& player2)
{
	auto& gameBoard = board.GetBoardReference();
	int size = gameBoard[index].size();

	if (index < 0 || index >= size) {
		std::cout << "Invalid row index. Operation canceled.\n";
		return;
	}

	if (gameBoard[index][0].has_value()) {
		auto& firstTile = gameBoard[index][0];
		auto& stack = firstTile->GetValueRef();

		for (auto& piece : stack) {
			piece.SetIsEliminated(true);
			if (piece.GetUserName() == player1.GetUserName()) {
				player1.AddPiece(piece);
			}
			else if (piece.GetUserName() == player2.GetUserName()) {
				player2.AddPiece(piece);
			}
		}

		firstTile.reset(); 
	}

	for (int col = 1; col < size; ++col) {
		if (gameBoard[index][col].has_value()) {
            gameBoard[index][col - 1] = std::move(gameBoard[index][col]);
        } else {
            gameBoard[index][col - 1].reset();
        }

		
	}

	gameBoard[index][size - 1].reset();

	std::cout << "Row successfully shifted to the left.\n";
}



void Eter::Elemental::shiftRowToRight(Board& board, int index, Player& player1, Player& player2)
{
	auto& gameBoard = board.GetBoardReference();
	int size = gameBoard[index].size();

	if (index < 0 || index >= size) {
		std::cout << "Invalid row index. Operation canceled.\n";
		return;
	}

	auto& lastTile = gameBoard[index][size - 1];
	if (lastTile.has_value()) {
		auto& stack = lastTile->GetValueRef();
		for (auto& piece : stack) {
			if (piece.GetUserName() == player1.GetUserName())
				piece.SetIsEliminated(true), player1.AddPiece(piece);
			else
				piece.SetIsEliminated(true), player2.AddPiece(piece);
		}
		lastTile->RemoveStack(); 
	}

	for (int col = size - 1; col > 0; --col) {
		gameBoard[index][col] = gameBoard[index][col - 1];
	}

	gameBoard[index][0].reset();
	std::cout << "Row successfully shifted to right.\n";
}

void Eter::Elemental::shiftColUp(Board& board, int index, Player& player1, Player& player2)
{
	auto& gameBoard = board.GetBoardReference();
	int size = board.GetCurrentSize(); 

	auto topTile = gameBoard[0][index];
	if (topTile.has_value()) {
		auto& stack = topTile->GetValueRef();
		for (auto& piece : stack) {
			if (piece.GetUserName() == player1.GetUserName())
				piece.SetIsEliminated(true), player1.AddPiece(piece);
			else
				piece.SetIsEliminated(true), player2.AddPiece(piece);
		}
	}

	for (int row = 1; row < size; ++row) {
		gameBoard[row - 1][index] = gameBoard[row][index];
	}

	gameBoard[size - 1][index].reset();

}

void Eter::Elemental::shiftColDown(Board& board, int index, Player& player1, Player& player2)
{
	auto& gameBoard = board.GetBoardReference();
	int size = board.GetCurrentSize();

	auto bottomTile = gameBoard[size - 1][index];
	if (bottomTile.has_value()) {
		auto& stack = bottomTile->GetValueRef();
		for (auto& piece : stack) {
			piece.SetIsEliminated(true);
			if (piece.GetUserName() == player1.GetUserName())
				 player1.AddPiece(piece);
			else
				 player2.AddPiece(piece);
		}
	}

	for (int row = size - 2; row >= 0; --row) {
		gameBoard[row + 1][index] = gameBoard[row][index];
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

bool Eter::Elemental::neighboringCardsStacs(int rowIndex1, int colIndex1, int rowIndex2, int colIndex2)
{
	return (rowIndex1 == rowIndex2 && std::abs(colIndex1 - colIndex2) == 1) || 
		   (colIndex1 == colIndex2 && std::abs(rowIndex1 - rowIndex2) == 1);
}

const std::string Eter::Elemental::toSringElementalCardName(ElementalCardName nameCard) const
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

void Eter::Elemental::Hurricane(Board& board, Player& player1, Player& player2)
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
			shiftRowToRight(board, src,player1, player2);
		else if (option == "left")
			shiftRowToLeft(board, src, player1, player2);
		else
			std::cout << "Invalid option.";
		

	}
	else if (option == "column")
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
			shiftColUp(board, src,  player1,  player2);
		else if (option == "down")
			shiftColDown(board, src,  player1, player2);
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
	for (int row = 0; row < gameBoard.size(); ++row) {
		for (int col = 0; col < gameBoard[row].size(); ++col) {
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

	if (newRow < 0 || newCol < 0) {
		m_board.IncreaseBoardForNegativeIndexes({ newRow, newCol });
		gameBoard = m_board.GetBoardReference();
	}
	if (newRow >= (int)gameBoard.size() - 1 && gameBoard.size() < m_board.GetMaxSize()) {
		gameBoard.insert(gameBoard.end(), std::vector<std::optional<Tile>>(gameBoard[0].size()));
	}
	if (newCol >= (int)gameBoard[0].size() - 1 && gameBoard[0].size() < m_board.GetMaxSize()) {
		for (auto& r : gameBoard) {
			r.insert(r.end(), std::optional<Tile>());
		}
	}

	int adjustedLine = newRow, adjustedColumn = newCol;
	adjustedLine < 0 ? adjustedLine += 1 : adjustedLine;
	adjustedColumn < 0 ? adjustedColumn += 1 : adjustedColumn;

	if (adjustedLine >= gameBoard.size() || adjustedColumn >= gameBoard[0].size() ||
		adjustedLine < 0 || adjustedColumn < 0) {
		std::cout << "Invalid move->Tile position is out of bounds\n";
		return;
	}

	auto& destTileOptional = gameBoard[adjustedLine][adjustedColumn];

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

	std::cout << "Card successfully moved to (" << adjustedLine << ", " << adjustedColumn << ").\n";

}

void Eter::Elemental::Mirage(Board& board, Player& player) {
	Piece illusionCard;
	bool foundIllusion = false;
	int illusionRow = -1, illusionCol = -1;
	auto& gameBoard = board.GetBoardReference();

	// Găsim cartea de iluzie pe tablă
	for (int row = 0; row < gameBoard.size(); ++row) {
		for (int col = 0; col < gameBoard[row].size(); ++col) {
			auto& tileOptional = gameBoard[row][col];
			if (tileOptional.has_value()) {
				auto& stack = tileOptional->GetValueRef();
				if (!stack.empty() && stack.back().GetUserName() == player.GetUserName() && stack.back().GetIsIllusion()) {
					// Salvăm iluzia și o eliminăm de pe tablă
					illusionCard = stack.back();
					stack.pop_back();
					foundIllusion = true;
					illusionRow = row;
					illusionCol = col;
					break;
				}
			}
		}
		if (foundIllusion) break;
	}

	if (!foundIllusion) {
		std::cout << "No Illusion card found for the player on the board.\n";
		return;
	}

	std::cout << "Illusion card found at row " << illusionRow << ", column " << illusionCol << ".\n";

	// Alegem o nouă carte din mână
	std::cout << "Choose a card from your hand to replace the Illusion:\n";
	player.PrintPieces();

	int choice;
	std::cin >> choice;

	auto& hand = player.GetPiecesReference();

	if (choice < 1 || choice > static_cast<int>(hand.size())) {
		std::cout << "Invalid choice. Operation canceled.\n";
		// Reintroducem iluzia în mână, dacă utilizatorul a anulat operațiunea
		player.AddPiece(illusionCard);
		return;
	}

	// Alegem cartea dorită și o configurăm ca iluzie
	Piece chosenCard = hand[choice - 1];
	chosenCard.SetIsIllusion(true);
	chosenCard.SetIsPlaced(true);
	chosenCard.SetUserName(player.GetUserName());

	// Eliminăm cartea selectată din mână și reintroducem iluzia
	hand.erase(hand.begin() + (choice - 1));
	player.AddPiece(illusionCard);

	player.SetIllusionPlayed(false);
	// Plasăm noua iluzie pe tablă
	auto& destinationTile = gameBoard[illusionRow][illusionCol];
	if (!destinationTile.has_value()) {
		destinationTile.emplace();
	}
	destinationTile->SetValue(chosenCard);
	player.SetIllusionPlayed(true);

	std::cout << "Illusion replaced successfully! New card placed at (" << illusionRow << ", " << illusionCol << ").\n";
}



void Eter::Elemental::Wave(Board& board, Player& player)
{
	auto& gameBoard = board.GetBoardReference();
	std::cout << "Select the position of the card/stack you want to move to a free adiacent tile.(row,column)\n";
	int srcRow, srcCol;
	std::cin >> srcRow >> srcCol;
	if (srcRow<0 || srcRow>board.GetCurrentSize() || srcCol<0 || srcCol>board.GetCurrentSize()) {
		std::cout << "Invalid position.\n";
		return;
	}

	auto& srcTile = gameBoard[srcRow][srcCol];
	if (!srcTile.has_value()) {
		std::cout << "No card/stack found at the selected position.\n";
		return;
	}

	if (srcTile.value().GetTopValue().GetEterCard()) {
		std::cout << "You cannot move the Eter card.\n";
		return;
	}

	std::cout << "In what direction would you like to move the card/stack (right, left, up, down, up-left, up-right, down-left, down-right)? The card must have a higher value than the one already placed.\n";
	std::string move;
	std::cin >> move;

	int newRow = srcRow, newCol = srcCol;

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
	else if(move=="up-left"){
		newRow--;
		newCol--;
	}
	else if (move == "up-right"){
		newRow--;
		newCol++;
	}
	else if (move == "down-left") {
		newRow++;
		newCol--;
	}
	else if (move == "down-right") {
		newRow++;
		newCol++;
	}
	else {
		std::cout << "Invalid direction. Operation canceled.\n";
		return;
	}

	if (newRow < 0 || newRow >= board.GetCurrentSize() || newCol < 0 || newCol >= board.GetCurrentSize() || gameBoard[newRow][newCol].has_value()) {
		std::cout << "Invalid move. The card would move out of bounds or the destination tile is not empty. Operation canceled.\n";
		return;
	}

	//Moving the card/stack
	gameBoard[newRow][newCol] = srcTile; 
	srcTile.reset(); 
	std::cout << "Card/stack moved to (" << newRow << ", " << newCol << ").\n";

	//Placing a new card to the now empty space
	std::cout << "Choose a card from your hand to play on the now empty space at (" << srcRow << ", " << srcCol << "):\n";
	player.PrintPieces();

	int choice;
	std::cin >> choice;

	auto& hand = player.GetPiecesReference();
	if (choice < 1 || choice > static_cast<int>(hand.size())) {
		std::cout << "Invalid choice. Operation canceled.\n";
		return;
	}
	Piece chosenCard = hand[choice - 1];
	chosenCard.SetIsPlaced(true);
	hand.erase(hand.begin() + (choice - 1));

	gameBoard[srcRow][srcCol] = Tile(chosenCard);
	std::cout << "Card from your hand placed successfully on (" << srcRow << ", " << srcCol << ").\n";
}

void Eter::Elemental::Whirlpool(Board& board) {
	auto& gameBoard = board.GetBoardReference();

	std::cout << "What tile would you like to fill? Tile must be empty and have cards at positions up and down, or left and right. Enter row and column:\n";
	int row, col;
	std::cin >> row >> col;

	if (row < 0 || row >= board.GetCurrentSize() || col < 0 || col >= board.GetCurrentSize() || gameBoard[row][col].has_value()) {
		std::cout << "Invalid position or the tile is not empty.\n";
		return;
	}

	std::cout << "Do you want to use adjacent positions on the same row (horizontal) or the same column (vertical)? Enter 'row' or 'column':\n";
	std::string choice;
	std::cin >> choice;

	Piece* card1 = nullptr;
	Piece* card2 = nullptr;
	int adjRow1 = -1, adjCol1 = -1, adjRow2 = -1, adjCol2 = -1;

	//Validating options
	if (choice == "row") {
		if (col > 0 && gameBoard[row][col - 1].has_value() && !gameBoard[row][col - 1]->GetValueRef().empty()) {
			card1 = &gameBoard[row][col - 1]->GetValueRef().back();
			adjRow1 = row;
			adjCol1 = col - 1;

			if (card1->GetEterCard()) {
				std::cout << "You cannot move the Eter card.\n";
				return;
			}
		}
		if (col < board.GetCurrentSize() - 1 && gameBoard[row][col + 1].has_value() && !gameBoard[row][col + 1]->GetValueRef().empty()) {
			card2 = &gameBoard[row][col + 1]->GetValueRef().back();
			adjRow2 = row;
			adjCol2 = col + 1;

			if (card2->GetEterCard()) {
				std::cout << "You cannot move the Eter card.\n";
				return;
			}
		}
	}
	else if (choice == "column") {
		if (row > 0 && gameBoard[row - 1][col].has_value() && !gameBoard[row - 1][col]->GetValueRef().empty()) {
			card1 = &gameBoard[row - 1][col]->GetValueRef().back();
			adjRow1 = row - 1;
			adjCol1 = col;
		}
		if (row < board.GetCurrentSize() - 1 && gameBoard[row + 1][col].has_value() && !gameBoard[row + 1][col]->GetValueRef().empty()) {
			card2 = &gameBoard[row + 1][col]->GetValueRef().back();
			adjRow2 = row + 1;
			adjCol2 = col;
		}
	}
	else {
		std::cout << "Invalid choice. Operation canceled.\n";
		return;
	}

	if (!card1 || !card2) {
		std::cout << "There are not two cards in a straight line adjacent to the target tile.\n";
		return;
	}

	//Comparing the cards
	Piece* topCard = nullptr;
	Piece* bottomCard = nullptr;

	if (card1->GetValue() > card2->GetValue()) {
		topCard = card1;
		bottomCard = card2;
	}
	else if (card1->GetValue() < card2->GetValue()) {
		topCard = card2;
		bottomCard = card1;
	}
	else {
		std::cout << "The cards have equal values (" << card1->GetValue() << "). Which card should be on top? (1 for first, 2 for second):\n";
		std::cout << "Card 1: owner is " << card1->GetUserName() << "\n";
		std::cout << "Card 2: owner is " << card2->GetUserName() << "\n";
		int cardChoice;
		std::cin >> cardChoice;
		if (cardChoice == 1) {
			topCard = card1;
			bottomCard = card2;
		}
		else {
			topCard = card2;
			bottomCard = card1;
		}
	}

	//Placing the cards
	auto& stack1 = gameBoard[adjRow1][adjCol1]->GetValueRef();
	stack1.pop_back();
	if (stack1.empty()) gameBoard[adjRow1][adjCol1] = Tile();

	auto& stack2 = gameBoard[adjRow2][adjCol2]->GetValueRef();
	stack2.pop_back();
	if (stack2.empty()) gameBoard[adjRow2][adjCol2] = Tile();

	auto& destStack = gameBoard[row][col]->GetValueRef();
	destStack.push_back(*bottomCard);
	destStack.push_back(*topCard);

	std::cout << "Whirlpool executed successfully. Cards moved to (" << row << ", " << col << ").\n";
}

void Eter::Elemental::Blizzard(Board& board)
{
	auto gameBoard = board.GetBoardReference();

	std::string input = "";
	std::cout << "Choose between 'row' and 'column': ";
	std::cin >> input;

	enum rowOrColumn
	{
		row,
		column
	};

	rowOrColumn choice;
	if (input == "row") {
		choice = rowOrColumn::row;
	}
	else if (input == "column") {
		choice = rowOrColumn::column;
	}

	switch (choice)
	{
	case rowOrColumn::row: {
		std::cout << "What row would you like to block?\n";
		int srcRow;
		std::cin >> srcRow;

		int freeSpaces = 0;
		for (int row = 0; row < gameBoard.size(); ++row)
			for (int column = 0; column < gameBoard[row].size(); ++column)
				if(row != srcRow)
					if (!gameBoard[row][column].has_value())
						++freeSpaces;

		if (freeSpaces == 0) {
			std::cout << "There are no free spaces to move the cards to.\n";
			return;
		}

		for (int row = 0; row < gameBoard.size(); ++row)
			for (int column = 0; column < gameBoard[row].size(); ++column)
				if (row == srcRow)
					if (!gameBoard[row][column].has_value()) {
						gameBoard[row][column] = Tile();
						//gameBoard[row][column].value().SetTileBlocked(true);
					}
		break;
	}
	case rowOrColumn::column :
		//TO DO: opponent can't play cards on the column
		break;
	}

	bool freeTile = false;
	for (auto& row : gameBoard) {
		for (auto& tile : row) {
			//TO DO: if not the blocked row or column
			if (tile.value().GetTopValue().GetValue() != NULL)
				freeTile = true;
		}
	}
}

void Eter::Elemental::Waterfall(Board& board)
{
	auto& gameBoard = board.GetBoardReference();
	std::cout << "Choose the column you want to apply the power to (column index). Keep in mind the column must have at leat 3 positions occupied.\n";
	int col;
	std::cin >> col;
	if (col<0 || col> board.GetCurrentSize())
	{
		std::cout << "Position invalid.\n";;
		return;
	}

	//Verify there are at least 3 positions occupied
	int occupied = 0;
	for (int row = 0; row < board.GetCurrentSize(); ++row)
		if (gameBoard[row][col].has_value()) {
			if (gameBoard[row][col].value().GetTopValue().GetEterCard()) {
				std::cout << "You cannot move the Eter card.\n";
				return;
			}
			if (!gameBoard[row][col].value().GetTopValue().GetIsIllusion()) {
				std::cout << "The card is an illusion card and cannot be affected.\n";
				return;
			}
			occupied++;
		}
			
	if (occupied <3)
	{
		std::cout << "Condition of at least 3 positions of the column to be occupied is not valid.\n";
		return;
	}

	// Find the bottom-most occupied tile
	int bottomRow = -1;
	for (int row = board.GetCurrentSize() - 1; row >= 0; --row) {
		if (gameBoard[row][col].has_value()) {
			bottomRow = row;
			break;
		}
	}

	// Combine all stacks into the bottom-most stack
	auto& bottomTile = gameBoard[bottomRow][col];
	auto& bottomStack = bottomTile->GetValueRef();

	for (int row = bottomRow - 1; row >= 0; --row) {
		auto& currentTile = gameBoard[row][col];
		if (currentTile.has_value()) {
			auto& currentStack = currentTile->GetValueRef();
			bottomStack.insert(bottomStack.end(), currentStack.begin(), currentStack.end()); // Add current stack to bottom stack
			currentTile.reset(); // Clear the current tile
		}
	}

	std::cout << "Waterfall power applied successfully! Cards in column " << col << " have been merged into stacks moving downward.\n";
}

void Eter::Elemental::Support(Player& player)
{
	auto& hand = player.GetPiecesReference(); 

	std::vector<int> eligibleIndexes;
	for (size_t i = 0; i < hand.size(); ++i) {
		if (hand[i].GetValue() < 4) {
			eligibleIndexes.push_back(i);
		}
	}

	if (eligibleIndexes.empty()) {
		std::cout << "No eligible cards in deck to increase their value (all are 4).\n";
		return;
	}

	std::cout << "Choose a card to increase its value (+1):\n";
	for (size_t i = 0; i < eligibleIndexes.size(); ++i) {
		int index = eligibleIndexes[i];
		std::cout << i + 1 << ". Piece Value: " << hand[index].GetValue() << "\n";
	}

	int choice;
	std::cin >> choice;

	if (choice < 1 || choice > static_cast<int>(eligibleIndexes.size())) {
		std::cout << "Invalid choice. Operation canceled.\n";
		return;
	}

	int chosenIndex = eligibleIndexes[choice - 1];
	Piece& chosenPiece = hand[chosenIndex];
	chosenPiece.SetValue(chosenPiece.GetValue() + 1);

	std::cout << "Card value increased successfully! New value: " << chosenPiece.GetValue() << "\n";
}


//void Eter::Elemental::ControlledExplosion()
//{
//	// cause a power explosion
//}

void Eter::Elemental::Destruction(const Player& opponent, Board& board) 
{
	auto& GameBoard = board.GetBoardReference();

	size_t lastRow = board.GetLastMove().m_row;
	size_t lastCol = board.GetLastMove().m_column;

	auto& tile = GameBoard[lastRow][lastCol];
	if (tile.has_value()) {
		Tile& currentTile = tile.value();
		if (currentTile.GetTopValue().GetUserName() == opponent.GetUserName()) {
			if (currentTile.GetTopValue().GetEterCard()) {
				std::cout << "You cannot remove an eter card!\n";
				return;
			}

			currentTile.GetValueRef().pop_back();

			if (currentTile.GetValue().empty())
				tile.reset();

			std::cout << "Successfully removed opponent's last piece.\n";
			return;
		}
	}
	std::cout << "Could not find opponent's last piece to destroy.\n";
}

void Eter::Elemental::Squall(Player& opponent, Board& board) {
	auto& gameBoard = board.GetBoardReference();
	std::vector<std::pair<int, int>> opponentTilePositions;

	for (int row = 0; row < gameBoard.size(); ++row) {
		for (int col = 0; col < gameBoard[row].size(); ++col) {
			if (gameBoard[row][col].has_value() &&
				gameBoard[row][col]->GetTopValue().GetUserName() == opponent.GetUserName()) {
				opponentTilePositions.emplace_back(row, col);
			}
		}
	}
	if (opponentTilePositions.empty()) {
		std::cout << "No visible cards of the opponent found on the playing field.\n";
		return;
	}

	std::cout << "Choose a card to return to the opponent's hand from the following positions:\n";
	for (size_t i = 0; i < opponentTilePositions.size(); ++i) {
		int row = opponentTilePositions[i].first;
		int col = opponentTilePositions[i].second;
		std::cout << i + 1 << ". Position (" << row << ", " << col << ") - Card: "
			<< gameBoard[row][col]->GetTopValue().GetUserName() << "\n";
	}

	std::cout << "Enter the number of the card to return: ";
	int choice;
	std::cin >> choice;

	if (choice < 1 || choice > static_cast<int>(opponentTilePositions.size())) {
		std::cout << "Invalid choice. Operation canceled.\n";
		return;
	}

	int chosenRow = opponentTilePositions[choice - 1].first;
	int chosenCol = opponentTilePositions[choice - 1].second;
	auto& selectedTile = gameBoard[chosenRow][chosenCol];
	auto& stack = selectedTile->GetValueRef();

	Piece removedPiece(stack.back());
    removedPiece.SetIsEliminated(true);
	opponent.AddPiece(removedPiece);
	

	stack.pop_back();

	if (stack.empty()) {
		gameBoard[chosenRow][chosenCol] = std::nullopt;
	}

	std::cout << "Card from position (" << chosenRow << ", " << chosenCol
		<< ") successfully returned to the opponent's hand.\n";
}

void Eter::Elemental::Gale(Board& board, Player& player1, Player& player2)
{
	auto& gameBoard = board.GetBoardReference();

	for (auto& row : gameBoard) {
		for (auto& tile : row) {
			if (tile.has_value()) {
				auto& currentTile = tile.value();
				auto& stack = currentTile.GetValueRef();

				if (stack.size() > 1) {
					Piece topPiece = stack.back();
					stack.pop_back();
					//returning the other pieces to their owner
					while (!stack.empty()) {
						Piece currentPiece = stack.back();
						stack.pop_back();

						currentPiece.SetIsEliminated(true);
						
						if (currentPiece.GetUserName() == player1.GetUserName()) {
							player1.AddPiece(currentPiece);
						}
						else if (currentPiece.GetUserName() == player2.GetUserName()) {
							player2.AddPiece(currentPiece);
						}
					}
					currentTile.RemoveStack();
					currentTile.SetValue(topPiece);
				}
			}
		}
	}

}

void Eter::Elemental::Storm(Board& board) //Remove from play any stack of minimum 2 cards
{
	auto& gameBoard = board.GetBoardReference();
	std::vector<std::pair<int, int>> eligibleTiles;

	for (int row = 0; row < gameBoard.size(); ++row) {
		for (int col = 0; col < gameBoard[row].size(); ++col) {
			auto& tileOptional = gameBoard[row][col];
			if (tileOptional.has_value()) {
				auto& stack = tileOptional->GetValueRef();
				if (stack.size() >= 2) {
					eligibleTiles.emplace_back(row, col);
					std::cout << "Option " << eligibleTiles.size() << ": Stack at row "
						<< row << ", column " << col << " with " << stack.size() << " cards.\n";
				}
			}
		}
	}

	if (eligibleTiles.empty()) {
		std::cout << "No eligible stacks found. Operation canceled.\n";
		return;
	}

	int choice;
	std::cout << "Choose a stack to remove (enter the option number): ";
	std::cin >> choice;

	if (choice < 1 || choice > static_cast<int>(eligibleTiles.size())) {
		std::cout << "Invalid choice. Operation canceled.\n";
		return;
	}

	auto [row, col] = eligibleTiles[choice - 1];
	auto& selectedTile = gameBoard[row][col];

	selectedTile.reset();

}

void Eter::to_json(nlohmann::json& j, const Elemental& elemental)
{
	//there was a problem with the json library, 
	// it was not able to serialize the enum type so i have to do this ugly workaround"

	j = nlohmann::json{ 
		{"ElementalCardUsed", elemental.GetElementalCardUsed()},
		{"nameCard", elemental.toSringElementalCardName(elemental.GetNameCard())},
		{"username", elemental.GetUsername()} 
	};
}

void Eter::from_json(const nlohmann::json& j, Elemental& e)
{
	std::string nameCard = j.at("nameCard");
	Eter::ElementalCardName cardName;
	if (nameCard == "Controlled Explosion")
		cardName = Eter::ElementalCardName::CONTROLLED_EXPLOSION;
	else if (nameCard == "Destruction")
		cardName = Eter::ElementalCardName::DESTRUCTION;
	else if (nameCard == "Flame")
		cardName = Eter::ElementalCardName::FLAME;
	else if (nameCard == "Fire")
		cardName = Eter::ElementalCardName::FIRE;
	else if (nameCard == "Ash")
		cardName = Eter::ElementalCardName::ASH;
	else if (nameCard == "Spark")
		cardName = Eter::ElementalCardName::SPARK;
	else if (nameCard == "Squall")
		cardName = Eter::ElementalCardName::SQUALL;
	else if (nameCard == "Gale")
		cardName = Eter::ElementalCardName::GALE;
	else if (nameCard == "Hurricane")
		cardName = Eter::ElementalCardName::HURRICANE;
	else if (nameCard == "Gust")
		cardName = Eter::ElementalCardName::GUST;
	else if (nameCard == "Mirage")
		cardName = Eter::ElementalCardName::MIRAGE;
	else if (nameCard == "Storm")
		cardName = Eter::ElementalCardName::STORM;
	else if (nameCard == "Tide")
		cardName = Eter::ElementalCardName::TIDE;
	else if (nameCard == "Mist")
		cardName = Eter::ElementalCardName::MIST;
	else if (nameCard == "Wave")
		cardName = Eter::ElementalCardName::WAVE;
	else if (nameCard == "Whirlpool")
		cardName = Eter::ElementalCardName::WHIRLPOOL;
	else if (nameCard == "Blizzard")
		cardName = Eter::ElementalCardName::BLIZZARD;
	else if (nameCard == "Waterfall")
		cardName = Eter::ElementalCardName::WATERFALL;
	else if (nameCard == "Support")
		cardName = Eter::ElementalCardName::SUPPORT;
	else if (nameCard == "Earthquake")
		cardName = Eter::ElementalCardName::EARTHQUAKE;
	else if (nameCard == "Crumble")
		cardName = Eter::ElementalCardName::CRUMBLE;
	else if (nameCard == "Border")
		cardName = Eter::ElementalCardName::BORDER;
	else if (nameCard == "Avalanche")
		cardName = Eter::ElementalCardName::AVALANCHE;
	else if (nameCard == "Rock")
		cardName = Eter::ElementalCardName::ROCK;

	e.SetElementalCardUsed(j.at("ElementalCardUsed"));
	e.SetNameCard(cardName);
	e.SetUsername(j.at("username"));
}
