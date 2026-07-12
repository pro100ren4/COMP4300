#pragma once

#include <string>

#include "Config.h"
#include "EntityManager.h"


class Game
{
	Config m_config;
	std::string m_currentWorkingDirectory;
  Font m_font;

	bool m_isRunning = false;
  size_t m_enemyTimer = 0;
  int m_score = 0;

	EntityManager m_manager;

	void spawnPlayer();
	void spawnEnemy();

	void destroyPlayer();
	void destroyEnemy();

	void systemRender();
	void systemMovement();
	void systemPlayer();
  void systemInput();
  void systemCollision();

  void clearInputs();
	void drawBackground();
  void drawScore();
	bool readConfigFile(const std::string &pathToConfigFile);
	static int rand(int min, int max);

public:
	Game(const char *currentWorkingDirectory);
	~Game();
	void run();
};
