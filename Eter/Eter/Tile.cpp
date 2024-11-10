#include "Tile.h"
#include "Piece.h"
#include <stdexcept>
#include <stack>

Eter::Tile::Tile(const Piece& piece){
	m_value.push(piece);
}

std::stack<Eter::Piece> Eter::Tile::GetValue() const {
	return m_value;
}

Eter::Piece Eter::Tile::GetTopValue() const{
	if (!m_value.empty()) {
		return m_value.top();
	}
	throw std::runtime_error("No piece on tile"); // Handle error if stack is empty
}

void Eter::Tile::SetValue(const Piece& piece){
	m_value.push(piece);
}

std::ostream& Eter::operator<<(std::ostream& os, const Tile& tile){
	if (!tile.m_value.empty()) {
		const Piece& topPiece = tile.m_value.top();
		os << topPiece.GetUserName() << ":" << topPiece.GetValue(); 
	}
	else 
		os << "Empty tile\n";
	return os;
}
