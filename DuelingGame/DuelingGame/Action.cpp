#include "Action.h"


// 0 = ATTACK
// 1 = DEFEND
// 3 = PARRY
//
//Action::Action(ActionType type, std::string actor)
//	: type(type), value(0)
//{
//	str = (type == ATTACK) ? "Attack" : (type == DEFEND) ? "Defend" : "Parry";
//}
//
//// refer to action map for which action wins
//Action Action::ProcessActions(const Action* act)
//{
//	ActionType thisType = this->type;
//	ActionType actType  = act->type; 
//	int index = (int)actType;
//	this->value = GetActionTable(type)[index];
//	return *this; 
//}
//
//std::array<float, 3> Action::GetActionTable(ActionType type)
//{
//	return actionMap[type];
//}


Action::Action(ActionMediator* mediator = nullptr) : mediator_(mediator) {}

bool Action::IsComposite() const {
	return false;
}

void Action::SetMediator(ActionMediator* mediator) {
	this->mediator_ = mediator;
}
void Action::SetParent(Action* parent) {
	this->parent_ = parent;
}

Action* Action::GetParent() const {
	return this->parent_;
}
bool Action::IsComposite() const {
	return false;
} 

void CompositeAction::Add(Action* action) {
	children_.emplace_back(action);
	action->SetParent(this);
}

void CompositeAction::Remove(Action* action) {
	children_.remove_if([&](const std::shared_ptr<Action>& ptr) {
		return ptr.get() == action;
		});
	action->SetParent(nullptr);
}


std::string CompositeAction::Act(Character* target) const { 
	std::string result;
	for (const auto& a : children_) {
		if (a == children_.back())
			result += a->Act(target);
		else
			result += a->Act(target) + "+";
	}
	return "Branch(" + result + ")"; 
}

bool CompositeAction::IsComposite() const {
	return true;
}


void CombatActionMediator::ProcessActions(Action* sender, std::string event) const {

	if (CompositeAction* composite = dynamic_cast<CompositeAction*>(sender)) {

		std::cout << "composite action" << std::endl;
	} else {
		std::cout << "single action" << std::endl;
	}
}

AttackAction::AttackAction(ActionMediator* mediator = nullptr) : Action(mediator) { } 
std::string AttackAction::Act(Character* target) const {
	return "test"; 
}

DefendAction::DefendAction(ActionMediator* mediator = nullptr) : Action(mediator) { } 
std::string DefendAction::Act(Character* target) const {
	return "test"; 
}

ParryAction::ParryAction(ActionMediator* mediator = nullptr) : Action(mediator) { } 
std::string ParryAction::Act(Character* target) const {
	return "test"; 
}
