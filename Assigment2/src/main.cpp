#include <iostream>

#include "Game.h"
#include "Vec2.h"
#include "EntityManager.h"

#include <raylib.h>

#define RAND(min, max) ((min) + (rand() % ((max) - (min) + 1)))
#define RANDF(min, max) (static_cast<float>((min) + (rand() % ((max) - (min) + 1))))

EntityManager manager;


int main(void)
{

	Game game(GetApplicationDirectory());
	game.run();

  // Testing enitity manager
#if 0 
  int score = 0;
  const int maxScore = 32;
  for (int i = 0; i < 100; i++)
  {
    std::shared_ptr<Entity> it = manager.addEntity("Test");
    it->score = std::make_shared<CScore>(score++);
    score = score % maxScore;
  }
  
  manager.update();
  
  EntitiesVector entities = manager.getEntities();

  for (int i = 0; i < 100; i++)
  {
    if (entities[i]->score->score % 4 == 0)
      entities[i]->destroy();
  }

  EntitiesVector entitiesBeforeUpdated = manager.getEntities();

  manager.update();

  EntitiesVector entitiesUpdated = manager.getEntities();
#endif

	return 0;
}
