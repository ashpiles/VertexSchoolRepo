#include "Action.h"


// 0 = ATTACK
// 1 = DEFEND
// 3 = PARRY
std::map<ActionType, std::array<float, 3> > Action::actionMap = {
	{ATTACK, {0, 0.5f, -2}},
	{DEFEND, {0.5f , 0, 0}},
	{PARRY,  {2, 0, 0}}
};

Action::Action(ActionType type, std::string actor)
	: type(type), value(0)
{
	str = (type == ATTACK) ? "Attack" : (type == DEFEND) ? "Defend" : "Parry";
}

// refer to action map for which action wins
Action Action::ProcessActions(const Action* act)
{
	ActionType thisType = this->type;
	ActionType actType  = act->type; 
	int index = (int)actType;
	this->value = GetActionTable(type)[index];
	return *this; 
}

std::array<float, 3> Action::GetActionTable(ActionType type)
{
	return actionMap[type];
}
