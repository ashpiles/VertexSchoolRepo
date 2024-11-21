#include "UI.h"

Menue::Menue(Vector2* anchor_) : sprites(GameResource("../Resources/UI.png")), anchor(anchor_)
{}
Menue::~Menue() {}

void Menue::Draw() 
{
	float scrWidth = GetScreenWidth();
	float scrHeight = GetScreenHeight();
	Vector2 pos = *anchor;
	pos.x += anchorOffset.x;
	pos.y += anchorOffset.y;
	std::cout << std::to_string(pos.x) << std::to_string(pos.y) << std::endl;
	shadowDst = { pos.x, pos.y, scrWidth / 6 , scrHeight / 4 };
	DrawTextureNPatch(sprites.GetTexture(), shadow, shadowDst, {0, 0}, 0.0f, WHITE);
	DrawRectangle(pos.x, pos.y + 30 * menuePos, shadowDst.width, 20, Fade(WHITE, 0.5f));

	pos.x += 5;
	DrawText("move", pos.x, pos.y, 20, WHITE); // to align right it needs a parent bounding box
	DrawText("attack", pos.x, pos.y + 30, 20, WHITE);
	DrawText("defend", pos.x, pos.y + 60, 20, WHITE);
	DrawText("parry", pos.x, pos.y + 90, 20, WHITE);

}

void Menue::ListenForInput(KeyboardKey key)
{
	switch (key)
	{
	case KEY_W:
		menuePos = menuePos + 1 < 4 ? menuePos + 1 : menuePos;
		break;
	case KEY_S:
		menuePos = menuePos - 1 > -1 ? menuePos - 1 : menuePos;
		break;
	case KEY_A:
		break;
	case KEY_D:
		break; 
	case KEY_M:
		isOpen = !isOpen;
		break;
	case KEY_SPACE:
		break;
	case KEY_ENTER:
		break;
	default:
		break;
	}
	
}
