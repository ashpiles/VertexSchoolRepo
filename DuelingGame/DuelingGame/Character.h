#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include <memory> 
#include "raylib.h"
#include "Shape2D.h"

class Action;

class Character
{
public:

	Character(int MaxHealth, int AtkPower, int Armor, int MaxStamina, std::string Name, Rectangle Rect);
	int GetHealth() const { return Health; }
	std::string GetName() const { return Name; }
	bool GetIsAlive() const { return Health > 0; }
	int GetAtkPower() const { return AtkPower; }
	int GetStamina() const { return Stamina; }

	void UpdateHealth(int Amount);
	void UpdateStamina(bool Increase);
	Rectangle GetHitbox();

	virtual std::unique_ptr<Action> ChooseAction() = 0;
	void InitStats();
	std::unique_ptr<Action> GetActionFromInput(int Input); 

	Vector2& Position;
	Vector2& Scale;

protected:
	std::string Name;
	int MaxHealth;
	int Health;
	int AtkPower;
	int Armor;
	int MaxStamina;
	int Stamina; 
	Shape2D Shape;
};

#endif
