#include <iostream>
#include <algorithm>

#include "Player.h"
#include "Enemy.h"
#include "Action.h"
#include "Grid.h"
#include "GameObject.h"
#include "UI.h"

#include "raylib.h"

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

	list<Tile> tiles;
	for (int y = -10; y < 10; y++)
	{
		for (int x = -10; x < 10; x++)
		{
			tiles.emplace_back(Coordinate{x, y}, &tileRes);
		}
	}

	Player player("hero", playerStats, {0, 0}, &playerRes);

	Camera2D camera = { 0 };
	Vector2 playerPos = player.GetWorldPos();
	camera.target = { playerPos.x + 20.0f, playerPos.y + 20.0f };
	camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
	camera.rotation = 0.0f;
	camera.zoom = 2.0f;
	Menue menue = Menue(&playerPos);
	menue.anchorOffset = { (screenWidth / 8), -(screenHeight / 5)};
    SetTargetFPS(60); 


	ItemFunc drawTiles = [](list<int> indecies) -> list<GridItem*>{ 

		list<GridItem*> items; 
		GridItem* item;

		for (int index : indecies)
		{
			item = Grid::GetItem(index);
			if (item->GetDrawOrder() <= 1)
				item->DrawItem();
			else
				items.push_back(item);
		}
		return items;
	};

	while (!WindowShouldClose())
	{
		// Update
		//---------------------------------------------------------------------------------- 
		Vector2 movement = {0, 0};
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

				list<GridItem*> next = Grid::GetCells({ -10, -10 }, { 10, 10 }, drawTiles);
				for (auto const& item : next)
				{
					item->DrawItem();
				}
				if (menue.IsOpen()) menue.Draw();
	
			EndMode2D(); 

        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();
    
    return 0;
}
