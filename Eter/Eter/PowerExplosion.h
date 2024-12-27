#pragma once
#include <vector>
#include "Player.h"
#include "Board.h"

using Matrix = std::vector<std::vector<int>>;

namespace Eter {

	enum class powerExplosionCard { //TO DISCUSS ABOUT CARD TYPES
		cardType1,
		cardType2,
		cardType3,
	};

	class PowerExplosion {

	public:

		//Constructor
		PowerExplosion() = default;
		PowerExplosion(const Matrix& affetedTiles);
		~PowerExplosion() = default;

		//Getters
		Player* GetTriggeringPlayer() const;
		Matrix GetAffectedTiles() const;
		bool GetWasUsed() const;

		//Setters
		void SetTriggeringPlayer(Player* triggeringPlayer);
		void SetAffectedTiles(const Matrix& affectedTiles);
		void SetWasUsed(const bool& wasUsed);

		//Methods
		void Trigger(Board& board, Player& player); 
		Matrix Rotate90Degrees();
		void ApllyExplosion(Board& board, Player& player);

	private:
		Player* m_triggeringPlayer;
		Matrix m_affectedTiles;	
		bool m_wasUsed;
	};
}

