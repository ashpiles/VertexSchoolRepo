#include <iostream>
#include <algorithm>

#include "Player.h"
#include "Enemy.h"
#include "Action.h"
#include "Grid.h"
#include "GameObject.h"

#include "raylib.h"

#define MAX_BATCH_ELEMENTS 8192


// the issue is that i am moving data objs around its getting a little complex
// there are pointer 

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
	std::vector<Tile> tiles;
	for (auto& i : Grid::GetCells({ -5,-5 }, { 5,5 }))
	{
		tiles.push_back(Tile(&tileRes));
		i->AddItem(std::make_unique<Tile>(tiles.back()));
	}
	
	Player player("hero", playerStats, &playerRes);

	Grid::GetCell({ 0, 0 })
		.AddItem(std::make_unique<Player>(player));


	Vector2 playerPos = player.GetWorldPos();
	Camera2D camera = { 0 };
	camera.target = { playerPos.x + 20.0f, playerPos.y + 20.0f };
	camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
	camera.rotation = 0.0f;
	camera.zoom = 2.0f;
    SetTargetFPS(60);


	float timer = 0;


    while (!WindowShouldClose())
    {
        // Update
        //---------------------------------------------------------------------------------- 
		Vector2 movement = { 0, 0 };
		if (IsKeyDown(KEY_D)) player.Move({ 1,0 });
		else if (IsKeyDown(KEY_A)) player.Move({-1, 0});
		if (IsKeyDown(KEY_W)) player.Move({ 0, 1 });
		else if (IsKeyDown(KEY_S)) player.Move({0, -1});


		playerPos = player.GetWorldPos();
		camera.target = { playerPos.x + 20.0f, playerPos.y + 20.0f };
 
	
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
			BeginMode2D(camera);

				grid.DrawGrid();
	
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
