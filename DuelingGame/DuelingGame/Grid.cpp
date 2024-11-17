#include "Grid.h"
#include <iostream>

// Grid
/*=========================================================================================*/
std::unique_ptr<Cell> Grid::grid = nullptr;
std::map<int, int> Grid::gridMap;
Grid::Grid() 
{ 
	memory = (Cell*)malloc(sizeof(Cell) * (MAX_CELLS + 1));

//	int axesLength = std::sqrt(MAX_CELLS / 4);

	auto fillCell = [&](Coordinate coord, int& i)
	{ 
		if (!gridMap.contains(coord.Hash()))
		{
			new (&memory[i]) Cell(coord);
			gridMap[coord.Hash()] = i;
			i++;
		}
	}; 
	
	int x = 0, y = 0, index = 0, i = 0;

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
	std::cout << std::to_string(index) << std::endl; 


	grid.reset(memory);

}
// elements are already deleted, don't do anything complicated
Grid::~Grid()
{

//	for (int i = 0; i < MAX_CELLS; i++) {
//		memory[i].~Cell(); // Explicitly call the destructor for each Cell
//	} 
}

Cell& Grid::GetCell(Coordinate coord)
{
	int hash = coord.Hash();
	if (!gridMap.contains(hash))
	{
		std::cerr << "Error: Invalid coordinate (" << coord.x << ", " << coord.y << ").\n";
		throw std::out_of_range("Coordinate out of bounds");
	}
	return grid.get()[gridMap.at(hash)];
}

void Grid::DrawGrid()
{
	for (int i = 0; i < MAX_CELLS; i++)
	{
		if (!memory[i].items.empty())
			memory[i].DrawCell();
	}
}


std::vector<Cell*> Grid::GetCells(Coordinate from, Coordinate to)
{
	std::vector<Cell*> cells;

	// Magnitude
	int yDiff = std::abs(to.y - from.y) + 1; 
	int xDiff = std::abs(to.x - from.x) + 1; 

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
			if (gridMap.contains(coord.Hash()))
			{
				cells.push_back(&GetCell(coord)); // Store pointer to Cell
			}
		}
	}

	return cells;
}

// Cell
/*=========================================================================================*/
Cell::Cell() : position{ 0,0 } {}
Cell::Cell(int x, int y) : position{x, y} {}
Cell::Cell(Coordinate cord) : position(cord) {}
Cell::~Cell()
{
//	for (auto const& i : items)
//		i->~GridItem();
}

// ask for refrence to insure that the smart ptr is taken

void Cell::AddItem(GridItem& item)
{
	item.position = position;
	items[item.ID] = std::make_unique<GridItem>(item);
}

void Cell::RemoveItem(GridItem& item)
{ 
	items.erase(item.ID);
}

// not working as intended
std::unique_ptr<GridItem> Cell::PopItem(GridItem& item)
{
	std::unique_ptr<GridItem> extractedItem = nullptr;

//	auto it = std::find_if(items.begin(), items.end(),
//		[&item](const std::unique_ptr<GridItem>& p) {
//			return p.get() == &item;
//		});
//
//	if (it != items.end())
//	{
//		extractedItem = std::move(*it);
//		items.erase(it);
//	}
//
	return extractedItem;
}


void Cell::DrawCell()
{
	for (auto const& i : items)
	{ 
		i.second->DrawItem();
	}

}

// GridItem
/*=========================================================================================*/
GridItem::GridItem(GameResource* res) 
	: position({0,0}), resource(res), ID(MakeUUID()) { }
GridItem::GridItem() : position{ 0,0 }, resource(nullptr), ID(MakeUUID()) {}
GridItem::~GridItem() {}

std::string GridItem::MakeUUID()
{
	static std::random_device dev;
    static std::mt19937 rng(dev());

    std::uniform_int_distribution<int> dist(0, 15);

    const char *v = "0123456789abcdef";
    const bool dash[] = { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 };

    std::string res;
    for (int i = 0; i < 16; i++) {
        if (dash[i]) res += "-";
        res += v[dist(rng)];
        res += v[dist(rng)];
    }
    return res;
}

void GridItem::DrawItem()
{
	Vector2 pos = { position.x * 32, position.y * 32 };
	DrawTextureV(resource->GetTexture(), pos, WHITE);
}

/*
the current memory structure might be bad. Its doing a lot.
because the grids store unique ptrs the cell lists own those ptrs,
so when trying to move them you run into issues

in the future a shared obj pool which uses shared ptrs to manage objs in play is the option
that way memory in use and memory to refrence can be seperated
*/

void GridItem::Move(Coordinate coord)
{
	coord.x += this->position.x;
	coord.y += this->position.y;

	Grid::GetCell(this->position).RemoveItem(*this);
	Grid::GetCell(coord).AddItem(*this);
}


