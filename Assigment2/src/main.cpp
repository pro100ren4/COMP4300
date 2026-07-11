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
	Game game(GetWorkingDirectory());
	game.run();

#if 0
	InitWindow(800, 600, "Test");

	SetTargetFPS(60);

	EntityManager manager;

	std::cout << GetWorkingDirectory() << std::endl;

	while (!WindowShouldClose())
	{

		auto e = manager.addEntity("Polygon");

		e->transform = std::make_shared<CTransform>(Vec2{ RANDF(0, 800), RANDF(0, 600) },
														Vec2{ 0.f, 0.f }, 0.f);
		e->shape = std::make_shared<CShape>(RAND(3, 10), GREEN, WHITE, 10.f, 30.f);
		std::string(GetWorkingDirectory(), "/res/config.txt");

		BeginDrawing();
		ClearBackground(BLACK);
		EntitiesVector entities = manager.getEntities();
		for (auto& entity : entities)
		{
			DrawPoly(Vector2{ entity->transform->position.x, entity->transform->position.y },
						entity->shape->numberVerticies,
						entity->shape->radius,
						0.f,
						entity->shape->fill);
			DrawPolyLinesEx(Vector2{ entity->transform->position.x, entity->transform->position.y },
							entity->shape->numberVerticies,
							entity->shape->radius,
							0.f,
							entity->shape->thickness,
							entity->shape->outline);
			} 
		EndDrawing();
	}

	CloseWindow();
#endif
	return 0;
}
