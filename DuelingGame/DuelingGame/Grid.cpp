#include "Grid.h"
#include <iostream>
#include <algorithm>


// Grid
/*=========================================================================================*/
Grid::Grid() 
{
	int x = 0, y = 0, index = 0, i = 0;

	auto fillCell = [](Coordinate coord, int& i)
	{ 
		if (!GridMap.contains(coord.Hash()))
		{
			GridMap[coord.Hash()] = new Cell(coord);
			i++;
		}
	}; 

	// writes slightly too much memory
	while (index < MAX_CELLS)
	{
		x = i % 10;
		y = i % 10 == 0 && i != 0 ? y + 1 : y;

		fillCell({ x, y }, index);
		fillCell({ -x, y }, index);
		fillCell({ -x, -y }, index); 
		fillCell({ x, -y }, index);
		i++;
	}
	cout << to_string(index) << endl; 
}

Grid::~Grid() 
{
	for (auto pair : GridMap)
	{
		delete pair.second;
		GridMap.erase(pair.first);
	}
}

Cell* Grid::GetCell(Coordinate pos) 
{
	return GridMap[pos.Hash()];
}

vector<Cell*> Grid::GetCells(Coordinate from, Coordinate to) 
{
	vector<Cell*> cells; 

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

			// Boundary check
			if (GridMap.contains(coord.Hash()))
			{
				cells.push_back(GetCell(coord)); 
			}
		}
	}

	return cells;
}

map<int, Cell*> Grid::GridMap;

// Cell
/*=========================================================================================*/
Cell::Cell(Coordinate coord) : coordinate(coordinate)
{ }

Cell::~Cell()
{ }

// can return a null pointer 
GridItem* Cell::GetItem(string id)
{
	if (IDMap.contains(id))
	{ 
		return IDMap[id];
	}

	// have err catching instead
	return nullptr;
}

vector<GridItem*> Cell::GetItems()
{
	vector<GridItem*> items;

	for (auto pair : IDMap)
		items.push_back(pair.second);

	return items;
}

vector<GridItem*> Cell::GetByType(size_t type)
{ 
	vector<GridItem*> items;

	// likely a costly operation
	for (auto pair : IDMap)
	{ 
		if (typeid(*pair.second).hash_code() == type)
			items.push_back(pair.second);
	}

	return items;
}

void Cell::AddItem(string id)
{
	// can cause issues with item deletion
	IDMap[id] = GridItem::ItemTable[id].get();
	typeMap[typeid(IDMap[id]).hash_code()] = id;
}

void Cell::RemoveItem(string id)
{
	typeMap.erase(typeid(IDMap[id]).hash_code());
	IDMap.erase(id);
}

// GridItem
/*=========================================================================================*/
GridItem::GridItem() : ID(MakeUUID())
{
    ItemTable[ID] = make_unique<GridItem>(this);
}

