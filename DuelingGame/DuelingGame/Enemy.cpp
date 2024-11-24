#include "Enemy.h"
#include "Action.h"
 
Enemy::Enemy(std::string name_, CharacterStats stats_, Coordinate coord, GameResource* res) : 
	Character(name_, stats_, coord, res), Generator(std::random_device{}()), Distribution(0, 2)
{ }


//std::unique_ptr<Action> Enemy::ChooseAction() {
//	int Input = Distribution(Generator);
//	if (Stamina == 0)
//	{
//		std::uniform_int_distribution<> LimitedDistribution(0, 2);
//		Input = LimitedDistribution(Generator) == 1 ? 0 : 2; // implement enemy exhaustion
//	}
//	return GetActionFromInput(Input);
//} 
//
//
//void Enemy::IncreaseDifficulty(int RoundNumber) {
//	switch (RoundNumber) {
//	case 1:
//		return;
//	case 2:
//		Health += RoundNumber;
//		Name = "Goblin Warrior";
//	case 3:
//		Health += RoundNumber;
//		AtkPower += 1;
//		Name = "Gladiator";
//	case 4:
//		Health += RoundNumber;
//		AtkPower += 2;
//		Name = "Berserker";
//	case 5:
//		Health += RoundNumber;
//		AtkPower += RoundNumber / 2;
//		Armor += RoundNumber / 2; 
//		Name = "Knight Champion";
//	} 
//
//}
//
