#pragma once
#ifndef GRID_H
#define GRID_H
#include <map>
#include <list>
#include <vector>
#include <cmath>
#include "GameObject.h"
#include <random> 

using namespace std;

class Grid;
class GridItem;
#define MAX_CELLS 400
#define TILE_SIZE 16
#define MAX_ITEMS 1000


typedef list<GridItem*> (*ItemFunc)(list<int>);

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

	static Coordinate ReverseHash(int hash)
	{
		int abs = hash % 2 == 0 ? hash : -(hash + 1);
		int z = static_cast<int>(floor(sqrt(2.0 * abs)));
		int w = abs - (z * (z + 1)) / 2; // triangular number

		int a = z >= w ? z : w;
		int b = z >= w ? w : z;

		int x = a % 2 == 0 ? a / 2 : -(a + 1) / 2;
		int y = b % 2 == 0 ? b / 2 : -(b + 1) / 2;

		if (hash % 2 == 0)
		{
			x = -x;
			y = -y;
		}

		return Coordinate{ 0, 0 };
	}
};

class Grid final
{
public:
	static list<GridItem*> GetCell(Coordinate pos, ItemFunc func = nullptr);
	static list<GridItem*> GetCells(Coordinate from, Coordinate to, ItemFunc func = nullptr);
	static GridItem* GetItem(int index) { return Items[index]; }
private:
	
	static map<int, list<int> > GridMap;
	static map<string, int> IDMap;
	static GridItem* Items[MAX_ITEMS];
	static int itemCount;
	static map<int, bool> isItemFree;
	
	friend class GridItem;
}; 
 
/// <summary>
/// Game resource accessible by the Grid
/// allows for simple behaviours
/// constructor allocates onto the heap, accessible via uuid
/// </summary>
class GridItem
{
public:
	~GridItem();
	virtual void DrawItem() = 0;
	void Move(Coordinate coord);
	uint16_t GetDrawOrder() { return drawOrder; }
	uint16_t GetCollisionMask() { return collisionMask; }

	const string ID;
private:
	string MakeUUID();
	int memoryIndex;

protected: 
	GridItem(Coordinate coord);

	uint16_t collisionMask;
	uint16_t drawOrder;
	GameResource* resource;
	Vector2 position;
	Coordinate coordinate = { 0 , 0 };
	friend class Cell;
};


class Tile : public GridItem
{
public:
	Tile(Coordinate coord, GameResource* res);
	~Tile();
	void DrawItem();

};

#endif
