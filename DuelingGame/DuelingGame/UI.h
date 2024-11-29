#pragma once
#ifndef UI_H
#define UI_H
#include <iostream>
#include "GameEntity.h"


class Menue
{
	// needs to ease in
	// have highlighting
	// choose an option 
	// move to different page
public:
	// needs to get the player pos and then steal the inputs
	Menue(Vector2* anchor_);
	~Menue();

	Vector2 anchorOffset;
	void Draw();
	void ListenForInput(KeyboardKey key);
	bool IsOpen() { return isOpen; }
private:

	Vector2* anchor;
	int menuePos = 0;
	bool isOpen = false;
	GameResource sprites;
	NPatchInfo shadow = { {0, 48, 32, 32}, 0, 0, 0, 0, NPATCH_NINE_PATCH };
	Rectangle shadowDst;
	Rectangle baseDst;
};

#endif UI_H
