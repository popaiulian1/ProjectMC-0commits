#include "Player.h"
#include "Piece.h"
#include "Board.h"
#include "Tile.h"
#include "Game.h"
#include <iostream>

Eter::Player::Player()
{
	m_score = 0;
	m_faceDownCardPlayed = false;
	m_remainingTime = 0;
}

Eter::Player::Player(std::string username, const int& score, const std::vector<Piece>& cards, bool faceDownCardPlayed) : 
	m_username{ username }, m_score{ score }, m_cards{ cards }, m_faceDownCardPlayed { false }
{
}

Eter::Player::Player(std::string username, const int& score, const std::vector<Piece>& cards, Wizards wizard) :
	m_username{ username }, m_score{ score }, m_cards{ cards }, m_wizard { wizard }
{
}

Eter::Player::Player(const Player& other) :
	m_username{ other.m_username }, m_score{ other.m_score }, m_cards{ other.m_cards }, m_faceDownCardPlayed{ m_faceDownCardPlayed }
{
}

const std::string& Eter::Player::GetUserName() const
{
	return m_username;
}

const int& Eter::Player::GetScore() const
{
	return m_score;
}

const std::vector<Eter::Piece>& Eter::Player::GetCards() const
{
	return m_cards;
}

bool Eter::Player::GetFaceDownCardPlayed() const
{
	return m_faceDownCardPlayed;
}

const uint8_t& Eter::Player::GetRemainingTime() const
{
	return m_remainingTime;
}

void Eter::Player::setUserName(const std::string& username)
{
	m_username = username;
}

void Eter::Player::setScore(const int& score)
{
	m_score = score;
}

void Eter::Player::setCards(const std::vector<Piece>& cards)
{
	m_cards = cards;
}

void Eter::Player::SetFaceDownCardPlayed(const bool& faceDownCardPlayed)
{
	m_faceDownCardPlayed = faceDownCardPlayed;
}

void Eter::Player::setRemainingTime(const uint8_t& remainingTime)
{
	m_remainingTime = remainingTime;
}

Eter::Piece Eter::Player::RemovePiece(const Piece& removePiece)
{
	std::cout << "Piesa aleasa din deck este: " << removePiece.GetValue();
	return removePiece;
}

void Eter::Player::PrintCards(const std::vector<Piece>& cards)
{
	for (int i = 0; i < cards.size(); i++) {
		std::cout << "Piesa " << i + 1 << ': ' << cards[i].GetValue();
	}
	std::cout << '\n';
}

Eter::Piece Eter::Player::GetLastPlayedCard() const
{
    return m_lastPlayedCard;
}

bool Eter::Player::HasWon(const Board& board) const
{
   
    auto gameBoard = board.GetBoard();
    size_t maxSize = board.GetMaxSize();

    // Lambda to check if the tile's top piece belongs to this player
    auto isTileOwnedByPlayer = [this](const std::optional<Tile>& tile) {
        return tile.has_value() && tile->GetTopValue().GetUserName() == this->GetUserName();
    };

    // Check for horizontal, vertical, and diagonal lines
    for (size_t i = 0; i < maxSize; i++) {
        // Horizontal check
        if (isTileOwnedByPlayer(gameBoard[i][0]) &&
            isTileOwnedByPlayer(gameBoard[i][1]) &&
            isTileOwnedByPlayer(gameBoard[i][2])) {
            return true;
        }

        // Vertical check
        if (isTileOwnedByPlayer(gameBoard[0][i]) &&
            isTileOwnedByPlayer(gameBoard[1][i]) &&
            isTileOwnedByPlayer(gameBoard[2][i])) {
            return true;
        }
    }

    // Diagonal checks
    if (isTileOwnedByPlayer(gameBoard[0][0]) &&
        isTileOwnedByPlayer(gameBoard[1][1]) &&
        isTileOwnedByPlayer(gameBoard[2][2])) {
        return true;
    }

    if (isTileOwnedByPlayer(gameBoard[0][2]) &&
        isTileOwnedByPlayer(gameBoard[1][1]) &&
        isTileOwnedByPlayer(gameBoard[2][0])) {
        return true;
    }

    return false;
}


