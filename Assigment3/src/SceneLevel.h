#pragma once

#include <memory>

#include "Config.h"
#include "EntityManager.h"
#include "Scene.h"

class SceneLevel : public Scene
{
  EntityManager m_entities;
  std::shared_ptr<LevelConfig> m_levelConfig;

  bool m_displaySprites = true;
  bool m_displayGrid = false;
  bool m_displayAABB = false;


  const int m_tileWidth = 18;
  const int m_tileHeight = 18;

  void createTile(const TileConfig &c);

  void drawTiles();
  void drawGrid();
  void dradAABB();

public:
  SceneLevel(std::shared_ptr<LevelConfig> levelConfig);
  ~SceneLevel();

  void systemInput()  override;
  void systemUpdate() override;
  void systemRender() override;
};
