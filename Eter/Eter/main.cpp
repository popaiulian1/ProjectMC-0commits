#include <iostream>
#include "Game.h"
#include "json.hpp"
#include <fstream>

void jsonTestRead() {
	std::ifstream input("exampleImporting.json");
	nlohmann::json j;
	input >> j;

	std::cout << j.dump(4) << std::endl;
}

void jsonTestWrite() {
	nlohmann::json j = R"(
		{
		"pi": 3.141,
		"happy": true,
		"name": "Niels",
		 "nothing": null,
		 "answer": {
		"everything": 42
		 },
		 "list": [ 1, 0, 2 ],
		 "object": {
		   "currency": "USD",
		   "value": 42.99
		 }
		})"_json;

	std::ofstream output("exampleExporting.json");
	output << j.dump(4) << std::endl;

}

int main() {

	/*Eter::Game game;
	game.StartGame();*/

	Eter::Board board(Eter::GameType::Practice);

	board.SetTileValue({ 0, 0 }, 'X', "Player1");
	board.SetTileValue({ 0, 1 }, 'X', "Player1");
	board.SetTileValue({ 0, 2 }, 'X', "Player1");
	board.SetTileValue({ 1, 2 }, 'X', "Player1");

	board.exportBoardToJson("boardSave.json");
	

	/*jsonTestRead();
	jsonTestWrite();*/

	return 0;
}
