/*
we put the oops in oop
you already know how it is
                             ╱|、
                           (˚ˎ 。7  
                            |、˜〵          
                            じしˍ,)ノ
*/ 
#pragma once
#ifndef ACTION_H
#define ACTION_H

#include <string>
#include <iostream>
#include <map>
#include <array>
#include <list>
#include <memory>

// Forward declarations
class Character;
class Action;
class ActionMediator;

// Abstract Classes
/*=============================================================================*/

// Enum for Action Types
enum ActionType {
    ATTACK,
    DEFEND,
    PARRY,
    NONE
};

// ActionMediator class
class ActionMediator {
public:
    virtual void ProcessActions(Action* sender, const std::string& event) const = 0;
};

// Action class
class Action {
protected:
    Action* Parent;
    ActionMediator* Mediator;
private:
    Character* Target;
public:
    virtual ~Action();
    void SetParent(Action* parent);
    void SetTarget(Character* target);
    Action* GetParent() const;

    virtual void Add(Action* action) {}
    virtual void Remove(Action* action) {}

    virtual bool IsComposite() const;

    Action(ActionMediator* mediator = nullptr, Character* target = nullptr);
    void SetMediator(ActionMediator* mediator);
    virtual std::string Act() const = 0;
};

// CompositeAction class
class CompositeAction : public Action {
protected:
    std::list<std::shared_ptr<Action>> Children;
public:
    void Add(Action* action) override;
    void Remove(Action* action) override;
    bool IsComposite() const override;
    std::string Act() const override;
};

// CombatActionMediator class
class CombatActionMediator : public ActionMediator {
protected:
    Action* action;
public:
    const std::map<ActionType, std::array<float, 3> > actionMap = {
        {ATTACK, {0, 0.5f, -2}},
        {DEFEND, {0.5f, 0, 0}},
        {PARRY, {2, 0, 0}}
    };
    void ProcessActions(Action* sender, const std::string& event) const override;
};

// Concrete Action Classes
/*=============================================================================*/

class AttackAction : public Action {
public:
    AttackAction(ActionMediator* mediator = nullptr, Character* target = nullptr);
    std::string Act() const override;
};

class DefendAction : public Action {
public:
    DefendAction(ActionMediator* mediator = nullptr, Character* target = nullptr);
    std::string Act() const override;
};

class ParryAction : public Action {
public:
    ParryAction(ActionMediator* mediator = nullptr, Character* target = nullptr);
    std::string Act() const override;
};

#endif // ACTION_H

