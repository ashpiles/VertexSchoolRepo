#pragma once
#ifndef TILE_GRID_H
#define TILE_GRID_H
#include "corelib.h"


struct Tile {
    Texture2D texture;
    Rectangle source;
    Rectangle destination;
};

class TileGrid {
public:
    TileGrid();
    void DrawGrid();
private:
    Tile grid[WORLD_BOUNDS][WORLD_BOUNDS];
};

#endif
