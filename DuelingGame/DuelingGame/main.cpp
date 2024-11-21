#include <iostream>
#include <algorithm>

#include "Player.h"
#include "Enemy.h"
#include "Action.h"
#include "Grid.h"
#include "GameObject.h"
#include "UI.h"

#include "raylib.h"

#define MAX_BATCH_ELEMENTS 8192


// the issue is that i am moving data objs around its getting a little complex
// there are pointer 

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Dungeons Dungeons and more Dungeons");

	GameResource playerRes = GameResource("../Resources/knight.png");
	GameResource enemyRes = GameResource("../Resources/gobo.png");
	GameResource tileRes = GameResource("../Resources/tile.png");
	GameResource wallRes = GameResource("../Resources/tile-block.png");
	CharacterStats playerStats = {
		.maxHealth = 5,
		.health = 5,
		.atkPower = 2,
		.armor = 2,
		.maxStamina = 5,
		.stamina = 5 
	};
	CharacterStats enemyStats = {
		.maxHealth = 2,
		.health = 2,
		.atkPower = 1,
		.armor = 1,
		.maxStamina = 2,
		.stamina = 2 
	}; 


	Grid grid = Grid();
	std::vector<Tile> tiles;
	for (auto& i : Grid::GetCells({ -10, -10 }, { 10, 10 }))
	{
		Coordinate coord = i->GetPosition();
		if (std::abs(coord.x) >= 9 || std::abs(coord.y) >= 10 )
		{
			tiles.push_back(Tile(&wallRes, 2));
		}
		else
		{
			tiles.push_back(Tile(&tileRes));
		}
		i->AddItem((tiles.back()));
	}
	
	Player player("hero", playerStats, &playerRes);
	Enemy enemy("gobo", enemyStats, &enemyRes);

	Grid::GetCell({ 0, 0 }).AddItem(player);
	Grid::GetCell({ 1, 0 }).AddItem(enemy); 

	Vector2 playerPos = player.GetWorldPos();
	Camera2D camera = { 0 };
	camera.target = { playerPos.x + 20.0f, playerPos.y + 20.0f };
	camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
	camera.rotation = 0.0f;
	camera.zoom = 2.0f;
	Menue menue = Menue(&playerPos);
	menue.anchorOffset = { (screenWidth / 8), -(screenHeight / 5)};
    SetTargetFPS(60); 

	bool menueOpen = false;

	// loops 4ever
//	Grid::PathFindTo({ 0,0 });

    while (!WindowShouldClose())
    {
        // Update
        //---------------------------------------------------------------------------------- 
		Vector2 movement = { 0, 0 };
		if (menue.IsOpen() == false) 
		{ 
			if		(IsKeyDown(KEY_D)) player.Move({  1, 0 });
			else if (IsKeyDown(KEY_A)) player.Move({ -1, 0 });
			if		(IsKeyDown(KEY_W)) player.Move({ 0, -1 });
			else if (IsKeyDown(KEY_S)) player.Move({ 0, 1 }); 
		}

		menue.ListenForInput((KeyboardKey) GetKeyPressed());
		playerPos = player.GetWorldPos();
		camera.target = { playerPos.x + 20.0f, playerPos.y + 20.0f }; 
	
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
			BeginMode2D(camera);

				grid.DrawGrid();
				if (menue.IsOpen()) menue.Draw();
	
			EndMode2D(); 

        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();
    
    return 0;
}
