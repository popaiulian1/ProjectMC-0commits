#pragma once
#include <vector>
#include "Player.h"
#include "Board.h"

using Matrix = std::vector<std::vector<int>>;

namespace Eter {
	class PowerExplosion {

	public:

		//Constructor
		PowerExplosion() = default;
		~PowerExplosion() = default;

		//Getters
		Player* GetTriggeringPlayer() const;
		Matrix GetAffectedTiles() const;
		bool GetWasUsed() const;

		//Setters
		void SetTriggeringPlayer(Player* triggeringPlayer);
		void SetAffectedTiles(const Matrix& affectedTiles);
		void SetWasUsed(const bool& wasUsed);

	private:
		Player* m_triggeringPlayer;
		Matrix m_affectedTiles;
		bool m_wasUsed;
	};
}

