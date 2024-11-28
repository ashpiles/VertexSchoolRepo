#pragma once
#include "Grid.h"

class Player : public Character
{
public:
	Player(std::string name_, CharacterStats stats_, Coordinate coord, GameResource* res);
	~Player();
 
};
