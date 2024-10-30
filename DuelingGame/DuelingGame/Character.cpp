#include "Character.h"
#include "Log.h"
#include <iostream>

Character::Character(int MaxHealth, int AtkPower, int Armor, int MaxStamina, std::string Name) :
	MaxHealth(MaxHealth), AtkPower(AtkPower), Armor(Armor), MaxStamina(MaxStamina), Name(Name)
{
	InitStats();
}

void Character::UpdateHealth(int Amount)
{
	Health += Amount;
	if (Health <= 0) Health = 0;
	Log::LogMessage(LOG_ERROR, Name + " has " + std::to_string(Health) + " health remaining");
}

void Character::UpdateStamina(bool Increase)
{
	Stamina = (Increase) ? Stamina += 1 : Stamina -= 1;
	if (Stamina > MaxStamina)
		Stamina = MaxStamina;
	else if (Stamina <= 0)
		Stamina = 0;
}

void Character::InitStats()
{
	Health = MaxHealth;
	Stamina = MaxStamina;
}
Action Character::GetActionFromInput(int Input)
{
	switch (Input)
	{
	case 0: return Action(ATTACK, Name);

	case 1:
		UpdateStamina(false);
		return Action(PARRY, Name);
	case 2:
		UpdateStamina(true);
		return Action(DEFEND, Name);
	}
}