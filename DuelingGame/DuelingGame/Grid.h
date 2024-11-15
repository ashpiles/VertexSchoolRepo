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

	void AddItem(std::unique_ptr<GridItem> item);
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
	std::list<std::unique_ptr<GridItem> > items; 
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

/*

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
	Cell* GetCell(Coordinate coordinate);
	void MoveGridItem(GridItem* item, Coordinate coord);
	void AddToGrid(GridItem* item, Coordinate coord);
	Grid();
	~Grid();
private:
	Cell CreateCell(int x, int y);
	void FillMemory(Cell* memory);
	Cell* grid;
	GridMemory memory;
	std::map<Coordinate, int> map;
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
	Coordinate GetPosition() { return position; }
private:
	Coordinate position;
	Cell(int x, int y);
	std::list<GridItem*> componenets;
	friend Grid;
};

// componenet
class GridItem
{
public:
	~GridItem();

	Coordinate GetGridPos();
	Vector2 GetWorldPos();
	void DrawItem();

protected:
	GridItem(GameResource* res);
	GridItem();
	GameResource* resource;

private: 
	Coordinate coord;
	friend Cell;
	friend Grid;
};
 
class Tile : public GridItem
{ 
public:
	~Tile();
	Tile();
	Tile(GameResource* res);
	// need to override the move func
	//void Move(Vector2 dir);
};
*/
 
#endif
