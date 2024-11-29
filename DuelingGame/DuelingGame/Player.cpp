
#include "Player.h"


Player::Player(std::string name_, CharacterStats stats_, Coordinate coord, GameResource* res)
	: Character(name_, stats_, coord, res) { }

Player::~Player() {}

void Player::Update() {}
