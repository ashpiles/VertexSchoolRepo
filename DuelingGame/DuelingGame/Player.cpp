
#include "Player.h"
#include "Action.h"
#include <iostream>


Player::Player(int MaxHealth, int AtkPower, int Armor, int MaxStamina, std::string Name, Rectangle Rect) 
	: Character(MaxHealth, AtkPower, Armor, MaxStamina, Name, Rect)
{ 
} 


std::unique_ptr<Action> Player::ChooseAction()
{
	int Input = 1; 

	return GetActionFromInput(Input); 
}
