#pragma once
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "raylib.h"
#include <string>
#include <memory>


// needs to be a prototype
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


#endif
