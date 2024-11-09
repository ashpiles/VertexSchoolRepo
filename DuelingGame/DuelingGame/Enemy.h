#pragma once 
#include "Character.h"
#include <random>
 
class Enemy : public Character
{
public:
	Enemy(std::string name_, CharacterStats stats_, Vector2 pos, GameResource* res);

	//void IncreaseDifficulty(int RoundNumber); 

private: 
	std::mt19937 Generator;
	std::uniform_int_distribution<> Distribution;
};
 