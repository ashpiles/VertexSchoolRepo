#include "Grid.h" 

// MoveAction 
/*=========================================================================================*/

MoveAction::MoveAction(Coordinate coord_) : coord(coord_) { }

MoveAction* MoveAction::operator()(Character* actor_)
{
	if (actor_ != nullptr)
	{
		actor = actor_;
		actor->Move(coord);
		return this;
	}
	else
		return nullptr;
}

void MoveAction::Undo()
{
	if(actor != nullptr)
		actor->Move(coord * -1);
}

// DefendAction 
/*=========================================================================================*/

DefendAction::DefendAction(int defAmount_, std::string str_) : defAmount(defAmount_), str(str_){}

DefendAction* DefendAction::operator()(Character* actor)
{
	// adds temp armor
	return nullptr;
}

void DefendAction::Undo()
{ }

// AttackAction 
/*=========================================================================================*/

AttackAction::AttackAction( std::string str_) : str(str_){}

AttackAction* AttackAction::operator()(Character* actor, Character* subject)
{
	// subtract health from 
	return nullptr;
}

void AttackAction::Undo()
{ }

// ParryAction 
/*=========================================================================================*/

ParryAction::ParryAction( std::string str_) : str(str_){}

ParryAction* ParryAction::operator()(Character* actor, Character* subject)
{

	return nullptr;
}

void ParryAction::Undo()
{ }

