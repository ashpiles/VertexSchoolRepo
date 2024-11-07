#pragma once
#ifndef SHAPE2D_H
#define SHAPE2D_H

#include "raylib.h"
#include <string>


struct Shape2D {
	Vector2 Scale;
	Vector2 Position;
	Shape2D();
	Shape2D(Rectangle rect);
	Rectangle GetShape();

};

// maps the texture to a shape2d
// the shape2d is the dest rect
// this texture loader will hold the source rect
struct TextureLoader {

	// can also do some error checking for ensuring resources are correctly located
	// can also do some resource loading management shennigans maybe


	// it might be best to have a look up table where textures are assigned ids or names
	std::string Path; 
	Texture2D Load();
	TextureLoader(std::string path);
	TextureLoader();
};


#endif
