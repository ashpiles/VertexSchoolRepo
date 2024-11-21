#include "Rendering.h"

// Renderer 
/*=========================================================================================*/
std::vector<RenderEntity*> entities;
Renderer::Renderer() {}
Renderer::~Renderer() {}

void Renderer::AddEntity(RenderEntity* entity) 
{
	entities.push_back(entity);
}

void Renderer::RemoveEntity(RenderEntity* entity) 
{
	//entities.erase(entity);
}

void Renderer::Render()
{
	for (const auto i : entities)
	{
		i->Render();
	}
}

// RenderEntity
/*=========================================================================================*/

// RenderItem
/*=========================================================================================*/
RenderItem::RenderItem(GameResource* res, Vector2* parent, int depth_) 
	: resource(res), parentPos(parent)
{
	depth = depth_;
	Init();
}
RenderItem::~RenderItem() {}

void RenderItem::Render()
{ 
	position = *parentPos;
	Vector2 pos = { position.x * 32, position.y * 32 };
	DrawTextureV(resource->GetTexture(), pos, WHITE);
}
void RenderItem::Init()
{
	Renderer::AddEntity(this);
}


