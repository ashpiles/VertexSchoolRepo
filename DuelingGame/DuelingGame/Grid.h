#pragma once
#ifndef GRID_H
#define GRID_H
#include <map>
#include <list>
#include "raylib.h"
#include <memory>
#include "GameObject.h"


class Cell;
class GridItem;
class Grid;
class GridMemory;

#define MAX_CELLS 100


/*
Grid Memory is where things are placed to be used. This is memory being used.
The memory allocated then is not to be disallocated until the end of the program.
*/
class GridMemory final
{ 
private:
	GridMemory();
	~GridMemory();
	Cell* gridMemory;
	friend Grid;
};


class Grid final
{
public:
	static Cell* GetCell(Vector2 coordinate);
	Grid();
	~Grid();
private:
	Cell CreateCell(int x, int y);
	void FillMemory(Cell* memory);
	static std::unique_ptr<Cell> grid;
	GridMemory memory;
};



// composite
class Cell final
{
public:
	Cell();
	~Cell();

	void AddItem(GridItem* item);
	void RemoveItem(GridItem* item);
	void DrawCell(); // grid items should have a "draw flag" to signify what should and shouldn't be drawn
private:
	Vector2 position; // is possible to change position; try and make this unchanging
	Cell(int x, int y);
	std::list<GridItem*> componenets;
	friend Grid;
};

// componenet
class GridItem
{
public:
	~GridItem();

	void Move(Vector2 dir); 
	Vector2 GetGridPos();
	Vector2 GetWorldPos();
	void DrawItem();


protected:
	GridItem(Vector2 position, GameResource* res);
	GridItem(Cell* parent, GameResource* res); 
	GameResource* resource;
	Vector2* position;

private: 
	Cell* parent;
	friend Cell;
};
 
// tiles need to work in a way that makes it so only one tile per cell can be placed
class Tile : protected GridItem
{ 
public:
	~Tile();
	Tile(Vector2 dir, GameResource* res);
	Tile(Cell* cell, GameResource* res);
	// need to override the move func
	//void Move(Vector2 dir);
};
 






/* I am going to have to localize position to the tile
// and have some tile origin shennigans stuff going on prbly

// locate the player onto the center of the square
// vertex is the orginal position
// the other verticies are just the other tile width and height added

// need to use the texturedrawpro
class Grid;

// turn a tile into a fly weight mebe
class Tile {

protected:
	Texture2D* texturePtr;
	Grid* parent;

public: 
	std::string path; 
	
	Tile();

	~Tile();

private:
	friend class Grid;

	Vector2 coords;

	Tile(Texture2D* tex, Grid* grid, Vector2 coords)
		: texturePtr(tex), parent(grid), path("../Resources/tile.png"), coords(coords) {}

};

// tiles can be flyweights 
class Grid {
	// a tile is a resource
	// the grid is just a matrix of tiles

	// all you need is the size of the tile and you have a grid
	// what I need to do is load tile data in and out
	// all tiles must have neighbors
private:
	Texture2D tex;

public: 
	Tile CreateTile(Texture2D *tex, int x, int y);
	Tile *GetTile(int x, int y);
	void DrawGrid(); 

	void Localize(Shape2D &object);
	void Move(Shape2D &object, Vector2 distance);
	Grid();


protected:
	~Grid();
	static const int width = 10;
	static const int height = 10;
	static const int tileSize = 32;
	std::map < std::tuple<int, int>, Tile*> map;
	Tile data[height][width];
	// it might be best to hash the coordinates
	
};
*/

#endif