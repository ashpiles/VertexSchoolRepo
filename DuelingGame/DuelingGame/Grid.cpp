#include "Grid.h"
#include <iostream>
 
// Grid 
/*======================================================================================*/
Grid::Grid() : memory(GridMemory())
{
	// now memory can be stored in different objects meant to cache memory
	// an inherit issue that must then be dealt with is memory cached in seperate areas
	grid.reset(memory.gridMemory);
	FillMemory(memory.gridMemory);
}
Grid::~Grid() { }

// (っ-﹏- ς)
// please remember make debugging tools to check this stuff it is so scary
std::unique_ptr<Cell> Grid::grid = nullptr;
Cell* Grid::GetCell(Vector2 coord) 
{ 
	// it might be a good idea to create some gaurd rails in grid memory
	// for when going out of bounds
	return &grid.get()[(int)coord.y * 10 + (int)coord.x];
} 

Cell Grid::CreateCell(int x, int y) 
{
	return Cell(x, y);
}

void Grid::FillMemory(Cell* memory)
{

	int x,y = 0;
	for (int i = 0; i < MAX_CELLS; i++)
	{
		x = i % 10;
		y = i == 10 ? y + 10 : y;
		memory[i].position.x = x;
		memory[i].position.y = y;
	}
}
 
GridMemory::GridMemory()
{
	gridMemory = (Cell*)malloc(MAX_CELLS*sizeof(Cell)); 
}
GridMemory::~GridMemory()
{
	free(gridMemory);
}


// Cell
/*======================================================================================*/ 
/*
It is possible to add a grid item to unintialized cells
*/
Cell::Cell(int x, int y) : position({(float)x, (float)y}), componenets()
{ }
Cell::Cell() : position() { }
Cell::~Cell() {}

/*
because the cell is a pointer allocated by malloc it is filled with junk data
so the components list is actually gaining undefined behavior
it is considered not empty but is not filled with any data
*/
void Cell::AddItem(GridItem* item)
{
	item->position = &position;
	std::cout << componenets.size() << std::endl;
	if (componenets.empty())
		componenets = { item };
	else
		componenets.push_back(item);
}

void Cell::RemoveItem(GridItem* item)
{
	item->position = nullptr;
	componenets.remove(item);
}

void Cell::DrawCell()
{
	for (auto const& i : componenets)
		i->DrawItem();
} 

// GridItem 
/*======================================================================================*/
GridItem::GridItem(Vector2 position, GameResource* res) : position(nullptr), resource(res)
{ 
	parent = Grid::GetCell(position);
	parent->AddItem(this);
}
GridItem::GridItem(Cell* cell, GameResource* res) : position(nullptr), resource(res)
{
	parent = cell;
	parent->AddItem(this);
}

GridItem::~GridItem() {}

void GridItem::Move(Vector2 dir)
{
	Cell* target = Grid::GetCell(*position); 
	parent->RemoveItem(this);
	target->AddItem(this);

}

Vector2 GridItem::GetGridPos()
{
	return *position;
}
Vector2 GridItem::GetWorldPos()
{
	Vector2 pos = *position;
	pos.x *= 32;
	pos.y *= 32;
	return pos;
}

void GridItem::DrawItem()
{
	DrawTextureV(resource->GetTexture(), GetWorldPos(), WHITE);
}



// Tile 
/*======================================================================================*/
Tile::Tile(Vector2 dir, GameResource* res) : GridItem(dir, res) 
{
}
Tile::Tile(Cell* cell, GameResource* res) : GridItem(cell, res)
{}
Tile::~Tile() {}

/*Grid::Grid()
{
	TextureLoader loader("../Resources/tile.png");
	tex = loader.Load(); 
	for (int y = 0; y < height; y++) 
	{
		for (int x = 0; x < width; x++) 
		{
			data[y][x] = CreateTile(&tex, x, y); 
			map[std::tuple<int, int>(x, y)] = &data[y][x];
		}
	}

}


// this will have to clip to the nearest grid cell
void Grid::Localize(Shape2D& object) 
{
}

void Grid::Move(Shape2D& object, Vector2 distance) 
{

	distance.x = distance.x * tileSize;
	distance.y = distance.y * tileSize;
}

Grid::~Grid() 
{
	UnloadTexture(tex);
}

Tile* Grid::GetTile(int x, int y) 
{
	return map[std::tuple<int, int>(x, y)];
} 


Tile::Tile()
	: coords{ 0,0 }, texturePtr(nullptr) {}


Tile::~Tile() {}

Tile Grid::CreateTile(Texture2D* tex, int x, int y) 
{
	Vector2 coords = { x, y };

	return Tile(tex, this, coords);
}

 
// I need to do the texture optimization now instead of later
// I cannot allow for each tile to be a texture it uses way too much data
// instead what I must do is have a hashing system where texture is given an id in context
// and then I take that and run with it



// this method is also derefrencing a pointer constantly so that can slow things down
// a texture cache will become mandatory for loading in and out the textures that should be drawn on screen
// poteintally baking the textures into chunks which will be then rendered as is could be good
// also taking the position calculations out of the draw function is a good idea


// =================================================================================================
// I should just use the flyweight method with the texture loader
// textures are loaded into objects which are refrenced via id and we simply go and pick up these objects
// with the a textured obj flyweight
// the flyweight would do good to hold any shared object pointers
void Grid::DrawGrid() 
{ 
	Tile tile;
	Texture2D texture;
	for (int y = 0; y < width; y++) 
	{
		for (int x = 0; x < height; x++) 
		{
			tile = *map[{x, y}];
			texture = *tile.texturePtr;
			if (tile.coords.x == 0 && tile.coords.y == 0) 
				DrawTexture(texture, tile.coords.x + 160, tile.coords.y + 200, WHITE);
			else
				DrawTexture(texture, tile.coords.x * texture.width + 160, tile.coords.y * texture.height + 200, WHITE);

		}
	}
}



*/

