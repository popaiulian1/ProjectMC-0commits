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

		//Setters
		void SetTriggeringPlayer(Player* triggeringPlayer);
		void SetAffectedTiles(const Matrix& affectedTiles);

	private:
		Player* m_triggeringPlayer;
		Matrix m_affectedTiles;
	};
}

