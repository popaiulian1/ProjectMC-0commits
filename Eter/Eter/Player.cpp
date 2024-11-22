#include "Player.h"

//Constructors
Eter::Player::Player(const std::string& username, const int& score, const std::vector<Eter::Piece>& pieces, const bool& illusionPlayed):
	m_username{ username }, 
    m_score{ score }, 
    m_pieces{ pieces },
	m_illusionPlayed{ illusionPlayed }
{}

Eter::Player::Player()
{
	m_username = "";
	m_score = 0;
	m_illusionPlayed = false;
}

Eter::Player& Eter::Player::operator=(const Player& other)
{
    if (this != &other) {
		m_username = other.m_username;
		m_score = other.m_score;
		m_pieces = other.m_pieces;
		m_illusionPlayed = other.m_illusionPlayed;
    }
	return *this;
}


//Getters
const std::string& Eter::Player::GetUserName() const
{
    return m_username;
}

const int& Eter::Player::GetScore() const
{
	return m_score;
}

const std::vector<Eter::Piece>& Eter::Player::GetPieces() const
{
	return m_pieces;
}

const bool& Eter::Player::GetIllusionPlayed() const
{
    return m_illusionPlayed;
}

Eter::Piece Eter::Player::GetLastPlayedPiece() const
{
    return m_lastPlayedPiece;
}

//Setters
void Eter::Player::SetUserName(const std::string& username)
{
	m_username = username;
}

void Eter::Player::SetScore(const int& score)
{
	m_score = score;
}

void Eter::Player::SetPieces(const std::vector<Eter::Piece>& pieces)
{
	m_pieces = pieces;
}

void Eter::Player::SetIllusionPlayed(const bool& illusionPlayed)
{
	m_illusionPlayed = illusionPlayed;
}


//Methods
std::pair<int, int> Eter::Player::Play()
{
    int rowIndex, colIndex;

    std::cout << "Enter Row Index: ";
    std::cin >> rowIndex;
    std::cout << "Enter Column Index: ";
    std::cin >> colIndex;

    return { rowIndex, colIndex };
}

char Eter::Player::ChoosePiece()
{
    if (m_pieces.empty()) {
        throw std::runtime_error("No pieces left to choose!");
        return '\0';
    }

    std::cout << "\n<=====================================================================>\n";
    std::cout << "DECK :  \n| ";
	for (Piece piece : m_pieces)
    {
		std::cout << piece.GetValue() << " | ";
	}
    std::cout << std::endl << "INDEX : \n| ";
	for (int index = 0; index < m_pieces.size(); index++) {
        std::cout << index << " | ";
	}
    std::cout << "\n<=====================================================================>\n";

	std::cout << "Choose by index a piece to play: ";
    int inputIndex;
	std::cin >> inputIndex;
	char returnArgument = m_pieces[inputIndex].GetValue();
	m_lastPlayedPiece = m_pieces[inputIndex];
	m_pieces.erase(m_pieces.begin() + inputIndex);

	return returnArgument;
}

void Eter::Player::PrintPieces() const
{
    for (int index = 0; index < m_pieces.size(); index++) {
        std::cout << "| " << index + 1 << ". Piece Value: " << m_pieces[index].GetValue() << " |\n";
    }
}

void Eter::Player::AddPiece(const Eter::Piece& piece)
{
	Piece pieceCopy = piece;
	pieceCopy.SetIsPlaced(true);
	this->m_pieces.push_back(piece);
}

void Eter::Player::RemovePieces()
{
    this->m_pieces.clear();
}

bool Eter::Player::HasWon(const Board& board)
{
    auto gameBoard = board.GetBoard();
    size_t maxSize = board.GetMaxSize();
	int count = 0;

    // Lambda to check if the tile's top piece belongs to this player
    auto isTileOwnedByPlayer = [this](const std::optional<Tile>& tile) {
        return tile.has_value() && tile->GetTopValue().GetUserName() == this->GetUserName();
        };

    // Check for horizontal, vertical, and diagonal lines
    for (size_t i = 0; i < maxSize; i++) {
        for (size_t j = 0; j < maxSize; j++) {
            // Horizontal check
            if (!isTileOwnedByPlayer(gameBoard[i][j])) {
                count = 0;
            }
            else {
                count++;
            }
        }
        if(count == maxSize) return true;

		count != 0 ? count = 0 : count;
    }

    count = 0;

    for (size_t i = 0; i < maxSize; i++) {
        for (size_t j = 0; j < maxSize; j++) {
            // Vertical check
            if (!isTileOwnedByPlayer(gameBoard[j][i])) {
                count = 0;
            }
            else {
                count++;
            }
            if (count == maxSize) return true;

            count != 0 ? count = 0 : count;
        }
    }

    count = 0;

	for (size_t i = 0; i < maxSize; i++) {
		// Primary Diagonal check
        if (isTileOwnedByPlayer(gameBoard[i][i])) {
			count++;
		}
		if (count == maxSize) return true;

		count != 0 ? count = 0 : count;
	}

    count = 0;
    
	for (size_t i = 0; i < maxSize; i++) {
		// Secondary Diagonal check
        if (isTileOwnedByPlayer(gameBoard[i][maxSize - i - 1])) {
			count++;
		}
		if (count == maxSize) return true;
        
		count != 0 ? count = 0 : count;
	}

    return false;
}

std::ostream& Eter::operator<<(std::ostream& os, const Player& player)
{
    os << '\n' << player.GetUserName() << " -> info:\n-------------------------------\n";
    os << "Username: " << player.m_username << '\n';
    os << "Cards {";
    for (const Piece& piece : player.m_pieces) {
        os << piece.GetValue() << " ";
    }
    os << "}\n";
    os << "Score: " << player.m_score << "\n";
	os << "Illusion Played: " << player.m_illusionPlayed << "\n";

    return os;
}
