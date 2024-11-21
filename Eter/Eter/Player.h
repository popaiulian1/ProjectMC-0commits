#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Piece.h"
#include "Board.h"

namespace Eter {
	class Player
	{
	public:
		Player() = default;
		~Player() = default;
		Player(const Player&) = default;
		Player& operator=(const Player& other);
		Player(const std::string& username, const int& score, const std::vector<Eter::Piece>& pieces, const bool& illusionPlayed);
		//+ player constructor with wizard and element
		
		//Getters
		const std::string& GetUserName() const;
		const int& GetScore() const;
		const std::vector<Eter::Piece>& GetPieces() const;
		const bool& GetIllusionPlayed() const;
		Piece GetLastPlayedPiece() const;

		//Setters
		void SetUserName(const std::string& username);
		void SetScore(const int& score);
		void SetPieces(const std::vector<Eter::Piece>& pieces);
		void SetIllusionPlayed(const bool& illusionPlayed);
		 
		// (TO DO) -> Iulian: Add two methods called Play() and ChoosePiece() to the Player class
		//					  first method returns a pair (positions) second returns char as a value 
		//					  to be placed on the board, it needs to be off the players deck.
		// ---------------------------------------------------------------------------------------->
		// (ALSO) -> Iulian:  Look over lastPlayedPiece and reimplement it.

		//Methods
		void PrintPieces(const std::vector<Piece>& pieces) const;
		void AddPiece(const Eter::Piece& piece);
		void RemovePieces();
		bool HasWon(const Board& board);
		friend std::ostream& operator<<(std::ostream& os, const Player& player);

	private:
		std::string m_username;
		int m_score;
		std::vector<Eter::Piece> m_pieces;
		Piece m_lastPlayedPiece;
		bool m_illusionPlayed; //m_faceDownCardPlayed
	};
}



