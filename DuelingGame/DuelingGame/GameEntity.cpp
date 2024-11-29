#include "GameEntity.h"


// GameEntity 
/*=========================================================================================*/ 
GameEntity::GameEntity(Coordinate coord, GameResource* res) 
	: GridItem(coord), position(&coordinate), resource(res) { }
GameEntity::~GameEntity() { } 

uint16_t GameEntity::GetDrawOrder() { return collisionMask; }
uint16_t GameEntity::GetCollisionMask() { return drawOrder; }


// GameResource 
/*=========================================================================================*/
GameResource::GameResource(std::string path) 
{ 
	texture = LoadTexture(path.c_str());
}

GameResource::~GameResource()
{
	UnloadTexture(texture);
}

void GameResource::SetTexture(std::string path)
{ 
	UnloadTexture(texture);
	texture = LoadTexture(path.c_str());
}

Texture2D& GameResource::GetTexture()
{
	return texture;
} 

// MoveAction 
/*=========================================================================================*/

MoveAction::MoveAction(Coordinate coord_) : coord(coord_) { }

MoveAction* MoveAction::operator()(GameEntity* actor_)
{
	if (actor_ != nullptr)
	{
		actor = actor_;
		actor->Move(coord);
		return this;
	}
	else
		return nullptr;
}

void MoveAction::Undo()
{
	if(actor != nullptr)
		actor->Move(coord * -1);
}

// DefendAction 
/*=========================================================================================*/

DefendAction::DefendAction(int defAmount_, std::string str_) : defAmount(defAmount_), str(str_){}

DefendAction* DefendAction::operator()(GameEntity* actor)
{
	// adds temp armor
	return nullptr;
}

void DefendAction::Undo()
{ }

// AttackAction 
/*=========================================================================================*/

AttackAction::AttackAction( std::string str_) : str(str_){}

AttackAction* AttackAction::operator()(GameEntity* actor, GameEntity* subject)
{
	// subtract health from 
	return nullptr;
}

void AttackAction::Undo()
{ }

// ParryAction 
/*=========================================================================================*/

ParryAction::ParryAction( std::string str_) : str(str_){}

ParryAction* ParryAction::operator()(GameEntity* actor, GameEntity* subject)
{

	return nullptr;
}

void ParryAction::Undo()
{ }



// Tile
/*=========================================================================================*/
Tile::Tile(Coordinate coord, GameResource* res) : GameEntity(coord, res)
{
}

Tile::~Tile()
{

}

void Tile::DrawItem()
{
	DrawTextureV(resource->GetTexture(), { (float) position->x * TILE_SIZE, (float) position->y * TILE_SIZE }, WHITE);
}

void Tile::Update() {}


