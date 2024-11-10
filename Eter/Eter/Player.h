#pragma once
#include <string>
#include <vector>
#include "Piece.h"
#include "Wizards.h"

namespace Eter {
	class Player {
	public:
		Player();
		Player(std::string username, const int& score, const std::vector<Piece>& cards, bool faceDownCardPlayed);
		Player(std::string username, const int& score, const std::vector<Piece>& cards, Wizards wizard);
		Player(const Player& other);
		~Player() = default;

		const std::string& GetUserName() const;
		const int& GetScore() const;
		const std::vector<Piece>& GetCards() const;
		bool GetFaceDownCardPlayed() const;
		Piece GetLastPlayedCard() const;
		const uint8_t& GetRemainingTime() const;

		void setUserName(const std::string& username);
		void setScore(const int& score);
		void setCards(const std::vector<Piece>& cards);
		void SetFaceDownCardPlayed(const bool& faceDownCardPlayed);
		void setRemainingTime(const uint8_t& remainingTime);

		Piece RemovePiece(const Piece& removePiece);
		void PrintCards(const std::vector<Piece>& cards);
		
		bool HasWon(const Board& board) const; // Returns true if the player has won

	private:
		std::string m_username;
		int m_score;
		std::vector<Piece> m_cards;
		bool m_faceDownCardPlayed;
		Piece m_lastPlayedCard;
		Wizards m_wizard;
		uint8_t m_remainingTime;
	};
}



