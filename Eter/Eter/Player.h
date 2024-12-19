#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Piece.h"
#include "Board.h"

namespace Eter {
	
	class Player {
	
	public:
		//Constructors
		Player();
		Player(const std::string& username, const int& score, const std::vector<Eter::Piece>& pieces, const bool& illusionPlayed, const bool& eterCardPlayed, const int& gamesWon);

		//Rule Of Five 
		~Player() = default;

		Player(const Player&) = default;
		Player& operator=(const Player& other);

		Player(Player&& other) noexcept;
		Player& operator=(Player&& other) noexcept;

		void swap(Player& other) noexcept;
		
		//Getters
		const std::string& GetUserName() const;
		const int& GetScore() const;
		const std::vector<Eter::Piece>& GetPieces() const;
		std::vector<Eter::Piece>& GetPiecesReference(); //Non-const reference
		const bool& GetIllusionPlayed() const;
		Piece GetLastPlayedPiece() const;
		//const bool& GetPowerExplosionAccess() const;
		int GetGamesWon() const;
		bool GetEterCardPlayed() const;

		//Setters
		void SetUserName(const std::string& username);
		void SetScore(const int& score);
		void SetPieces(const std::vector<Eter::Piece>& pieces);
		void SetIllusionPlayed(const bool& illusionPlayed);
		//void SetPowerExplosionAccess(const bool& powerExplosionAccess);
		void SetGamesWon(const int& gamesWon);
		void SetEterCardPlayed(const bool& eterCardPlayed);
		 
		//Methods
		std::pair<int, int> Play(); //takes row and column index for piece position to be played (Iulian) -> modified to int because it the compiler did not take negative values somehow???
		char ChoosePiece(); //player chooses a piece from his deck; the chosen piece it's removed then from his deck
		void PrintPieces() const;
		void AddPiece(const Eter::Piece& piece);
		void RemovePieces();
		bool HasWon(const Board& board);
		void ResetPlayer(); //for tournament, resets player 
		friend std::ostream& operator<<(std::ostream& os, const Player& player);

	private:
		std::string m_username;
		int m_score;
		std::vector<Eter::Piece> m_pieces;
		Piece m_lastPlayedPiece;
		bool m_illusionPlayed; 
		//bool m_powerExplosionAccess;
		int m_gamesWon;
		bool m_eterCardPlayed;
	};
}



