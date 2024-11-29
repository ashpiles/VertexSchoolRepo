
#include "GridItem.h"
#include "Grid.h"
#include <random>

GridItem::GridItem(Coordinate coord) : ID(MakeUUID()), coordinate(coord)
{
    memoryIndex = Grid::itemCount;
    Grid::Items[Grid::itemCount] = this;
    Grid::isItemFree[Grid::itemCount] = false;
    Grid::GridMap[coordinate.Hash()].push_back(Grid::itemCount);
    Grid::itemCount++; 
}

// this will not automatically clean up the grid mem
GridItem::~GridItem()
{
    Grid::Items[memoryIndex] = nullptr;
    Grid::isItemFree[memoryIndex] = true;
}

void GridItem::Move(Coordinate coord)
{
    Grid::GridMap[coordinate.Hash()].remove(memoryIndex); 
    coordinate = coordinate + coord;
    Grid::GridMap[coordinate.Hash()].push_back(memoryIndex);
}

// Move to literall coordinate location
void GridItem::MoveTo(Coordinate coord)
{
    Grid::GridMap[coordinate.Hash()].remove(memoryIndex); 
    coordinate = coord;
    Grid::GridMap[coordinate.Hash()].push_back(memoryIndex);
}
 
Coordinate GridItem::GetPosition() { return coordinate; }

std::string GridItem::MakeUUID()
{
	static std::random_device dev;
    static std::mt19937 rng(dev());

    std::uniform_int_distribution<int> dist(0, 15);

    const char *v = "0123456789abcdef";
    const bool dash[] = { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 };

    std::string res;
    for (int i = 0; i < 16; i++)
	{
        if (dash[i]) res += "-";
        res += v[dist(rng)];
        res += v[dist(rng)];
    }
    return res;
} 
