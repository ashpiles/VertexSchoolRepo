#pragma once
#include <string>
#include <iostream>
#include <map>
#include <array>
#include <list>
#include <memory>
#include "Character.h"

/*
we put the oops in oop
you already know how it is
                             ╱|、
                           (˚ˎ 。7  
                            |、˜〵          
                            じしˍ,)ノ
*/

// Abstract Classes
/*=============================================================================*/

// it is both the componenet for a composite and a mediator
// this allows for actions performed at the same time to be handeled
class Action {
protected:
    Action* parent_; 
    ActionMediator* mediator_; 
public:
    virtual ~Action();
    void SetParent(Action* parent);
    Action* GetParent() const;

    virtual void Add(Action *action) {}
    virtual void Remove(Action* action) {}

    virtual bool IsComposite() const;

    Action(ActionMediator* mediator = nullptr);
    void SetMediator(ActionMediator* mediator);
    virtual std::string Act(Character* target) const = 0;
//    Action(ActionType type, std::string actor);
//
//    std::string str;
//    const std::string actor;
//    const ActionType type; 
//    float value;
//    Action ProcessActions(const Action* act);
//    static std::array<float, 3> GetActionTable(ActionType type);
//  private:
//
//
//    // given an action type; return a bool array of it's
//    // win/lose relation to the other action types
//    // bool arr follows the index of the enum 
//    static std::map<ActionType, std::array<float, 3> > actionMap;
}; 

class CompositeAction : public Action {
protected:
    std::list<std::shared_ptr<Action> > children_;
public:
    void Add(Action* action) override; 
    void Remove(Action* action) override;
    bool IsComposite() const override;
    std::string Act(Character* target) const override;
};


class ActionMediator {
public:
    virtual void ProcessActions(Action* sender, std::string event) const = 0;
};

// Concrete Classes
/*=============================================================================*/ 
 
enum ActionType {
    ATTACK,
    DEFEND,
    PARRY,
    NONE
}; 

// the mediator will handle composites of actions
// 
class CombatActionMediator : public ActionMediator {
protected:
    Action* action;
public:
    const std::map<ActionType, std::array<float, 3> > actionMap = {
		{ATTACK, {0, 0.5f, -2}},
		{DEFEND, {0.5f , 0, 0}},
		{PARRY,  {2, 0, 0}} 
    };
    void ProcessActions(Action* sender, std::string event) const override;

};


class AttackAction : public Action{
public: 
	AttackAction(ActionMediator* mediator);
    std::string Act(Character* target) const override;
};

class DefendAction : public Action{
public:
    DefendAction(ActionMediator* mediator);
    std::string Act(Character* target) const override;
};

class ParryAction : public Action{
public:
    ParryAction(ActionMediator* mediator);
    std::string Act(Character* target) const override;
};

 
