#pragma once
#include "Board.h"
#include "Tile.h"
#include "Player.h"

namespace Eter {

	enum class ElementalCardName {
		CONTROLLED_EXPLOSION,
		DESTRUCTION,
		FLAME,
		FIRE,
		ASH,
		SPARK,
		SQUALL,
		GALE,
		HURRICANE,
		GUST,
		MIRAGE,
		STORM,
		TIDE,
		MIST,
		WAVE,
		WHIRLPOOL,
		BLIZZARD,
		WATERFALL,
		SUPPORT,
		EARTHQUAKE,
		CRUMBLE,
		BORDER,
		AVALANCHE,
		ROCK,
		NONE
	};

	class Elemental
	{
	public:
		
		//Constructors
		Elemental() = default;
		Elemental(const Board board, bool ElementalCardUsed, ElementalCardName nameCard);
		Elemental(const Elemental& other);
		~Elemental() = default;

		//Methods
		void Destruction(const Player& opponent, const Board& board);
		void Squall(Player& opponent, Board& board);
		void Gale(Board& board, Player& player1, Player& player2);
		void Storm(int row, int column);
		void Tide(int row1, int column1, int row2, int column2);
		void Mist(Player& player);
		void Earthquake(const Board& board);
		void Rock(Board& board, Player& player, Player& opponent);
		void Flame(Player& opponent, Board& board, const Piece& playerCard);
		void Fire(Board& board, Player& player1, Player& player2);
		void Ash(Board& board, Player& player);
		

	private:
		Board m_board;
		bool m_ElementalCardUsed;
		ElementalCardName m_nameCard;
	};
}


