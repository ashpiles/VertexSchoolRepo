#pragma once
#ifndef GRID_H
#define GRID_H
#include <map>
#include <list>
#include <vector>
#include "raylib.h"
#include <memory>
#include <cmath>
#include "GameObject.h"
#include <random>

class Cell;
class GridItem;
class Grid;
class GridMemory;

#define MAX_CELLS 400


struct Coordinate
{
	int x;
	int y;

	bool operator==(const Coordinate& other) const
	{
		return this->x == other.x && this->y == other.y;
	}

	bool operator<(const Coordinate& other) const
	{
        return x < other.x || (x == other.x && y < other.y);
    }

	// Szudzik Pairing
	int Hash()
	{
		int a = x >= 0 ? 2 * x : -2 * x - 1;
		int b = y >= 0 ? 2 * y : -2 * y - 1;
		int c = (a >= b ? a * a + a + b : a + b * b) / 2;

		return x < 0 && y < 0 || x >= 0 && y >= 0 ? c : -c - 1;
	}
};


class Grid final
{
public:
	Grid();
	~Grid();
	static Cell& GetCell(Coordinate coord);
	static std::vector<Cell*> GetCells(Coordinate from, Coordinate to); 
	static std::unique_ptr<Cell> grid;
	void DrawGrid();
private:
	Cell* memory;
	static std::map<int, int> gridMap;

}; 

class Cell final
{
public:
	// add cell needs a template func which converts the item to a unique ptr

	void AddItem(GridItem& item);
	void RemoveItem(GridItem& item);
	std::unique_ptr<GridItem> PopItem(GridItem& item);
	void DrawCell(); // have a flag for grid items to determine if they are to be drawn
	Coordinate GetPosition() { return position; }
	~Cell();

private:
	Cell();
	Cell(int x, int y);
	Cell(Coordinate coord);
	Coordinate position;

	// there needs to be a draw priority on draw items
	std::map<std::string, std::unique_ptr<GridItem> > items; // in the future not a unique ptr but a calling func to the obj
	friend class Grid;
};

/*
I could mke it so that each grid item has it's own unique ptr
that way there is no doubling of items
*/
class GridItem
{
public:
	GridItem();
	GridItem(GameResource* res);
	~GridItem();
	void DrawItem();
	void Move(Coordinate coord);
	const Coordinate GetPosition() { return position; }
	Vector2 GetWorldPos();

	const std::string ID;

private:
	std::string MakeUUID();
	Coordinate position;
    GameResource* resource;
	friend class Cell;

};

class Tile : public GridItem
{
public:
	Tile();
	Tile(GameResource* res);
	~Tile();
};


 
#endif
