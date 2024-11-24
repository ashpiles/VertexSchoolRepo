
#include "Player.h"
#include "Action.h"
#include <iostream>


Player::Player(std::string name_, CharacterStats stats_, Coordinate coord, GameResource* res)
	: Character(name_, stats_, coord, res) { }

Player::~Player() {}
