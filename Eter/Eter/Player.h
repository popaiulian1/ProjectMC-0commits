#pragma once
#include <string>
#include <vector>
#include "Piece.h"
#include "Wizards.h"

namespace Eter {
	class Player {
	public:
		Player();
		Player(std::string username, const int& score, const std::vector<Piece>& cards);
		Player(std::string username, const int& score, const std::vector<Piece>& cards, Wizards wizard);
		Player(const Player& other);
		~Player() = default;

		const std::string& GetUserName() const;
		const int& GetScore() const;
		const std::vector<Piece>& GetCards() const;
		const int& GetRemainingTime() const;

		void setUserName(const std::string& username);
		void setScore(const int& score);
		void setCards(const std::vector<Piece>& cards);
		void setRemainingTime(const int& remainingTime);

	private:
		std::string m_username;
		int m_score;
		std::vector<Piece> m_cards;
		Wizards m_wizard;
		int m_remainingTime;
	};
}
