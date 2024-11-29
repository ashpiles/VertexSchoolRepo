#include "Grid.h"
#include "raylib.h"
#include <random> 
#include <cmath>


GridItem* Grid::GetItem(int index)
{
	return Items[index];
}

std::list<Coordinate> Grid::GetCoords(Coordinate from, Coordinate to) 
{
	std::list<Coordinate> coords; 

	// Magnitude
	Coordinate diff = Coordinate::Magnitude(to, from);
	diff = diff + Coordinate{1, 1};

	// Direction
	int xDir = (to.x > from.x) ? 1 : (to.x < from.x) ? -1 : 0;
	int yDir = (to.y > from.y) ? 1 : (to.y < from.y) ? -1 : 0;

	for (int y = 0; y < diff.y; y++)
	{
		for (int x = 0; x < diff.x; x++)
		{
			Coordinate coord = {
			from.x + x * xDir,
			from.y + y * yDir
			};

			if(GridMap.contains(coord.Hash()))
				coords.push_back(coord);
		}
	}

return coords;
} 

void DebugPathFinding()
{
	std::vector<Coordinate> prevSqr;
	bool pathPrintGate = false;
	bool moveGate = false;
	if (!Grid::vField.empty() )
	{ 
		Rectangle source = { 0, 0, 16, 16 };
		Rectangle dest = { 0, 0, 16, 16 };
		for (auto const& pair : Grid::vField)
		{ 
			//cout << Coordinate::ReverseHash(pair.first).ToString() << " : " << Coordinate::ReverseHash(pair.second).ToString() << endl;
			//cout << Coordinate::ReverseHash(pair.second).ToString() << " : " << to_std::string(pair.second) << endl;
			switch (pair.second)
			{
			case 1:
				// south west 
				source.x = 48; 
				source.y = 0;
			case 2:
				// north
				source.x = 0;
				source.y = 0;
				break;
			case 3:
				// east
				source.x = 16;
				source.y = 16;
				break;
			case 4:
				// north east
				source.x = 32;
				source.y = 0;
				break;
			case -1:
				// south
				source.x = 0;
				source.y = 0;
				break;
			case -2:
				// west
				source.x = 0;
				source.y = 16;
				break;
			case -3:
				// north west
				source.x = 32;
				source.y = 16;
				break;
			case -4:
				// south east
				source.x = 48;
				source.y = 16;
				break;
			}
			Vector2 newDest = { 0, 0 };//Coordinate::ReverseHash(pair.first).Scale(TILE_SIZE);
			dest.x = newDest.x;
			dest.y = newDest.y;
			//DrawTexturePro(arrows.GetTexture(), source, dest, { 0, 0 }, 0.0f, Fade(WHITE, 0.5f));
		}
		//pathPrintGate = false;
	}

	if (!prevSqr.empty())
	{ 
		for (auto const& sqr : prevSqr)
		{
			DrawRectangle(sqr.x * TILE_SIZE, sqr.y * TILE_SIZE, 16, 16, Fade(GREEN, 0.5f));
		}

	}

} 

std::map<int, std::list<int> > Grid::GridMap;
std::map<std::string, int> Grid::IDMap;
GridItem* Grid::Items[MAX_ITEMS];
int Grid::itemCount = 0;
std::map<int, bool> Grid::isItemFree;

std::map<long, long> Grid::vField; 

