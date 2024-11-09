#include <iostream>

#include "Player.h"
#include "Enemy.h"
#include "Action.h"
#include "Grid.h"
#include "GameObject.h"

#include "raylib.h"

#define MAX_BATCH_ELEMENTS 8192

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Dungeons Dungeons and more Dungeons");

	GameResource playerRes = GameResource("../Resources/gobo.png");
	GameResource tileRes = GameResource("../Resources/tile.png");
	CharacterStats playerStats = {
		.maxHealth = 5,
		.health = 5,
		.atkPower = 2,
		.armor = 2,
		.maxStamina = 5,
		.stamina = 5 
	};

	Grid grid = Grid();

	for (int i = 0; i < 10; i++)
	{
		Vector2 dir = {5, i};
		Tile tile(dir, &tileRes);
	}

	Player player("Hero", playerStats, Vector2{0,0}, &playerRes);

	Vector2 playerPos = player.GetWorldPos();
	Camera2D camera = { 0 };
	camera.target = { playerPos.x + 20.0f, playerPos.y + 20.0f };
	camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;
    SetTargetFPS(60);


	float timer = 0;


    while (!WindowShouldClose())
    {
        // Update
        //---------------------------------------------------------------------------------- 
		timer += GetFrameTime();
		if (timer >= 1.2) { 
			Vector2 movement = { 0, 0 };
			if      (IsKeyDown(KEY_D)) movement.x += 2;
			else if (IsKeyDown(KEY_A)) movement.x -= 2;
			if      (IsKeyDown(KEY_W)) movement.y -= 2;
			else if (IsKeyDown(KEY_S)) movement.y += 2;
			timer = 0;
		}


		//camera.target = { player.Position.x + 20.0f, player.Position.y + 20.0f };
 
		camera.zoom += ((float)GetMouseWheelMove() * 0.05f);

		if (camera.zoom > 3.0f) camera.zoom = 3.0f;
		else if (camera.zoom < 0.1f) camera.zoom = 0.1f;

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
			BeginMode2D(camera);

			for (int x = 0; x < 10; x++)
			{
				//Cell* cell  = Grid::GetCell({5, (float) x}); 
				//cell->DrawCell();
			}

			//	DrawRectangleRec(player.GetHitbox(), RED);
				//Rectangle rect = player.GetHitbox();

			EndMode2D();


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();
    //--------------------------------------------------------------------------------------

    return 0;
}




/*
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


The action is given the value
it can be a composite design prblm


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
*/