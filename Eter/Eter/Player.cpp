#include "Player.h"


Eter::Player::Player(const std::string& username, const int& score, const std::vector<Eter::Piece>& pieces, const bool& illusionPlayed):
	m_username{ username }, 
    m_score{ score }, 
    m_pieces{ pieces },
	m_illusionPlayed{ illusionPlayed }
{}

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

void Eter::Player::PrintPieces(const std::vector<Piece>& pieces) const
{
    for (const auto& piece: pieces) 
		std::cout << "Piece " << piece.GetValue() << " " << piece.GetUserName() << "\n";
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

	for (size_t i = 0; i < maxSize; i++) {
		// Primary Diagonal check
        if (isTileOwnedByPlayer(gameBoard[i][i])) {
			count++;
		}
		if (count == maxSize) return true;

		count != 0 ? count = 0 : count;
	}
    
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
    os << player.GetUserName() << " data:\n-------------------------------\n";
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
