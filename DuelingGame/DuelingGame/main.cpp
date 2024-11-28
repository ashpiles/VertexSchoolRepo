#include <iostream>

#include "Player.h"
#include "Enemy.h"
#include "Grid.h"
#include "UI.h"


// the issue is that i am moving data objs around its getting a little complex
// there are pointer


int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
	const float MoveTimer = 20.0f;
	float moveTimer = 0.0f;

    InitWindow(screenWidth, screenHeight, "Dungeons Dungeons and more Dungeons");

	GameResource playerRes = GameResource("../Resources/knight.png");
	GameResource enemyRes = GameResource("../Resources/gobo.png");
	GameResource tileRes = GameResource("../Resources/tile.png");
	GameResource wallRes = GameResource("../Resources/tile-block.png");
	GameResource arrows = GameResource("../Resources/vectors.png");
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



	deque<Coordinate> prevPath;
	Coordinate begining;
	Coordinate end;

<<<<<<< Updated upstream
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

=======
	deque<MoveAction> path;


	CellSearch<mapped_items> itemMap;

	Coordinate mouseCoord = { 0, 0 };
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
=======
 
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			Vector2 mousePos = GetMousePosition();
			mousePos.x = mousePos.x - (screenWidth / 2);
			mousePos.y = (screenHeight / 2) - mousePos.y;
			cout << floor(mousePos.x / 32) << ", " << floor(mousePos.y / 8) << endl;
			Coordinate pos{ (int)floor(mousePos.x / (TILE_SIZE * 2)) , (int)floor(mousePos.y / (TILE_SIZE * 2))};
			pos.y *= -1;
			pos = pos + player.GetPosition();
			//	cout << pos.x << ", " << pos.y << endl;
			mouseCoord = pos + Coordinate{1, 0};
			path = player.PathFindTo(mouseCoord);
			prevPath.clear();
			begining = player.GetPosition();
			end = mouseCoord;
		}
		else
			mouseCoord = { 0, 0 };

		// Character input stream
		/*
		2 states (in combat or not in combat)
		if within range of enemy enter combat
		when in combat exit update loop
		create a queue of Actions in a turn order
		query players for their turn
		execute actions

		*/
		if (moveTimer > MoveTimer)
		{
			moveTimer = 0;
			if (!path.empty())
			{
				// now suddenly the path can be used by any character wtf
				MoveAction& moveFunc = path.front();
				Coordinate coord = moveFunc.GetCoordinate();
				MoveAction* trace = moveFunc(&player);
				trace->Undo();
				cout << coord.ToString() << endl;
				cout << coord.x << ", " << coord.y << endl;
				prevPath.push_back(player.GetPosition() - coord);
				path.pop_front();
			}
		}
		else
			moveTimer += GetTime();
>>>>>>> Stashed changes

		menue.ListenForInput((KeyboardKey) GetKeyPressed());
		playerPos = player.GetWorldPos();
		camera.target = { playerPos.x + 20.0f, playerPos.y + 20.0f };
<<<<<<< Updated upstream
=======


>>>>>>> Stashed changes
	// Draw
	//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(BLACK);

			BeginMode2D(camera);
 
				Grid::GetCells({ -10, -10 }, { 10, 10 }, &itemMap);

				if (!prevPath.empty())
				{
					
					DrawRectangle(begining.x * TILE_SIZE, begining.y * TILE_SIZE, 16, 16, BLUE); 
					DrawRectangle(end.x * TILE_SIZE, end.y * TILE_SIZE, 16, 16, RED); 
					for (auto const& p : prevPath)
					{
						DrawRectangle(p.x * TILE_SIZE, p.y * TILE_SIZE, 16, 16, Fade(GREEN, 0.5f)); 
					}
				}

				for (auto const& item : itemMap.GetData()["Tile"])
				{
					item->DrawItem();
				}
				for (auto const& item : itemMap.GetData()["Player"])
				{
					item->DrawItem();
				}
<<<<<<< Updated upstream
=======

			
>>>>>>> Stashed changes
				if (menue.IsOpen()) menue.Draw();
	
			EndMode2D(); 

        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();
    
    return 0;
}
