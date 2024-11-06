#include "Player.h"
#include "Piece.h"

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

const int& Eter::Player::GetRemainingTime() const
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

void Eter::Player::setRemainingTime(const int& remainingTime)
{
	m_remainingTime = remainingTime;
}
