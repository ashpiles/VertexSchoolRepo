#pragma once
#include <string>
#include <iostream>
#include <map>
#include <array>

enum ActionType {
    ATTACK,
    DEFEND,
    PARRY,
    NONE
};

class Action {
public:
    Action(ActionType type, std::string actor);

    std::string str;
    const std::string actor;
    const ActionType type; 
    float value;
    Action ProcessActions(const Action* act);
    static std::array<float, 3> GetActionTable(ActionType type);
  private:


    // given an action type; return a bool array of it's
    // win/lose relation to the other action types
    // bool arr follows the index of the enum 
    static std::map<ActionType, std::array<float, 3> > actionMap;
};

