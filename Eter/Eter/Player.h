#pragma once
#include <string>
#include <vector>
#include "Piece.h"
#include "Mage.h"

namespace Eter {
	class Player {
	public:
		Player();
		Player(std::string username, const int& score, const std::vector<Piece>& cards);
		Player(std::string username, const int& score, const std::vector<Piece>& cards, const Mage& mageCard);
		~Player() = default;
		const std::string& GetUserName() const;
		const int& GetScore() const;
		const std::vector<Piece>& GetCards() const;
		const Mage& GetMageCard() const;
		const int& GetTurnTimeRemaining() const;
	private:
		std::string m_username;
		int m_score;
		std::vector<Piece> m_cards;
		Mage m_mageCard;
		int m_turnTimeRemaining;
	};
}
