#include "Grid.h"
#include <iostream>
#include <algorithm>


// Grid
/*=========================================================================================*/
//NOTES:
/*
it would be cool if the get functions can take an extra function so that the items can be
itterated over and allow for some functional programming.

that would make all of this structure cooler / worth while
*/

list<GridItem*> Grid::GetCell(Coordinate pos, ItemFunc func)
{
	auto defaultFunc = [](list<int> indecies){ 
		list<GridItem*> items_;
		for (int i : indecies)
			items_.push_back(Grid::Items[i]);

		return items_; 
	};

	list<GridItem*> items;
	if (GridMap.contains(pos.Hash()))
	{
		if (func != nullptr)
			items.splice(items.end(), func(GridMap[pos.Hash()]));
		else
			items.splice(items.end(), defaultFunc(GridMap[pos.Hash()]));
	} 
	return items;
}

list<GridItem*> Grid::GetCells(Coordinate from, Coordinate to, ItemFunc func) 
{
	list<GridItem*> items; 

	// Magnitude
	int yDiff = abs(to.y - from.y) + 1; 
	int xDiff = abs(to.x - from.x) + 1; 

	// Direction
	int xDir = (to.x > from.x) ? 1 : (to.x < from.x) ? -1 : 0;
	int yDir = (to.y > from.y) ? 1 : (to.y < from.y) ? -1 : 0;

	for (int y = 0; y < yDiff; y++)
	{
		for (int x = 0; x < xDiff; x++)
		{
			Coordinate coord = {
				from.x + x * xDir,
				from.y + y * yDir
			};

			list<GridItem*> cell = GetCell(coord, func);
			items.insert(items.end(), cell.begin(), cell.end());
		}
	}

	return items;
}


map<int, list<int> > Grid::GridMap;
map<string, int> Grid::IDMap;
GridItem* Grid::Items[MAX_ITEMS];
int Grid::itemCount = 0;
map<int, bool> Grid::isItemFree;

// GridItem
/*=========================================================================================*/
GridItem::GridItem(Coordinate coord) : ID(MakeUUID()), coordinate(coord)
{
	memoryIndex = Grid::itemCount;
	Grid::Items[Grid::itemCount] = this;
	Grid::isItemFree[Grid::itemCount] = false;
	Grid::GridMap[coord.Hash()].push_back(Grid::itemCount);
	Grid::itemCount++;
}

GridItem::~GridItem()
{
	Grid::Items[memoryIndex] = nullptr;
	Grid::isItemFree[memoryIndex] = true;
}

void GridItem::Move(Coordinate coord)
{
	Grid::GridMap[coordinate.Hash()].remove(memoryIndex);
	coordinate.x += coord.x;
	coordinate.y += coord.y;
	Grid::GridMap[coordinate.Hash()].push_back(memoryIndex);
}

string GridItem::MakeUUID()
{
	static random_device dev;
    static mt19937 rng(dev());

    uniform_int_distribution<int> dist(0, 15);

    const char *v = "0123456789abcdef";
    const bool dash[] = { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 };

    string res;
    for (int i = 0; i < 16; i++)
	{
        if (dash[i]) res += "-";
        res += v[dist(rng)];
        res += v[dist(rng)];
    }
    return res;
} 

// Tile
/*=========================================================================================*/
Tile::Tile(Coordinate coord, GameResource* res) : GridItem(coord)
{
	resource = res;
	drawOrder = 1;
	collisionMask = 0b0;
}

Tile::~Tile()
{
	
}

void Tile::DrawItem()
{
	DrawTextureV(resource->GetTexture(), { (float) coordinate.x * TILE_SIZE, (float) coordinate.y * TILE_SIZE }, WHITE);
}


