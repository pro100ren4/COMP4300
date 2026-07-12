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

	return 0;
}
