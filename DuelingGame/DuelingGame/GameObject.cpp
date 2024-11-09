#include "GameObject.h"

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
