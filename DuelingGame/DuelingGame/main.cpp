#include <iostream>
#include "Log.h"
#include "Action.h"
#include "Player.h"
#include "Enemy.h"

void HandleActions(Player& player, Enemy& enemy);

int main()
{
	
	Player player(5, 2, 2, 2, "Hero");
	Enemy enemy(1, 1, 0, 1, "Goblin");
	int roundNumber = 1;

	while (player.GetIsAlive())
	{
		Log::Separartor();
		Log::LogMessage(LOG_DEFAULT, "Round " + std::to_string(roundNumber));
		Log::Separartor();
		Log::NewLine();

		HandleActions(player, enemy);
		if (!enemy.GetIsAlive()) 
		{


			roundNumber += 1;


			if (roundNumber > 5)
			{
				Log::LogMessage(LOG_INFO, "Our Hero has defeated all his opponents and is now champion of the arena !!!");
				break;
			}
			Log::LogMessage(LOG_DEFAULT, enemy.GetName() + " has been defeated by our Hero! A new stronger enemy appears");
			Log::NewLine();




			enemy.IncreaseDifficulty(roundNumber);
			Log::LogMessage(LOG_WARNING, enemy.GetName() + " enters the fray!");
			Log::NewLine();
			player.InitStats();
			Log::LogMessage(LOG_INFO, " Our Hero Recovers his stamina and energy ready for a new round!");


		}
	}


	if (!player.GetIsAlive())
	{
		Log::LogMessage(LOG_ERROR, "Our Hero has perished! You must try again!");
	
	}


	Log::LogMessage(LOG_INFO, "Thanks for playing!");
	return 0;

} 

/*
The action is given the value
it can be a composite design prblm
*/

// work on fusing this with the action look up table for more implicit logic
void HandleActions(Player& player, Enemy& enemy) 
{
	Action playerAction = player.ChooseAction();
	Action enemyAction = enemy.ChooseAction();

	Log::NewLine();
	Log::LogMessage(LOG_DEFAULT, "Player " + playerAction.str + "s");
	Log::LogMessage(LOG_DEFAULT, "Enemy " + enemyAction.str + "s");
	Log::NewLine();

	//playerAction.ProcessActions(&enemyAction);
	//enemyAction.ProcessActions(&enemyAction);

	switch (playerAction.type)
	{
	case ATTACK: 
		switch (enemyAction.type)
		{ 

		case ATTACK:
			Log::LogMessage(LOG_DEFAULT, "Its a clash... The weapons ring as they hit each other");
			break; 

		case PARRY:
			Log::LogMessage(LOG_ERROR, enemy.GetName() + " parries the attack! Oh no our hero is struck!");
			player.UpdateHealth(-(enemy.GetAtkPower() * 2));
			break;


		case DEFEND:
			Log::LogMessage(LOG_WARNING, enemy.GetName() + " Is defending! The attack is less successful!");
			enemy.UpdateHealth(-(player.GetAtkPower() / 2));
			break;
		}
		break;


	case PARRY:


		switch (enemyAction.type)
		{
		case ATTACK:
			Log::LogMessage(LOG_INFO, "Our Hero masterfully parries! " + enemy.GetName() + " Takes double damage!");
			enemy.UpdateHealth(-(player.GetAtkPower() * 2));
			break;


		case PARRY:
			Log::LogMessage(LOG_DEFAULT, "Both combatants drain reduce their stamina!");
			break;
		case DEFEND:
			Log::LogMessage(LOG_DEFAULT, "Our Hero misreads the tell and drains his stamina, the enemy recovers!");
			break;
		}
		break;


	case DEFEND:
		switch (enemyAction.type)
		{
		case ATTACK:
			Log::LogMessage(LOG_WARNING, "Our Hero Is defending! " + enemy.GetName() + "'s is less successful!");
			player.UpdateHealth(-(enemy.GetAtkPower() / 2));
			break;


		case PARRY:
			Log::LogMessage(LOG_DEFAULT, "The enemy misreads the tell and drains his stamina, our hero recovers!");
			break;
		case DEFEND:
			Log::LogMessage(LOG_INFO, "Both combatants are recovering energy!");
			break;
		}
		break;
	}


	Log::NewLine();


}