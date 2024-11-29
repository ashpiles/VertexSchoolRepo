#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H
#include "GameEntity.h"

struct CharacterStats
{ 
	int maxHealth;
	int health;
	int atkPower;
	int armor;
	int maxStamina;
	int stamina; 
};

// Base class for all complex Game Entities
class Character : public GameEntity 
{
public:
	Character(std::string name_, CharacterStats stats_, Coordinate coord, GameResource* res);
	~Character();
	void UpdateHealth(int Amount);
	void UpdateStamina(bool Increase);
	void InitStats();
	void DrawItem();
	Vector2 GetWorldPos();

	std::deque<MoveAction> PathFindTo(Coordinate coord);

protected:

	std::string name;
	CharacterStats stats;
};



#endif
