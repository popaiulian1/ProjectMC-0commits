#include "Tile.h"
#include "Piece.h"
#include <stdexcept>
#include <stack>

Eter::Tile::Tile(const Piece& piece) {
	m_value.push_back(piece);
}

Eter::Tile::Tile(const char& value)
{
	m_value.push_back(Piece(value, true, "", false, false));
}

std::deque<Eter::Piece> Eter::Tile::GetValue() const {
	return m_value;
}

std::deque<Eter::Piece>& Eter::Tile::GetValueRef()
{
	return m_value;
}

Eter::Piece Eter::Tile::GetTopValue()const {
	if (!m_value.empty()) {
		return m_value.back();
	}
	throw std::runtime_error("No piece on tile"); // Handle error if stack is empty
}

Eter::Piece& Eter::Tile::GetTopValueRef()
{
	if (!m_value.empty()) {
		return m_value.back();
	}
	throw std::runtime_error("No piece on tile"); // Handle error if stack is empty
}

void Eter::Tile::SetValue(const Piece& piece) {
	if (m_isPit) {
		throw std::runtime_error("Cannot set value on a pit tile");
	}
	Piece updatedPiece = piece;
    updatedPiece.SetIsPlaced(true);
	m_value.push_back(piece);
}

void Eter::Tile::SetAsPit()
{
	m_isPit = true;
	/*while (!m_value.empty()) {
		m_value.pop_back();
	}*/
}

void Eter::Tile::RemoveStack()
{
	while (!m_value.empty()) {
		m_value.pop_back();
	}
}

Eter::Tile& Eter::Tile::operator=(const Piece& piece)
{
	m_value.push_back(piece); return *this;
}

bool Eter::Tile::IsPit() const
{
	return m_isPit;
}


std::ostream& Eter::operator<<(std::ostream& os, const Tile& tile) {
	if (!tile.m_value.empty()) {
		const Piece& topPiece = tile.m_value.back();
		os << topPiece.GetUserName() << ":" << topPiece.GetValue();
	}
	else
		os << "Empty tile\n";
	return os;
}

void Eter::to_json(nlohmann::json& j, const Tile& t)
{
	j = nlohmann::json{
		{"value", t.GetValue()},
		{"isPit", t.IsPit()}
	};
}