Vector2 GridItem::GetWorldPos()
{
	Vector2 vec;
	vec.x = 32.0f * position.x;
	vec.y = 32.0f * position.y;
	return vec;
}

// Tile
/*=========================================================================================*/
Tile::Tile() : GridItem() {}
Tile::Tile(GameResource* res) : GridItem(res) {}
Tile::~Tile() {}

// GtidItemPool 
/*=========================================================================================*/
/*
instantiate the pool 
 - assign new objs to pool array
 - finaggel templates logic
fix Move func
 - get the objs via shared ptrs
 - have lists be made of shared ptrs
 - throw in logic whic prevents doubles

*/

//// Grid 
///*======================================================================================*/
//Grid::Grid() : memory(GridMemory())
//{
//	// now memory can be stored in different objects meant to cache memory
//	// an inherit issue that must then be dealt with is memory cached in seperate areas
//	grid = memory.gridMemory;
//	FillMemory(memory.gridMemory); 
//}
//Grid::~Grid()
//{
//}
//
//// (っ-﹏- ς)
//// please remember make debugging tools to check this stuff it is so scary
//
//Cell* Grid::GetCell(Coordinate coordinate) 
//{ 
//	
//	return &grid[map[coordinate]];
//} 
//
//void Grid::MoveGridItem(GridItem* item, Coordinate coord)
//{
//	Cell* home = GetCell(item->coord);
//	Cell* target = GetCell(coord);
//
//	home->RemoveItem(item);
//	target->AddItem(item);
//
//}
//
//void Grid::AddToGrid(GridItem* item, Coordinate coord)
//{
//	GetCell(coord)->AddItem(item);
//}
//
//
//
//Cell Grid::CreateCell(int x, int y) 
//{
//	return Cell(x, y);
//}
//
//void Grid::FillMemory(Cell* memory)
//{
//	 
//	// needs guard rails for when used not on grid memory
//
//	int x,y = 0;
//	for (int i = 0; i < MAX_CELLS; i++)
//	{
//		x = i % 10;
//		y = i % 10 == 0 ? y + 10 : y;
//
//		new (&memory[i]) Cell(x, y);
//		memory[i].position.x = x;
//		memory[i].position.y = y; 
//		std::string str = std::to_string(x) + ", " + std::to_string(y);
//		map[memory[i].position] = i;
//
//	}
//}
// 
//GridMemory::GridMemory()
//{
//	gridMemory = (Cell*)malloc(MAX_CELLS*sizeof(Cell)); 
//}
//GridMemory::~GridMemory()
//{
//	for (int i = 0; i < MAX_CELLS; i++) {
//		gridMemory[i].~Cell(); // Explicitly call the destructor for each Cell
//	}
//	free(gridMemory);
//}
//
//
//// Cell
///*======================================================================================*/ 
///*
//It is possible to add a grid item to unintialized cells
//*/
//Cell::Cell(int x, int y) : position({x, y}), componenets()
//{ }
//Cell::Cell() : position() { }
//Cell::~Cell() {}
//
//// its all being added to cell[0,0] componenets
//void Cell::AddItem(GridItem* item)
//{
//	item->coord = position;
//	std::cout << componenets.size() << std::endl;
//	if (componenets.empty())
//		componenets = { item };
//	else
//		componenets.push_back(item);
//}
//
//void Cell::RemoveItem(GridItem* item)
//{
//	item->coord = { 0, 0 };
//	componenets.remove(item);
//}
//
//void Cell::DrawCell()
//{
//	for (auto const& i : componenets)
//		i->DrawItem();
//} 
//
//// GridItem 
///*======================================================================================*/
//GridItem::GridItem() : resource(nullptr), coord{0,0}
//{
//
//} 
//GridItem::GridItem(GameResource* res) : resource(res), coord{0,0}
//{}
//
//GridItem::~GridItem() {}
//
//Coordinate GridItem::GetGridPos()
//{
//	return coord;
//}
//Vector2 GridItem::GetWorldPos()
//{
//	Coordinate pos = coord;
//	pos.x = pos.x * 32 + 280;
//	pos.y = pos.y * 32 + 400;
//	return { (float)pos.x, (float)pos.y };
//}
//
//void GridItem::DrawItem()
//{
//	//std::cout << GetWorldPos().x << ", " << GetWorldPos().y << std::endl;
//	DrawTextureV(resource->GetTexture(), GetWorldPos(), WHITE);
//}
//
//
//
//// Tile 
///*======================================================================================*/
//Tile::Tile() {}
//Tile::~Tile() {}
//Tile::Tile(GameResource* res) : GridItem(res) {}
//
//
