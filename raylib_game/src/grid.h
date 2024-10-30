#ifndef TILEGRID_H
#define TILEGRID_H

#include "corelib.h"


// the grid is going to create the empty slots
// store the texture data
// and facilatate movement



class Cell {
    // making these const is too much of a headache

public:
    Texture2D texture;
    Rectangle collision;
    Vector2 gridPosition;
    Vector2 worldPosition;
    Cell(Vector2 gridPos, Vector2 worldPos, Texture2D texp)
        : gridPosition(gridPos), worldPosition(worldPos), texture(texp) {}
    Cell() {}
};

class Grid {
public:
    Cell grid[WORLD_BOUNDS][WORLD_BOUNDS];

    void DrawGrid(){
        for(int y = 0; y < WORLD_BOUNDS; y++)
        {
            for (int x = 0; x < WORLD_BOUNDS; x++)
            {
                DrawTexture(grid[y][x].texture, grid[y][x].worldPosition.x, grid[y][x].worldPosition.y, Fade(WHITE, 0.5f));
            }
        }
    }


    Grid(int cellSize, Texture2D* tex)
        : CellSize(cellSize), TestTex(tex) {

        // loop relies on signed ints, cannot work with 0s
        // [0][WB/4], [WB/4][0]
        // the axis is unfilled
        for (int y = 1; y < WORLD_BOUNDS/4; y++) {
            for (int x = 1; x < WORLD_BOUNDS/4; x++) {

                Vector2 gPosQ1 = Vector2{(float)x, (float) y};
                Vector2 gPosQ2 = Vector2{(float)-x, (float)y};
                Vector2 gPosQ3 = Vector2{(float)-x, (float)-y};
                Vector2 gPosQ4 = Vector2{(float)x, (float)-y};
                grid[y][x]     = Cell(gPosQ1, gPosQ1 * CellSize, *TestTex);
                grid[y*2][x*2] = Cell(gPosQ2, gPosQ2 * CellSize, *TestTex);
                grid[y*3][x*3] = Cell(gPosQ3, gPosQ3 * CellSize, *TestTex);
                grid[y*4][x*4] = Cell(gPosQ4, gPosQ4 * CellSize, *TestTex);
            }
        }
    }

private:
        float CellSize = 32;
        Texture2D* TestTex;
};

#endif
