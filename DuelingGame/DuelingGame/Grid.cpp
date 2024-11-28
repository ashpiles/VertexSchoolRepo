#include "Grid.h"
#include <random> 


//// Grid
/*=========================================================================================*/
//NOTES::
/*
it would be cool if the get functions can take an extra function so that the items can be
itterated over and allow for some functional programming.

that would make all of this structure cooler / worth while
*/

template<typename T>
void Grid::GetCell(Coordinate pos, CellSearch<T>* func)
{ 
	if (GridMap.contains(pos.Hash()))
	{
		func(GridMap[pos.Hash()]);
	} 
}

template<typename T>
void Grid::GetCells(Coordinate from, Coordinate to, CellSearch<T>* func) 
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
<<<<<<< Updated upstream

	return items;
}
=======
 } 

list<Coordinate> Grid::GetCoords(Coordinate from, Coordinate to) 
{
	list<Coordinate> coords; 

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
>>>>>>> Stashed changes

void DebugPathFinding()
{
	vector<Coordinate> prevSqr;
	bool pathPrintGate = false;
	bool moveGate = false;
	if (!Grid::vField.empty() )
				{ 
					Rectangle source = { 0, 0, 16, 16 };
					Rectangle dest = { 0, 0, 16, 16 };
					for (auto const& pair : Grid::vField)
					{ 
						//cout << Coordinate::ReverseHash(pair.first).ToString() << " : " << Coordinate::ReverseHash(pair.second).ToString() << endl;
						//cout << Coordinate::ReverseHash(pair.second).ToString() << " : " << to_string(pair.second) << endl;
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
						Vector2 newDest = Coordinate::ReverseHash(pair.first).Scale(TILE_SIZE);
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


map<int, list<int> > Grid::GridMap;
map<string, int> Grid::IDMap;
GridItem* Grid::Items[MAX_ITEMS];
int Grid::itemCount = 0;
map<int, bool> Grid::isItemFree;

map<long, long> Grid::vField;

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

<<<<<<< Updated upstream
=======
// Move to literall coordinate location
void GridItem::MoveTo(Coordinate coord)
{
	Grid::GridMap[coordinate.Hash()].remove(memoryIndex);
	coordinate.x = coord.x;
	coordinate.y = coord.y;
	Grid::GridMap[coordinate.Hash()].remove(memoryIndex);
}

// might be best to seperate this into a different class
// and allow for injecting functions via remote controll for the different entity types 

// fails when clicking out of range of the grid
deque<MoveAction> GridItem::PathFindTo(Coordinate goal)
{
	deque<MoveAction> path;
	vector<Coordinate> frontier;
	map<int, Coordinate> cameFrom;
	map<int, int> distance;

	frontier.push_back(coordinate);
	cameFrom[coordinate.Hash()] = { 0, 0 };

	while (!frontier.empty())
	{
		Coordinate current = frontier.back();
		Coordinate n_back  = { current.x - 1, current.y - 1 };
		Coordinate n_front = { current.x + 1, current.y + 1 };
		frontier.pop_back();
		
		for (auto next : Grid::GetCoords(n_back, n_front))
		{
			if (!cameFrom.contains(next.Hash()))
			{
				frontier.push_back(next);
				cameFrom[next.Hash()] = (coordinate - next).Clamp();
				distance[next.Hash()] = 1 + distance[current.Hash()];

				Grid::vField[next.Hash()] = (coordinate - next).Clamp().Hash();
			}
		}
	}

	Coordinate pos = goal;
	while(pos.Hash() != coordinate.Hash())
	{ 
		// it is inverted for some reason
		path.push_back(MoveAction(cameFrom[pos.Hash()] * -1));
		pos = pos + cameFrom[pos.Hash()];
	}

	return path;
}

uint16_t GridItem::GetDrawOrder() { return drawOrder; }
uint16_t GridItem::GetCollisionMask() { return collisionMask; } 
Coordinate GridItem::GetPosition() { return coordinate; }

>>>>>>> Stashed changes
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


