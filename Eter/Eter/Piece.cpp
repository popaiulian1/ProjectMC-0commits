#include "Piece.h"

Eter::Piece::Piece() : m_value{ '\0'}, m_isPlaced{false}, m_username{""}
{}

Eter::Piece::Piece(const char& value, const bool& isPlaced, const std::string& username) : m_value{ value }, m_isPlaced{ isPlaced }, m_username{username}
{}

char Eter::Piece::GetValue() const
{
	return m_value;
}

bool Eter::Piece::GetIsPlaced() const
{
	return m_isPlaced;
}

const std::string& Eter::Piece::GetUserName() const
{
	return m_username;
}

void Eter::Piece::SetValue(const char& value)
{
	m_value = value;
}

void Eter::Piece::SetIsPlaced(const bool& isPlaced)
{
	m_isPlaced = isPlaced;
}

void Eter::Piece::SetUserName(const std::string& username)
{
	m_username = username;
}



