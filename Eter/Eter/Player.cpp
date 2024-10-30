#include "Player.h"

Eter::Player::Player()
{
	m_score = 0;
}

Eter::Player::Player(std::string username, const int& score, const std::vector<Piece>& cards) : 
	m_username{ username }, m_score{ score }, m_cards{ cards }
{
}

Eter::Player::Player(std::string username, const int& score, const std::vector<Piece>& cards, const Mage& mageCard) :
	m_username{ username }, m_score{ score }, m_cards{ cards }, m_mageCard{ mageCard }
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

const int& Eter::Player::GetTurnTimeRemaining() const
{
	return m_turnTimeRemaining;
}
