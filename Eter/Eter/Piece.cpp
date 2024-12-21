#include "Piece.h"

Eter::Piece::Piece() : 
	m_value{ '\0' }, 
	m_isPlaced{ false }, 
	m_username{ "" }, 
	m_isIllusion{ false },
	m_eterCard{ false },
	m_isEliminated{ false }
{}

Eter::Piece::Piece(const char& value, const bool& isPlaced, const std::string& username, const bool& isIllusion, const bool& eterCard, const bool& isEliminated) :
	m_value{ value }, 
	m_isPlaced{ isPlaced }, 
	m_username{ username }, 
	m_isIllusion{ isIllusion },
	m_eterCard{ eterCard },
	m_isEliminated {isEliminated}
{}

Eter::Piece::Piece(Piece && other) noexcept
{
	m_value = other.m_value;
	m_isPlaced = other.m_isPlaced;
	m_username = other.m_username;
	m_isIllusion = other.m_isIllusion;
	m_eterCard = other.m_eterCard;
	m_isEliminated = other.m_isEliminated;

	other.m_value = '\0';
	other.m_isPlaced = false;
	other.m_username = "";
	other.m_isIllusion = false;
	other.m_eterCard = false;
	other.m_isEliminated = false;
}

Eter::Piece::Piece(const Piece& other)
{
	m_value = other.m_value;
	m_isPlaced = other.m_isPlaced;
	m_username = other.m_username;
	m_isIllusion = other.m_isIllusion;
	m_eterCard = other.m_eterCard;
	m_isEliminated = other.m_isEliminated;
}

Eter::Piece& Eter::Piece::operator=(const Piece& other)
{
	if (this != &other) {
		m_value = other.m_value;
		m_isPlaced = other.m_isPlaced;
		m_username = other.m_username;
		m_isIllusion = other.m_isIllusion;
		m_eterCard = other.m_eterCard;
		m_eterCard = other.m_isEliminated;
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

const bool& Eter::Piece::GetEterCard() const
{
	return m_eterCard;
}

const bool& Eter::Piece::GetIsEliminated() const
{
	return m_isEliminated;
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

void Eter::Piece::SetEterCard(const bool& eterCard)
{
	m_eterCard = eterCard;
}

void Eter::Piece::SetIsEliminated(const bool& isEliminated)
{
	m_isEliminated = isEliminated;
}

void Eter::to_json(nlohmann::json& j, const Piece& p)
{
	j = nlohmann::json{
		{"value", p.GetValue()-'0'}, // convert the char to an int
		{"isPlaced", p.GetIsPlaced()},
		{"username", p.GetUserName()},
		{"isIllusion", p.GetIsIllusion()},
		{"eterCard", p.GetEterCard()},
		{"isEliminated", p.GetIsEliminated()}
	};
}
