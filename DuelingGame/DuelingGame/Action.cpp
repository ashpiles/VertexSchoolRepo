#include "Action.h"
#include "Character.h"


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


Action::Action(ActionMediator* mediator, Character* target)
	: Mediator(mediator), Target(target), Parent(nullptr){}



Action::~Action() {}

bool Action::IsComposite() const {
	return false;
} 

void Action::SetTarget(Character* target) {
	this->Target = target;
}

void Action::SetMediator(ActionMediator* mediator) {
	this->Mediator = mediator;
}
void Action::SetParent(Action* parent) {
	this->Parent = parent;
}

Action* Action::GetParent() const {
	return this->Parent;
}

void CompositeAction::Add(Action* action) {
	Children.emplace_back(action);
	action->SetParent(this);
}

void CompositeAction::Remove(Action* action) {
	Children.remove_if([&](const std::shared_ptr<Action>& ptr) {
		return ptr.get() == action;
		});
	action->SetParent(nullptr);
}


std::string CompositeAction::Act() const { 
	std::string result;
	for (const auto& a : Children) {
		if (a == Children.back())
			result += a->Act();
		else
			result += a->Act() + "+";
	}
	return "Branch(" + result + ")"; 
}

bool CompositeAction::IsComposite() const {
	return true;
}


// handles the comabt action priorties 
void CombatActionMediator::ProcessActions(Action* sender, const std::string& event) const {

	if (CompositeAction* composite = dynamic_cast<CompositeAction*>(sender)) {

		std::cout << "composite action" << std::endl;
	} else {
		std::cout << "single action" << std::endl;
	}
}

AttackAction::AttackAction(ActionMediator* mediator, Character* target) 
	: Action(mediator, target) { } 
std::string AttackAction::Act() const {
	return "test"; 
}

DefendAction::DefendAction(ActionMediator* mediator, Character* target)
	: Action(mediator, target) { } 
std::string DefendAction::Act() const {
	return "test"; 
}

ParryAction::ParryAction(ActionMediator* mediator, Character* target)
	: Action(mediator, target) { } 
std::string ParryAction::Act() const {
	return "test"; 
}
