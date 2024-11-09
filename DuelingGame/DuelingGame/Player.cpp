
#include "Player.h"
#include "Action.h"
#include <iostream>


Player::Player(std::string name_, CharacterStats stats_, Vector2 pos, GameResource* res) 
	: Character(name_, stats_, pos, res) { } 


