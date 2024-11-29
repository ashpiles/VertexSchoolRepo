#pragma once
#ifndef GRID_H
#define GRID_H
#include "CellSearch.h"



class Grid;
class GridItem;
struct Coordinate;

class Grid final
{ 
public:
	template<typename T>
	static void GetCell(Coordinate pos, CellSearch<T>& func)
	{ 
		if (GridMap.contains(pos.Hash()))
		{
			func(GridMap[pos.Hash()]);
		} 
	}

	template<typename T>
	static void GetCells(Coordinate from, Coordinate to, CellSearch<T>& func) 
	{

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

				GetCell<T>(coord, func);
			}
		} 
	}

	static std::list<Coordinate> GetCoords(Coordinate from, Coordinate to);

	static GridItem* GetItem(int index);
	static std::map<long, long> vField; 
	static void DebugPathFinding();


private:
	
	static std::map<int, std::list<int> > GridMap;
	static std::map<std::string, int> IDMap;
	static GridItem* Items[MAX_ITEMS];
	static int itemCount;
	static std::map<int, bool> isItemFree; 

	friend GridItem;
}; 
 
#endif
