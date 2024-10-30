
#include "Player.h"
#include <iostream>
#include "Log.h"


Player::Player(int MaxHealth, int AtkPower, int Armor, int MaxStamina, std::string Name) : Character(MaxHealth, AtkPower, Armor, MaxStamina, Name)
{ 

} 


Action Player::ChooseAction()
{
	int Input; 
	while (true) 
	{
		Log::LogMessage(LOG_DEFAULT, "Choose an action! \n1: Attack \n2: Parry \n3: Defend");
		std::cin >> Input;


		if (std::cin.fail() || Input < 1 || Input > 3) 
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			Log::LogMessage(LOG_ERROR, "Invalid Input... Please enter \n1: Attack \n2: Parry \n3: Defend");
		}
		else if (Input == 2 && Stamina == 0)
		{
			Log::LogMessage(LOG_ERROR, "You are exhausted... \nYou cannot Parry until you Defend");
		}
		else
		{
			break;
		}
	
	} 

	Input -= 1;
	return GetActionFromInput(Input); 
}
