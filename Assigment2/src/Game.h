#pragma once

#include <string>

#include "Config.h"
#include "EntityManager.h"


class Game
{
	Config m_config;
	std::string m_currentWorkingDirectory;

	bool m_isRunning = false;

	EntityManager m_manager;

	void spawnPlayer();

	void systemRender();
	void systemMovement();
	void systemPlayer();
  void systemInput();

  void clearInputs();
	void drawBackground();
	bool readConfigFile(const std::string &pathToConfigFile);
	static int rand(int min, int max);

public:
	Game(const char *currentWorkingDirectory);
	~Game();
	void run();
};
