#pragma once
#include "raylib.h"
#include "GridItem.h"
#include <deque>

class GameResource;

/// <summary>
/// Facades the memory management and searching responsibilities of grid items
/// Provides a space to inherit from so that Action functors may be applied to entities
/// </summary>
class GameEntity : public GridItem
{
public:
	virtual ~GameEntity();
	virtual void DrawItem() = 0;
	virtual void Update() = 0;
	uint16_t GetDrawOrder();
	uint16_t GetCollisionMask();

	// constant coordinate getter
	const Coordinate* const position;
protected:
	GameEntity(Coordinate coord, GameResource* res);
	uint16_t collisionMask;
	uint16_t drawOrder;
	GameResource* resource;
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

struct Action
{
public:
	virtual ~Action() {}
	virtual Action* operator()(GameEntity* actor) = 0;
	virtual void Undo() = 0;
protected:
	GameEntity* actor = nullptr;
};

struct MoveAction : public Action
{
public:
	MoveAction(Coordinate coord_);
	MoveAction* operator()(GameEntity* actor);
	void Undo();

	Coordinate GetCoordinate() { return coord; }

private: 
	Coordinate coord;
};


struct DefendAction : Action
{
public:
	DefendAction(int defAmount_, std::string str_);
	DefendAction* operator()(GameEntity* actor);
	void Undo(); 

private:
	std::string str;
	int defAmount;
};

struct AttackAction : Action
{
public:
	AttackAction( std::string str_);
	AttackAction* operator()(GameEntity* actor, GameEntity* subject);
	void Undo();

private:
	std::string str;
};
 
struct ParryAction : Action
{
public:
	ParryAction( std::string str_);
	ParryAction* operator()(GameEntity* actor, GameEntity* subject);
	void Undo();

private:
	std::string str;
}; 
 
class Tile : public GameEntity
{
public:
	Tile(Coordinate coord, GameResource* res);
	~Tile();

	void DrawItem();
	void Update();

}; 


