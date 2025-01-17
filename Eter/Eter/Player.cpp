#include "Player.h"


//Constructors

Eter::Player::Player(const std::string& username, const std::vector<Eter::Piece>& pieces, const int& score, const size_t& gamesWon, const Piece& lastPlayedPiece, const bool& illusionPlayed, const bool& powerExplosionAccess, const bool& eterCardPlayed)
 :  m_username{username},
    m_pieces{pieces},
    m_score{score},
    m_gamesWon{gamesWon},
    m_lastPlayedPiece{lastPlayedPiece},
    m_illusionPlayed{illusionPlayed},
    m_powerExplosionAccess{powerExplosionAccess},
    m_eterCardPlayed{eterCardPlayed}
{}


//Rule Of Five
Eter::Player& Eter::Player::operator=(const Player& other)
{
    if (this != &other) {
        m_username = other.m_username;
        m_score = other.m_score;
        m_pieces = other.m_pieces;
        m_lastPlayedPiece = other.m_lastPlayedPiece;
        m_illusionPlayed = other.m_illusionPlayed;
        m_gamesWon = other.m_gamesWon;
        m_eterCardPlayed = other.m_eterCardPlayed;
		m_powerExplosionAccess = other.m_powerExplosionAccess;
    }
	return *this;
}
Eter::Player::Player(Player&& other) noexcept
{
    this->swap(other);
}
Eter::Player& Eter::Player::operator=(Player&& other) noexcept
{
    this->swap(other);
    return *this;
}
void Eter::Player::swap(Player& other) noexcept
{
    this->m_username = other.m_username;
    this->m_score = other.m_score;
    this->m_pieces = other.m_pieces;
    this->m_lastPlayedPiece = other.m_lastPlayedPiece;
    this->m_illusionPlayed = other.m_illusionPlayed;
    this->m_gamesWon = other.m_gamesWon;
    //this->m_powerExplosionAccess = other.m_powerExplosionAccess;
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
std::vector<Eter::Piece>& Eter::Player::GetPiecesReference()
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
const bool& Eter::Player::GetPowerExplosionAccess() const
{
    return m_powerExplosionAccess;
}
size_t Eter::Player::GetGamesWon() const
{
	return m_gamesWon;
}
bool Eter::Player::GetEterCardPlayed() const
{
	return m_eterCardPlayed;
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
void Eter::Player::SetPowerExplosionAccess(const bool& powerExplosionAccess)
{
    m_powerExplosionAccess = powerExplosionAccess;
}
void Eter::Player::SetGamesWon(const size_t& gamesWon)
{
	m_gamesWon = gamesWon;
}
void Eter::Player::SetEterCardPlayed(const bool& eterCardPlayed)
{
	m_eterCardPlayed = eterCardPlayed;
}


//Methods
std::pair<int, int> Eter::Player::Play(bool& firstMove)
{
    if (firstMove) {
        firstMove = false;
        return { 0, 0 };
    }

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
        if(piece.GetEterCard() == true)
			std::cout << "E | ";
        else
		    std::cout << piece.GetValue() << " | ";
	}

    std::cout << std::endl << "INDEX : \n| ";
    for (size_t index = 0; index < m_pieces.size(); ++index) {
        if (m_pieces[index].GetEterCard()) {
            std::cout << "X | "; // Mark the special card as unselectable
        }
        else {
            std::cout << index << " | ";
        }
    }
    std::cout << "\n<=====================================================================>\n";
    
    int inputIndex;
    while (true) {
        std::cout << "Choose by index a piece to play: ";
        std::cin >> inputIndex;

        // Validate the chosen index
        if (inputIndex < 0 || inputIndex >= static_cast<int>(m_pieces.size())) {
            std::cout << "Invalid index. Try again.\n";
        }
        else if (m_pieces[inputIndex].GetEterCard()) {
            std::cout << "Special card cannot be played now. Choose a different card.\n";
        }
        else {
            break; // Valid non-special card chosen
        }
    }

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

    if (gameBoard[0].size() == maxSize) {
        for (size_t i = 0; i < gameBoard.size(); i++) {
            for (size_t j = 0; j < maxSize; j++) {
                // Horizontal check
				if (gameBoard[i][j].has_value() && gameBoard[i][j].value().IsPit())
					return false;

                if (!isTileOwnedByPlayer(gameBoard[i][j])) {
                    count = 0;
                }
                else {
                    count++;
                }
            }
            if (count == maxSize) return true;

            count != 0 ? count = 0 : count;
        }
    }

    if (gameBoard.size() == maxSize) {
        for (size_t i = 0; i < gameBoard[0].size(); i++) {
            for (size_t j = 0; j < maxSize; j++) {
                // Vertical check
                if (gameBoard[j][i].has_value() && gameBoard[j][i].value().IsPit())
                    return false;

                if (!isTileOwnedByPlayer(gameBoard[j][i])) {
                    count = 0;
                }
                else {
                    count++;
                }
            }
            if (count == maxSize) return true;

            count != 0 ? count = 0 : count;
        }
    }
 
    if (gameBoard.size() != gameBoard[0].size()) {
        return false;
    }

	for (size_t i = 0; i < gameBoard.size(); i++) {
		// Primary Diagonal check
        if (isTileOwnedByPlayer(gameBoard[i][i])) {
			count++;
		}
		if (count == maxSize) return true;
	}

    count = 0;
    
    for (size_t i = 0; i < gameBoard.size(); i++) {
        // Secondary Diagonal check
        if (isTileOwnedByPlayer(gameBoard[i][maxSize - i - 1])) {
            count++;
        }
        if (count == maxSize) return true;
    }

	return false;
}

void Eter::Player::ResetPlayer()
{
    m_score = 0;
    m_pieces.clear();
    m_lastPlayedPiece = Piece();
    m_illusionPlayed = false;
    m_eterCardPlayed = false;

    std::cout << "Player " << m_username << "has been reset for new game!";
}

void Eter::Player::IncrementGamesWon()
{
    ++m_gamesWon;
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

void Eter::to_json(nlohmann::json& j, const Player& p)
{
    j = nlohmann::json{
        {"username", p.GetUserName()},
        {"score", p.GetScore()},
        {"gamesWon", p.GetGamesWon()},
        {"lastPlayedPiece", p.GetLastPlayedPiece()},
        {"illusionPlayed", p.GetIllusionPlayed()},
        {"powerExplosionAccess", p.GetPowerExplosionAccess()},
        {"eterCardPlayed", p.GetEterCardPlayed()}
    };

	nlohmann::json j_pieces = nlohmann::json::array();

	for (auto& piece : p.GetPieces())
	{
		j_pieces.emplace_back(piece);
	}

	j["pieces"] = j_pieces;
}

void Eter::from_json(const nlohmann::json& j, Player& p)
{
	p.SetUserName(j.at("username").get<std::string>());
	p.SetScore(j.at("score").get<int>());
	p.SetGamesWon(j.at("gamesWon").get<size_t>());
	p.SetIllusionPlayed(j.at("illusionPlayed").get<bool>());
	p.SetPowerExplosionAccess(j.at("powerExplosionAccess").get<bool>());
	p.SetEterCardPlayed(j.at("eterCardPlayed").get<bool>());

	std::vector<Piece> pieces;
	for (const auto& piece : j.at("pieces")) {
		pieces.push_back(piece.get<Piece>());
	}

	p.SetPieces(pieces);
}
