#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player(int MaxHealth, int AtkPower, int Armor, int MaxStamina, std::string Name, Rectangle rect);
	std::unique_ptr<Action> ChooseAction() override;
};
