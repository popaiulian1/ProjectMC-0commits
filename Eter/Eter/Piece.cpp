#include "Piece.h"

Eter::Piece::Piece() : m_value{ '\0' }, m_isPlaced{ false }, m_username{ "" }
{}

Eter::Piece::Piece(const char& value, const bool& isPlaced, const std::string& username, const bool& isIllusion) : m_value{ value }, m_isPlaced{ isPlaced }, m_username{ username }, m_isIllusion{ isIllusion }
{}

Eter::Piece::Piece(Piece && other) noexcept
{
	m_value = other.m_value;
	m_isPlaced = other.m_isPlaced;
	m_username = other.m_username;
	m_isIllusion = other.m_isIllusion;
	other.m_value = '\0';
	other.m_isPlaced = false;
	other.m_username = "";
	other.m_isIllusion = false;
}

Eter::Piece::Piece(const Piece& other)
{
	m_value = other.m_value;
	m_isPlaced = other.m_isPlaced;
	m_username = other.m_username;
	m_isIllusion = other.m_isIllusion;
}

Eter::Piece& Eter::Piece::operator=(const Piece& other)
{
	if (this != &other) {
		m_value = other.m_value;
		m_isPlaced = other.m_isPlaced;
		m_username = other.m_username;
		m_isIllusion = other.m_isIllusion;
	}
	return *this;
}

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

const bool& Eter::Piece::GetIsIllusion() const
{
	return m_isIllusion;
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

void Eter::Piece::SetIsIllusion(const bool& isIllusion)
{
	this->m_isIllusion = isIllusion;
}



