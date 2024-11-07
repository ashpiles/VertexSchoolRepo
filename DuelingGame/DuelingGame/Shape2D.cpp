#include "Shape2D.h"



Shape2D::Shape2D() : Position{ 0,0 }, Scale{ 1, 1 } {}

Shape2D::Shape2D(Rectangle rect) 
	: Position({ rect.x, rect.y }), Scale({ rect.width, rect.height }) {}

Rectangle Shape2D::GetShape() {
	return Rectangle{ Position.x, Position.y, Scale.x, Scale.y };
}

TextureLoader::TextureLoader(std::string path) : Path(path) {}

Texture2D TextureLoader::Load() {
	return LoadTexture(Path.c_str());
}
TextureLoader::TextureLoader() {

}
