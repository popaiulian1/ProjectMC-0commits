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
		Elemental(const Board board, bool ElementalCardUsed, ElementalCardName nameCard, std::string username);
		Elemental(const Elemental& other);
		Elemental(Elemental&& other) = default;
		Elemental& operator=(const Elemental& other) = default;
		~Elemental() = default;


		//Getters
		const bool GetElementalCardUsed() const;
		const ElementalCardName GetNameCard() const;
		const std::string GetUsername() const;


		//Setters
		void SetElementalCardUsed(const bool ElementalCardUsed);
		void SetNameCard(const ElementalCardName nameCard);
		void SetUsername(const std::string username);
	

		//Methods for powers
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
		void Spark(Board& board, Player& player);
		void Hurricane(Board& board);
		void Gust(Board& board);
		
		//Methods
		void shiftRowToLeft(Board& board, int index);
		void shiftRowToRight(Board& board, int index);
		void shiftColUp(Board& board, int index);
		void shiftColDown(Board& board, int index);
		bool isRowFull(const Board& board, int rowIndex);
		bool isColumnFull(const Board& board, int colIndex);
		const std::string toSringElementalCardName(ElementalCardName nameCard);



	private:
		Board m_board;
		bool m_ElementalCardUsed;
		ElementalCardName m_nameCard;
		std::string m_username;
	};
}


