#include <iostream>
#include "Board.h"

int main(){

	Eter::Board board(Eter::GameType::Duel);
	std::cout << board << std::endl;
	Eter::Board board2(Eter::GameType::Practice);
	std::cout << board2 << std::endl;
	Eter::Board board3 = board2;
	std::cout << board3 << std::endl;

	Eter::Board board4(board);
	std::cout << board4 << std::endl;

	//std::cout<<static_cast<int>(board4.getType()); de verificat dupa implementarea constructorilor

	return 0;
}