#pragma once
#include <string>
#include "Action.h"


class Character
{
public:

	Character(int MaxHealth, int AtkPower, int Armor, int MaxStamina, std::string Name);
	int GetHealth() const { return Health; }
	std::string GetName() const { return Name; }
	bool GetIsAlive() const { return Health > 0; }
	int GetAtkPower() const { return AtkPower; }
	int GetStamina() const { return Stamina; }

	void UpdateHealth(int Amount);
	void UpdateStamina(bool Increase);

	virtual Action ChooseAction() = 0;
	void InitStats();
	Action GetActionFromInput(int Input);

protected:
	std::string Name;
	int MaxHealth;
	int Health;
	int AtkPower;
	int Armor;
	int MaxStamina;
	int Stamina;
};