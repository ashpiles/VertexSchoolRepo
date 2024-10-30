#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player(int MaxHealth, int AtkPower, int Armor, int MaxStamina, std::string Name);
	Action ChooseAction() override;
};
