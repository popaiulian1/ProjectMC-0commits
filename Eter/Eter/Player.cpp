#include "Player.h"

Eter::Player::Player(std::string username) : m_username{ username }
{
}

const std::string& Eter::Player::GetUserName() const
{
	return m_username;
}
