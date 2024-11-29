#pragma once
#include "Coordinate.h"
#define MAX_CELLS 400
#define TILE_SIZE 16
#define MAX_ITEMS 1000 

class Grid;

class GridItem
{
public:
	virtual ~GridItem();
	void Move(Coordinate coord);
	void MoveTo(Coordinate coord);
	virtual void DrawItem() = 0;
	virtual void Update() = 0;


	Coordinate GetPosition();

	const std::string ID;
private:
	std::string MakeUUID();
	int memoryIndex;
	friend Grid;

protected: 
	GridItem(Coordinate coord); 
	Coordinate coordinate;
}; 


