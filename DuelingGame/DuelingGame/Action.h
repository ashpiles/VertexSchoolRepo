#pragma once
#ifndef ACTION_H
#define ACTION_H
#include "Coordinate.h"
#include <string>

class Character;
struct Coordinate;

/// <summary>
/// Command pattern utilizing functors
/// an execution returns a pointer to itself which is the best we can do as a closurer
/// allows for state to be stored in the object as well
/// </summary>
struct Action
{
public:
	virtual ~Action() {}
	// execute
	virtual Action* operator()(Character* actor) = 0;
	virtual void Undo() = 0;
protected:
	Character* actor = nullptr;
};

struct MoveAction : Action
{
public:
	MoveAction(Coordinate coord_);
	MoveAction* operator()(Character* actor);
	void Undo();

	Coordinate GetCoordinate() { return coord; }

private: 
	Coordinate coord;
};


struct DefendAction : Action
{
public:
	DefendAction(int defAmount_, std::string str_);
	DefendAction* operator()(Character* actor);
	void Undo(); 

private:
	std::string str;
	int defAmount;
};

struct AttackAction : Action
{
public:
	AttackAction( std::string str_);
	AttackAction* operator()(Character* actor, Character* subject);
	void Undo();

private:
	std::string str;
};
 
struct ParryAction : Action
{
public:
	ParryAction( std::string str_);
	ParryAction* operator()(Character* actor, Character* subject);
	void Undo();

private:
	std::string str;
};

#endif
