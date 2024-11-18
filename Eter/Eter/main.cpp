#include <iostream>
#include "Board.h"
#include "Player.h"
#include "Game.h"

int main(){

	Eter::Board board(Eter::GameType::Practice);
	/*std::vector<Eter::Piece> Cards;
	Eter::Player Player1("Fluviu", 0, Cards, false);
	Eter::Player Player2("Mama", 0, Cards, false);
	Eter::Game game(Player1, Player2, board, Eter::GameType::Practice);
	game.StartGame(Player1, Player2, board);
	std::cout << std::endl;

	if (Player1.GetFaceDownCardPlayed() == false) {
		game.Illusion(Player1, board);
		std::cout << board << std::endl;
		Player1.SetFaceDownCardPlayed(true);
	}
		
	if (Player2.GetFaceDownCardPlayed() == false) {
		game.Illusion(Player2, board);
		std::cout << board << std::endl;
		Player2.SetFaceDownCardPlayed(true);
	}*/

	/*game.Illusion(Player1, board);
	std::cout << board << std::endl;
	std::cout << Player1.GetFaceDownCardPlayed() << std::endl;
	game.Illusion(Player2, board);
	std::cout << board << std::endl;
	std::cout << Player2.GetFaceDownCardPlayed() << std::endl;*/
	
	std::cout << board;
	board.SetTileValue({ 0, 0 }, 'A', Eter::Player("Player1", 0, std::vector<Eter::Piece>(), false));
	std::cout << board;
	board.SetTileValue({ -1, 0 }, 'B', Eter::Player("Player2", 0, std::vector<Eter::Piece>(), false));
	std::cout << board;
	board.SetTileValue({ -1, -1 }, 'C', Eter::Player("Player1", 0, std::vector<Eter::Piece>(), false));
	std::cout << board;
	board.SetTileValue({ 2, 2 }, 'D', Eter::Player("Player2", 0, std::vector<Eter::Piece>(), false));
	std::cout << "\n" << board;

	return 0;
} 