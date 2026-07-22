#pragma once

#include <map>
#include <string>

#include "Action.h"

class Scene
{
  std::string m_name;
  std::map<std::string, std::shared_ptr<Action>> actions;
    

public:
}
