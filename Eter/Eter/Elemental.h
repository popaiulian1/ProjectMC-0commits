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
		const Board GetBoardForElemental() const;


		//Setters
		void SetElementalCardUsed(const bool ElementalCardUsed);
		void SetNameCard(const ElementalCardName nameCard);
		void SetUsername(const std::string username);
		void SetBoardForElemental(const Board& board);
	

		//Methods for powers
		//void ControlledExplosion(); // TO DO
		void Destruction(const Player& opponent, Board& board);
		void Flame(Player& opponent, Board& board);
		void Fire(Board& board, Player& player1, Player& player2);
		void Ash(Board& board, Player& player);
		void Spark(Board& board, Player& player);
		void Squall(Player& opponent, Board& board);
		void Gale(Board& board, Player& player1, Player& player2);
		void Hurricane(Board& board);
		void Gust(Board& board);
		void Mirage(Board& board, Player& player);
		void Storm(int row, int column);
		void Tide(int row1, int column1, int row2, int column2);
		void Mist(Player& player);
		void Wave(Board& board, Player& player);
		void Whirlpool(Board& board);
		//void Blizzard(Board& board, int row, int column, Player& opponent); //TO DO
		void Waterfall(Board& board);
		//void Support(); // TO DO
		void Earthquake(Board& board);
		//void Crumble(); // TO DO
		//void Border(); // TO DO
		//void Avalanche(Board& board); // TO DO
		void Rock(Board& board, Player& player, Player& opponent);
		
		
		//Methods
		void shiftRowToLeft(Board& board, int index);
		void shiftRowToRight(Board& board, int index);
		void shiftColUp(Board& board, int index);
		void shiftColDown(Board& board, int index);
		bool isRowFull(const Board& board, int rowIndex);
		bool isColumnFull(const Board& board, int colIndex);
		bool neighboringCardsStacs(int rowIndex1, int colIndex1, int rowIndex2, int colIndex2);
		const std::string toSringElementalCardName(ElementalCardName nameCard);



	private:
		Board m_board;
		bool m_ElementalCardUsed;
		ElementalCardName m_nameCard;
		std::string m_username;
	};
}


