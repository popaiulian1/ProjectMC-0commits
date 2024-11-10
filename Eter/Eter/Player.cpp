#include "Player.h"
#include "Piece.h"
#include "Board.h"
#include "Tile.h"
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

