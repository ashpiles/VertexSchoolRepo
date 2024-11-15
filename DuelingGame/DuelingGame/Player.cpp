
#include "Player.h"
#include "Action.h"
#include <iostream>


Player::Player(std::string name_, CharacterStats stats_, GameResource* res)
	: Character(name_, stats_, res) { }

Player::~Player() {}
