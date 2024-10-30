#include "corelib.h"
#include "tile_grid.h"

int main() {
	const int scrWidth = 800;
	const int scrHeight = 450;
    const int assetScalar = 3;

	InitWindow(scrWidth, scrHeight, "raylib");

    Image imOrigin = LoadImage("res/costco_guys.png");
    ImageFormat(&imOrigin, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    Texture2D guy = LoadTextureFromImage(imOrigin);



    std::cout << "before makign grid" << std::endl;
    int frameWidth = guy.width;
    int frameHeight = guy.height;

	Rectangle screen = {0.0f, 0.0f, scrWidth, scrHeight};
    Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
    Rectangle destRec = { scrWidth/2.0f, scrHeight/2.0f, frameWidth*2.0f, frameHeight*2.0f };
    Vector2 origin = { (float)frameWidth, (float)frameHeight };

    Image tileOrigin = LoadImage("res/test_tile");
    ImageFormat(&tileOrigin, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    Texture2D tile = LoadTextureFromImage(tileOrigin);

    TileGrid grid();

    int rotation = 0;


	Camera2D camera = {0};
	camera.target = (Vector2){ destRec.x + 20.0f, destRec.y + 20.0f };
	camera.offset = (Vector2){ scrWidth/2.0f, scrHeight/2.0f };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	int width = 960;
	int height = 480;

    UnloadImage(imOrigin);
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		// Update

		if (IsKeyDown(KEY_D)) destRec.x += 2;
		else if (IsKeyDown(KEY_A)) destRec.x -= 2;
		if (IsKeyDown(KEY_W)) destRec.y -= 2;
		else if (IsKeyDown(KEY_S)) destRec.y += 2;

		camera.target = (Vector2){ destRec.x, destRec.y};
		// Draw
		BeginDrawing();
		ClearBackground(RAYWHITE);
            BeginMode2D(camera);

                DrawTexturePro(guy, sourceRec, destRec, origin, float(rotation), WHITE);
                grid.DrawGrid();

            EndMode2D();

		EndDrawing();
	}
    UnloadTexture(guy);
	CloseWindow();
	return 0;
}


/*================================================================================
TODO:
[_] large grid to place textures on
[_] grid based movement
[_] create menue


================================================================================*/


