#pragma once

#include <string>

enum ActionType
{ 
  PRESSED = 0,
  RELEASED = 1
};

class Action
{ 
public:
  ActionType type;
  std::string name;

  Action(ActionType type, std::string name)
    : type(type)
    , name(name)
  {}
}
