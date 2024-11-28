#pragma once
#ifndef GRID_H
#define GRID_H
#include <map>
#include <list>
<<<<<<< Updated upstream
#include <vector>
=======
#include <vector> 
#include <string>
#include <queue>
>>>>>>> Stashed changes
#include <cmath>
#include <algorithm>
#include "raylib.h"

#define MAX_CELLS 400
#define TILE_SIZE 16
#define MAX_ITEMS 1000 

using namespace std;

class Grid;
class GridItem;
class Tile;
class GameResource;
class Character;
struct Coordinate;
struct MoveAction;
struct Action;

using flat_items = std::list<GridItem*>;
using vector_items = std::vector<std::list<GridItem*> >;
using mapped_items = std::map<std::string, std::list<GridItem*> >;

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

<<<<<<< Updated upstream
	// Szudzik Pairing
	int Hash()
	{
		int a = x >= 0 ? 2 * x : -2 * x - 1;
		int b = y >= 0 ? 2 * y : -2 * y - 1;
		int c = (a >= b ? a * a + a + b : a + b * b) / 2;
=======
	Coordinate operator-(const Coordinate& other) const
	{
		return { x - other.x, y - other.y };
	}

	Coordinate operator+(const Coordinate& other) const
	{
		return { x + other.x, y + other.y };
	} 

	Coordinate operator*(const int& other) const
	{
		return { x * other, y * other };
	}

	string ToString()
	{
		return to_string(x) + ", " + to_string(y);
	}

	Vector2 Scale(float scalar = 1.0f)
	{
		return Vector2{x * scalar, y * scalar};
	} 

	Coordinate Clamp()
	{ 
		x = clamp(x, -1, 1); 
		y = clamp(y, -1, 1); 

		return Coordinate{ x, y };
	}

	static Coordinate Magnitude(Coordinate& c1, Coordinate& c2)
	{
		int yDiff = abs(c1.y - c2.y); 
		int xDiff = abs(c1.x - c2.x); 

		return { xDiff, yDiff };
	} 

	// Szudzik Pairing Function
	long Hash()
	{
		long a = x >= 0 ? 2 * x : -2 * x - 1;
		long b = y >= 0 ? 2 * y : -2 * y - 1;
		long c = (a >= b ? a * a + a + b : a + b * b) / 2; 
>>>>>>> Stashed changes

		return x < 0 && y < 0 || x >= 0 && y >= 0 ? c : -c - 1; 
	}

<<<<<<< Updated upstream
	static Coordinate ReverseHash(int hash)
=======
	// Szudzik Unpairing Function
	static Coordinate ReverseHash(long hash)
>>>>>>> Stashed changes
	{
		int abs = hash % 2 == 0 ? hash : -(hash + 1);
		int z = static_cast<int>(floor(sqrt(2.0 * abs)));
		int w = abs - (z * (z + 1)) / 2; // triangular number

<<<<<<< Updated upstream
		int a = z >= w ? z : w;
		int b = z >= w ? w : z;

		int x = a % 2 == 0 ? a / 2 : -(a + 1) / 2;
		int y = b % 2 == 0 ? b / 2 : -(b + 1) / 2;

		if (hash % 2 == 0)
=======
		int a = 0;
		int b = 0;
		long z = floor(sqrt(c));
		if (z * (z + 1) <= c) 
>>>>>>> Stashed changes
		{
			x = -x;
			y = -y;
		}

		return Coordinate{ 0, 0 };
	}
<<<<<<< Updated upstream
=======

}; 

template<typename T>
struct CellSearch
{
	CellSearch();
	~CellSearch();
	T* operator()(list<int> indecies);
	
	T& GetData();
private:
	T result;
>>>>>>> Stashed changes
};
 

class Grid final
{ 
public:
<<<<<<< Updated upstream
	static list<GridItem*> GetCell(Coordinate pos, ItemFunc func = nullptr);
	static list<GridItem*> GetCells(Coordinate from, Coordinate to, ItemFunc func = nullptr);
	static GridItem* GetItem(int index) { return Items[index]; }
=======
	template<typename T>
	static void GetCell(Coordinate pos, CellSearch<T>* func);

	template<typename T>
	static void GetCells(Coordinate from, Coordinate to, CellSearch<T>* func); 

	static list<Coordinate> GetCoords(Coordinate from, Coordinate to);
	static GridItem* GetItem(int index) { return Items[index]; }
	static map<long, long> vField; 
	static void DebugPathFinding();


>>>>>>> Stashed changes
private:
	
	static map<int, list<int> > GridMap;
	static map<string, int> IDMap;
	static GridItem* Items[MAX_ITEMS];
	static int itemCount;
	static map<int, bool> isItemFree;

	
	friend class GridItem;
}; 
 
// I'll just make an entity class which takes a resource
// grid items are abstract
// then I can plumb the headers correctly
// grid 
class GridItem
{
public:
	~GridItem();
	virtual void DrawItem() = 0;
	//virtual void Update();
	void Move(Coordinate coord);
<<<<<<< Updated upstream
	uint16_t GetDrawOrder() { return drawOrder; }
	uint16_t GetCollisionMask() { return collisionMask; }
=======
	void MoveTo(Coordinate coord);
	deque<MoveAction> PathFindTo(Coordinate coord);

	uint16_t GetDrawOrder();
	uint16_t GetCollisionMask();
	Coordinate GetPosition();
>>>>>>> Stashed changes

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
	Coordinate coordinate;
};


class Tile : public GridItem
{
public:
	Tile(Coordinate coord, GameResource* res);
	~Tile();
	void DrawItem();

}; 

class GameResource
{
public:
	GameResource(std::string path);
	~GameResource();
	void SetTexture(std::string path);
	Texture2D& GetTexture(); 

private:
	Texture2D texture;
}; 



struct CharacterStats
{ 
	int maxHealth;
	int health;
	int atkPower;
	int armor;
	int maxStamina;
	int stamina; 
};

class Character : public GridItem
{
public:
	Character(std::string name_, CharacterStats stats_, Coordinate coord, GameResource* res);
	~Character();
	void UpdateHealth(int Amount);
	void UpdateStamina(bool Increase);
	void InitStats();
	void DrawItem();
	Vector2 GetWorldPos() { return { (float)coordinate.x * TILE_SIZE, (float)coordinate.y * TILE_SIZE }; }

protected:

	const float moveTimerMax;
	float moveTimer = 0;
	std::string name;
	CharacterStats stats;
};

struct Action
{
public:
	virtual ~Action() {}
	// execute
	virtual Action* operator()(Character* actor) = 0;
	virtual void Undo() = 0;
protected:
	Character* actor = nullptr;
};

struct MoveAction : Action
{
public:
	MoveAction(Coordinate coord_);
	MoveAction* operator()(Character* actor);
	void Undo();

	Coordinate GetCoordinate() { return coord; }

private: 
	Coordinate coord;
};


struct DefendAction : Action
{
public:
	DefendAction(int defAmount_, std::string str_);
	DefendAction* operator()(Character* actor);
	void Undo(); 

private:
	std::string str;
	int defAmount;
};

struct AttackAction : Action
{
public:
	AttackAction( std::string str_);
	AttackAction* operator()(Character* actor, Character* subject);
	void Undo();

private:
	std::string str;
};
 
struct ParryAction : Action
{
public:
	ParryAction( std::string str_);
	ParryAction* operator()(Character* actor, Character* subject);
	void Undo();

private:
	std::string str;
}; 


#endif
