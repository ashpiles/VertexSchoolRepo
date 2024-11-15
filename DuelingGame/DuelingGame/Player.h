#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player(std::string name_, CharacterStats stats_, GameResource* res);
	~Player();
	
};
