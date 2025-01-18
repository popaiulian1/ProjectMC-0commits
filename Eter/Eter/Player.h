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
			    const size_t& gamesWon,
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
		size_t GetGamesWon() const;
		bool GetEterCardPlayed() const;

		//Setters
		void SetUserName(const std::string& username);
		void SetScore(const int& score);
		void SetPieces(const std::vector<Eter::Piece>& pieces);
		void SetIllusionPlayed(const bool& illusionPlayed);
		void SetPowerExplosionAccess(const bool& powerExplosionAccess);
		void SetGamesWon(const size_t& gamesWon);
		void SetEterCardPlayed(const bool& eterCardPlayed);
		void SetLastPlayedPiece(const Piece& lastPlayedPiece);
		 
		//Methods
		std::pair<int, int> Play(bool& firstMove); //takes row and column index for piece position to be played (Iulian) -> modified to int because it the compiler did not take negative values somehow???
		char ChoosePiece(); //player chooses a piece from his deck; the chosen piece it's removed then from his deck
		void PrintPieces() const;
		void AddPiece(const Eter::Piece& piece);
		void RemovePieces();
		bool HasWon(const Board& board);
		void ResetPlayer(); //for tournament, resets player 
		void IncrementGamesWon();
		friend std::ostream& operator<<(std::ostream& os, const Player& player);

	private:
		std::string m_username;
		std::vector<Eter::Piece> m_pieces;
		int m_score;
		size_t m_gamesWon;

		Piece m_lastPlayedPiece;
		bool m_illusionPlayed; 
		bool m_powerExplosionAccess;
		bool m_eterCardPlayed;

		//std::bitset<static_cast<size_t>(PlayerState::MAX_STATE)> m_states;  Compact storage for player states | IDEA TO IMPLEMENT
	};

	void to_json(nlohmann::json& j, const Player& p);
	void from_json(const nlohmann::json& j, Player& p);
}


