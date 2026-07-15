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
  std::shared_ptr<Entity> m_player;

  // Spawn functions
	void spawnPlayer();
	void spawnEnemy();
	void spawnBullet();

  // Systems
	void systemRender();
	void systemMovement();
	void systemPlayer();
	void systemEnemies();
  void systemInput();
  void systemCollision();
  void systemBullets();
  void systemTimer();

  // Kill functions
  void killPlayer();
  void killEnemy(std::shared_ptr<Entity> enemy);
  void killBullet(std::shared_ptr<Entity> bullet);

  // Utility functions
  bool readConfigFile(const std::string &pathToConfigFile);

  void drawBackground();
  void drawScore();
  void drawPlayerPosition();
  
  void clearInputs();
  bool checkCollision(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2);
	static int rand(int min, int max);

public:
	Game(const char *currentWorkingDirectory);
	~Game();
	void run();
};
