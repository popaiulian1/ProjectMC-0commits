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
		Player() = default;
		Player( const std::string& username,
			    const std::vector<Eter::Piece>& pieces,
			    const int& score,
			    const int& gamesWon,
				const Piece& lastPlayedPiece,
			    const bool& illusionPlayed,
				const bool& powerExplosionAccess,
			    const bool& eterCardPlayed
			 );

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
		const bool& GetPowerExplosionAccess() const;
		int GetGamesWon() const;
		bool GetEterCardPlayed() const;

		//Setters
		void SetUserName(const std::string& username);
		void SetScore(const int& score);
		void SetPieces(const std::vector<Eter::Piece>& pieces);
		void SetIllusionPlayed(const bool& illusionPlayed);
		void SetPowerExplosionAccess(const bool& powerExplosionAccess);
		void SetGamesWon(const int& gamesWon);
		void SetEterCardPlayed(const bool& eterCardPlayed);
		 
		//Methods
		std::pair<int, int> Play(bool& firstMove); //takes row and column index for piece position to be played (Iulian) -> modified to int because it the compiler did not take negative values somehow???
		char ChoosePiece(); //player chooses a piece from his deck; the chosen piece it's removed then from his deck
		void PrintPieces() const;
		void AddPiece(const Eter::Piece& piece);
		void RemovePieces();
		bool HasWon(const Board& board);
		void ResetPlayer(); //for tournament, resets player 
		friend std::ostream& operator<<(std::ostream& os, const Player& player);

	private:
		std::string m_username;
		std::vector<Eter::Piece> m_pieces;
		int m_score;
		int m_gamesWon;

		Piece m_lastPlayedPiece;
		bool m_illusionPlayed; 
		bool m_powerExplosionAccess;
		bool m_eterCardPlayed;
	};
}



