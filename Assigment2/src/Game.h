#pragma once

#include "Config.h"
#include <string>

class Game
{
  Config config; 

  void readConfigFile();

public:
  Game(std::string configFilePath);
  void run();
};
