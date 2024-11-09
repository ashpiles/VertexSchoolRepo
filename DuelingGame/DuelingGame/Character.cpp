#include "Action.h"
#include "Grid.h"
#include "Character.h"
#include <iostream>

Character:: Character(std::string name_, CharacterStats stats_, Vector2 pos, GameResource* res)
	: GridItem(pos, res), name(name_), stats(stats_) {}

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

void Character::InitStats() {
	stats.health  = stats.maxHealth;
	stats.stamina = stats.maxStamina;
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