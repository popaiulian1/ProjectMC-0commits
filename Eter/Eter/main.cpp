#include <iostream>
#include "Board.h"

int main(){

	Eter::Board board(Eter::GameType::Practice);
	std::cout << board << std::endl;
	board.SetTileValue(0, 0, 'a');
	std::cout << board << std::endl;
	board.SetTileValue(0, 1, 'b');
	std::cout << board << std::endl;
	board.SetTileValue(1, 0, 'c');
	std::cout << board << std::endl;
	board.SetTileValue(1, 1, 'd');
	std::cout << board << std::endl;
	board.SetTileValue(2, 0, 'e');
	std::cout << board << std::endl;
	board.SetTileValue(2, 1, 'f');
	std::cout << board << std::endl;
	board.SetTileValue(0, 2, 'g');
	std::cout << board << std::endl;
	board.SetTileValue(1, 2, 'h');
	std::cout << board << std::endl;
	board.SetTileValue(2, 2, 'i');
	std::cout << board << std::endl;

	return 0;
} 