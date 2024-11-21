#pragma once
#ifndef GRID_H
#define GRID_H
#include <map>
#include <list>
#include <vector>
#include <queue>
#include <memory>
#include <cmath>
#include "GameObject.h"
#include <random>
#include <typeinfo>

class Grid;
class Cell;
class GridItem;

#define MAX_CELLS 400
#define TILE_SIZE 16

using namespace std;

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


	Cell* GetCell(Coordinate pos);
	vector<Cell*> GetCells(Coordinate from, Coordinate to);
private:
	// coord : uuid, type or property
	
	static map<int, Cell* > GridMap;
};


class Cell final
{
public:
	Cell(Coordinate coord);
	~Cell();
	GridItem* GetItem(string id);
	vector<GridItem*> GetItems();
	vector<GridItem*> GetByType(size_t type);
	void AddItem(string id);
	void RemoveItem(string id);

	const Coordinate coordinate;
private:
	map<string, GridItem*> IDMap;
	map<size_t, string> typeMap;
};




/// <summary>
/// Game resource accessible by the Grid
/// allows for simple behaviours
/// constructor allocates onto the heap, accessible via uuid
/// </summary>
class GridItem
{
public:
	virtual void DrawItem() = 0;
	virtual void Move() = 0;

	const string ID;
private:
	GridItem();
	~GridItem();
	string MakeUUID();

	static map<string, unique_ptr<GridItem> > ItemTable;
	friend class Cell;
protected: 

	uint16_t collisionMask;
	uint16_t drawOrder;
	GameResource* resource;
};

class Tile : GridItem
{ };
/*class Grid final
{
public:
	Grid();
	~Grid();
	static Cell& GetCell(Coordinate coord); // should get via id
	static vector<Cell*> GetCells(Coordinate from, Coordinate to); 
	static unique_ptr<Cell> grid;
	static void PathFindTo(Coordinate coord);
	void DrawGrid();
	// should use remote cont to move a grid item with its move function?
private:
	Cell* memory;
	static map<int, int> gridMap;

}; 


class Cell final
{
public:
	// add cell needs a template func which converts the item to a unique ptr

	void AddItem(GridItem* item);
	void RemoveItem(GridItem* item);
	unique_ptr<GridItem> PopItem(GridItem& item);
	void DrawCell(); // have a flag for grid items to determine if they are to be drawn
	Coordinate GetPosition() { return position; }
	~Cell();

private:
	Cell();
	Cell(int x, int y);
	Cell(Coordinate coord);
	Coordinate position;

	// there needs to be a draw priority on draw items
	map<string, GridItem* > items; 
	friend class Grid;
};

class GridItem
{
public:
	virtual GridItem Create(Coordinate coord) = 0; // makes the item
	virtual void DrawItem() = 0;
	virtual void Move(Coordinate coord) = 0;
	const Coordinate GetPosition() { return position; }
	int GetCollisionLayer() { return collisionLayer; }
	Vector2 GetWorldPos(); 
	const string ID;

protected: 
	GridItem();
	GridItem(GameResource* res);
	~GridItem();
	int renderDepth = 0;
	int collisionLayer = 0; // should make an unisgned bit mask
	const float moveTimerMax = 50;
	float moveTimer = 0;
	Coordinate position;
    GameResource* resource;

private:
	string MakeUUID();
	friend class Cell; 
};

// need to get position inside tile
class Tile : virtual public GridItem
{
public:
	Tile();
	Tile(GameResource* res); 
	Tile(GameResource* res, int colLayer);
	~Tile();

	void DrawItem();
	void Move(Coordinate coord);
};

*/
 
#endif
