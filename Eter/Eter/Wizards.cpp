#include "Wizards.h"
#include "Board.h"

Eter::Wizards::Wizards() :
	name("Unknown"), mageType(MageType::FIRE), magicPowerUsed(false), etherCards(1), board(nullptr) {}

Eter::Wizards::Wizards(std::string wizardName, MageType type, const Board* gameBoard) : 
	name(wizardName), mageType(type), magicPowerUsed(false), etherCards(1), board(gameBoard) {}

Eter::Wizards::Wizards(const Wizards& other) :
	name(other.name), mageType(other.mageType), magicPowerUsed(other.magicPowerUsed), etherCards(other.etherCards), board(other.board) {}