GridItem::~GridItem()
{
    ItemTable.erase(ID);
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

map<string, unique_ptr<GridItem> > GridItem::ItemTable;

//// Grid
///*=========================================================================================*/
//unique_ptr<Cell> Grid::grid = nullptr;
//map<int, int> Grid::gridMap;
//Grid::Grid() 
//{ 
//	memory = (Cell*)malloc(sizeof(Cell) * (MAX_CELLS + 1));
//
////	int axesLength = sqrt(MAX_CELLS / 4);
//
//	auto fillCell = [&](Coordinate coord, int& i)
//	{ 
//		if (!gridMap.contains(coord.Hash()))
//		{
//			new (&memory[i]) Cell(coord);
//			gridMap[coord.Hash()] = i;
//			i++;
//		}
//	}; 
//	
//	int x = 0, y = 0, index = 0, i = 0;
//
//	// writes slightly too much memory
//	while (index < MAX_CELLS)
//	{
//		x = i % 10;
//		y = i % 10 == 0 && i != 0 ? y + 1 : y;
//
//		fillCell({ x, y }, index);
//		fillCell({ -x, y }, index);
//		fillCell({ -x, -y }, index); 
//		fillCell({ x, -y }, index);
//		i++;
//	}
//	cout << to_string(index) << endl; 
//
//
//	grid.reset(memory);
//
//}
//// elements are already deleted, don't do anything complicated
//Grid::~Grid()
//{
//
////	for (int i = 0; i < MAX_CELLS; i++) {
////		memory[i].~Cell(); // Explicitly call the destructor for each Cell
////	} 
//}
//
//Cell& Grid::GetCell(Coordinate coord)
//{
//	int hash = coord.Hash();
//	if (!gridMap.contains(hash))
//	{
//		cerr << "Error: Invalid coordinate (" << coord.x << ", " << coord.y << ").\n";
//throw out_of_range("Coordinate out of bounds");
//	}
//	return grid.get()[gridMap.at(hash)];
//}
//
//void Grid::DrawGrid()
//{
//	for (int i = 0; i < MAX_CELLS; i++)
//	{
//		if (!memory[i].items.empty())
//			memory[i].DrawCell();
//	}
//}
//
//
//vector<Cell*> Grid::GetCells(Coordinate from, Coordinate to)
//{
//	vector<Cell*> cells;
//
//	// Magnitude
//	int yDiff = abs(to.y - from.y) + 1; 
//	int xDiff = abs(to.x - from.x) + 1; 
//
//	// Direction
//	int xDir = (to.x > from.x) ? 1 : (to.x < from.x) ? -1 : 0;
//	int yDir = (to.y > from.y) ? 1 : (to.y < from.y) ? -1 : 0;
//
//	for (int y = 0; y < yDiff; y++)
//	{
//		for (int x = 0; x < xDiff; x++)
//		{
//			Coordinate coord = {
//				from.x + x * xDir,
//				from.y + y * yDir
//			};
//
//			// Boundary check
//			if (gridMap.contains(coord.Hash()))
//			{
//				cells.push_back(&GetCell(coord)); // Store pointer to Cell
//			}
//		}
//	}
//
//	return cells;
//}
//
//// likely will need to seperate into its own class
//
//
//// need to tighten up grid and movement sytem
//// I should make obj pools and the grid passes around the uuid not a pointer
//// movement will not be confined to the grid
//void Grid::PathFindTo(Coordinate coord)
//{
//	queue<Coordinate> frontier;
//	map<int, bool> reached;
//	frontier.push(coord);
//	reached[coord.Hash()] = true;
//
//	while (!frontier.empty())
//	{
//		Coordinate current = frontier.front();
//		// needs a safe version which grabs all available at a collision level
//		auto neighbours = Grid::GetCells(
//			{ current.x - 1, current.y - 1 }, 
//			{ current.x + 1, current.y + 1 }
//		);
//
//		for (auto next : neighbours)
//		{ 
//			for (auto const& item : next->items)
//			{
//				Coordinate pos = next->position;
//				if (item.second->GetCollisionLayer() == 0 && (!reached.contains(pos.Hash())))
//				{
//					frontier.push(pos);
//					reached[pos.Hash()] = true;
//					cout << pos.x << ", " << pos.y << endl;
//					continue;
//				}
//			}
//
//		}
//	}
//	// originating from coord
//	// find reachable coords
//	// mark path from one cell to another to create a vector field
//	// add weight to each cell
//}
//
//
//
//// Cell
///*=========================================================================================*/
//Cell::Cell() : position{ 0,0 } {}
//Cell::Cell(int x, int y) : position{x, y} {}
//Cell::Cell(Coordinate cord) : position(cord) {}
//Cell::~Cell()
//{
////	for (auto const& i : items)
////		i->~GridItem();
//}
//
//// ask for refrence to insure that the smart ptr is taken
//
//void Cell::AddItem(GridItem* item)
//{
//	item->position = position;
//	items[item->ID] = item;
//}
//
//void Cell::RemoveItem(GridItem* item)
//{ 
//	items.erase(item->ID);
//}
//
//// not working as intended
//unique_ptr<GridItem> Cell::PopItem(GridItem& item)
//{
//	unique_ptr<GridItem> extractedItem = nullptr;
//
////	auto it = find_if(items.begin(), items.end(),
////		[&item](const unique_ptr<GridItem>& p) {
////			return p.get() == &item;
////		});
////
////	if (it != items.end())
////	{
////		extractedItem = move(*it);
////		items.erase(it);
////	}
////
//	return extractedItem;
//}
//
//// rendering is a concern which must be seperated
//void Cell::DrawCell()
//{
//	map<int, vector<string> > drawMap; // maybe meging this with a larger chunk
//
//	for (auto const& i : items)
//	{ 
//		drawMap[i.second->renderDepth].push_back(i.first);
//	}
//	for (auto const& j : drawMap)
//	{
//		for (auto const& l : drawMap[j.first])
//		{
//			items[l]->DrawItem();
//		}
//	}
//}
// 
//
//// GridItem
///*=========================================================================================*/
//GridItem::GridItem(GameResource* res) 
//	: position({0,0}), resource(res), ID(MakeUUID()) { }
//GridItem::GridItem() : position{ 0,0 }, resource(nullptr), ID(MakeUUID()) {}
//GridItem::~GridItem() {}
//
//string GridItem::MakeUUID()
//{
//	static random_device dev;
//    static mt19937 rng(dev());
//
//    uniform_int_distribution<int> dist(0, 15);
//
//    const char *v = "0123456789abcdef";
//    const bool dash[] = { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 };
//
//    string res;
//    for (int i = 0; i < 16; i++)
//	{
//        if (dash[i]) res += "-";
//        res += v[dist(rng)];
//        res += v[dist(rng)];
//    }
//    return res;
//}
//
//
///*
//the current memory structure might be bad. Its doing a lot.
//because the grids store unique ptrs the cell lists own those ptrs,
//so when trying to move them you run into issues
//
//in the future a shared obj pool which uses shared ptrs to manage objs in play is the option
//that way memory in use and memory to refrence can be seperated
//*/
//
///*
//I need to rethink the game obj structure
//
//The cells can hold an id which is used to look up a pointer to the obj
//that should be the interface
//*/
//
///*
//void GridItem::Move(Coordinate coord)
//{
//	coord.x += this->position.x;
//	coord.y += this->position.y;
//
//	if (moveTimerMax < moveTimer)
//	{ 
//		if (Grid::GetCell(coord).CanItemMove(*this))
//		{ 
//			Grid::GetCell(this->position).RemoveItem(*this);
//			Grid::GetCell(coord).AddItem(*this);
//			moveTimer = 0;
//		}
//		else
//		{ 
//			cout << "Tried to move on occupied space" << endl;
//		} 
//	}
//	else
//	{
//		moveTimer += GetTime();
//	} 
//	//cout << moveTimer << endl;
//}
//*/
//
//Vector2 GridItem::GetWorldPos()
//{
//	Vector2 vec;
//	vec.x = TILE_SIZE * position.x;
//	vec.y = TILE_SIZE * position.y;
//	return vec;
//}
//
//// Tile
///*=========================================================================================*/
//Tile::Tile() : GridItem() {}
//Tile::Tile(GameResource* res) : GridItem(res) {}
//Tile::Tile(GameResource* res, int colLayer) : GridItem(res)
//{
//	collisionLayer = colLayer;
//}
//Tile::~Tile() {}
//
//void Tile::DrawItem()
//{
//	Vector2 pos = { position.x * TILE_SIZE, position.y * TILE_SIZE };
//	DrawTextureV(resource->GetTexture(), pos, WHITE);
//}
//
//void Tile::Move(Coordinate coord)
//{ }
//
//
//// GtidItemPool 
///*=========================================================================================*/
///*
//instantiate the pool 
// - assign new objs to pool array
// - finaggel templates logic
//fix Move func
// - get the objs via shared ptrs
// - have lists be made of shared ptrs
// - throw in logic whic prevents doubles
//
//*/
