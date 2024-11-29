#include "Character.h"
#include <vector>
#include <map>
#include "Grid.h"

Character::Character(std::string name_, CharacterStats stats_, Coordinate coord, GameResource* res)
	: GameEntity(coord, res), name(name_), stats(stats_)
{
	drawOrder = 2;
	collisionMask = 2;
}

Character::~Character() { }

void Character::UpdateHealth(int Amount) {
	stats.health += Amount;
	if (stats.health <= 0) stats.health = 0;
}

void Character::UpdateStamina(bool Increase) {
	int& stamina = stats.stamina;
	int& maxStamina = stats.maxStamina;

	stamina = (Increase) ? stamina += 1 : stamina -= 1;
	if (stamina > maxStamina)
		stamina = maxStamina;
	else if (stamina <= 0)
		stamina = 0;
}

void Character::InitStats() 
{
	stats.health  = stats.maxHealth;
	stats.stamina = stats.maxStamina;
}

Vector2 Character::GetWorldPos()
{
	return Vector2{ (float)position->x * TILE_SIZE, (float)position->y * TILE_SIZE };
}

void Character::DrawItem()
{
	Vector2 pos = GetWorldPos();
	DrawTexturePro(resource->GetTexture(), {0,0,32,32 }, { pos.x - 8, pos.y - 16, 32, 32 }, { 0, 0 }, 0.0f, WHITE);
}



// think of a better way to intergrate this with character / action stuff
std::deque<MoveAction> Character::PathFindTo(Coordinate goal)
{
	std::deque<MoveAction> path;
	std::vector<Coordinate> frontier;
	std::map<int, Coordinate> cameFrom;
	std::map<int, int> distance;

	frontier.push_back(coordinate);
	cameFrom[coordinate.Hash()] = { 0, 0 };

	while (!frontier.empty())
	{
		Coordinate current = frontier.back();
		Coordinate n_back  = { current.x - 1, current.y - 1 };
		Coordinate n_front = { current.x + 1, current.y + 1 };
		frontier.pop_back();
		
		for (auto next : Grid::GetCoords(n_back, n_front))
		{
			if (!cameFrom.contains(next.Hash()))
			{
				frontier.push_back(next);
				cameFrom[next.Hash()] = (coordinate - next).Clamp();
				distance[next.Hash()] = 1 + distance[current.Hash()];

				Grid::vField[next.Hash()] = (coordinate - next).Clamp().Hash();
			}
		}
	}
	Coordinate pos = goal;
	while(pos.Hash() != coordinate.Hash())
	{ 
		// it is inverted for some reason
		path.push_back(MoveAction(cameFrom[pos.Hash()] * -1));
		pos = pos + cameFrom[pos.Hash()];
	}

	return path;
}



//std::unique_ptr<Action> Character::GetActionFromInput(int Input) {
//	switch (Input) {
//	case 0: 
//		return std::make_unique<AttackAction>(); 
//	case 1:
//		UpdateStamina(false);
//		return std::make_unique<ParryAction>();
//	case 2:
//		UpdateStamina(true);
//		return std::make_unique<DefendAction>();
//	}
//}


