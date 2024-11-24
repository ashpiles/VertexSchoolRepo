#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include <memory> 
#include "Grid.h"
#include "raylib.h"

struct CharacterStats
{ 
	int maxHealth;
	int health;
	int atkPower;
	int armor;
	int maxStamina;
	int stamina; 
};

class Character : public GridItem
{
public:
	Character(std::string name_, CharacterStats stats_, Coordinate coord, GameResource* res);
	~Character();
	void UpdateHealth(int Amount);
	void UpdateStamina(bool Increase);
	void InitStats();
	void DrawItem();
	Vector2 GetWorldPos() { return { (float)coordinate.x * TILE_SIZE, (float)coordinate.y * TILE_SIZE }; }

	//std::unique_ptr<Action> GetActionFromInput(int Input); 
	//virtual std::unique_ptr<Action> ChooseAction() = 0;
protected:

	const float moveTimerMax;
	float moveTimer = 0;
	std::string name;
	CharacterStats stats;
};

#endif
