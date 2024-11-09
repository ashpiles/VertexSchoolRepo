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

	Character(std::string name_, CharacterStats stats_, Vector2 pos, GameResource* res);

	void UpdateHealth(int Amount);
	void UpdateStamina(bool Increase);

	void InitStats();
	//std::unique_ptr<Action> GetActionFromInput(int Input); 
	//virtual std::unique_ptr<Action> ChooseAction() = 0;


protected:
	std::string name;
	CharacterStats stats;
};

#endif
