#pragma once
#include "Board.h"
#include "Tile.h"
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
		Elemental();
		Elemental(const Board board, bool ElementalCardUsed, ElementalCardName nameCard);
		Elemental(const Elemental& other);
		~Elemental() = default;

		void Storm(int row, int column);
		void Tide(int row1, int column1, int row2, int column2);
	

	private:
		Board m_board;
		bool m_ElementalCardUsed;
		ElementalCardName m_nameCard;
	};
}


