#include "Game.h"

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

#include <raylib.h>

#include "Config.h"
#include "EntityManager.h"

void Game::drawBackground()
{
	
	int blockSize = 50;
	bool Switch = false;

	Color primaryColor{0x52, 0x61, 0x6B, 0xFF}; // #52616b
	Color secondaryColor{0x1E, 0x20, 0x22, 0xFF }; // #1e2022

	for (int y = 0; y < m_config.window.height; y += blockSize)
	{
		for (int x = 0; x < m_config.window.width; x += blockSize)
		{
			if (Switch)
				DrawRectangle(x, y, blockSize, blockSize, primaryColor);
			else
				DrawRectangle(x, y, blockSize, blockSize, secondaryColor);

			Switch = !Switch;
		}

		Switch = !Switch;
	}
}

bool Game::readConfigFile(const std::string& pathToConfigFile)
{
	std::ifstream configFile(m_currentWorkingDirectory + pathToConfigFile);
	if (!configFile)
	{
		std::cerr << "Failed to open file: " << m_currentWorkingDirectory + pathToConfigFile << std::endl;
		return false;
	}

	std::string identifier;
	while (configFile >> identifier)
	{
		if (identifier == "Window")
		{
			configFile >> m_config.window.width;
			configFile >> m_config.window.height;
			configFile >> m_config.window.FPSLimit;
			configFile >> m_config.window.isFullScreen;
		}
		else if (identifier == "Font")
		{
			int r, g, b;
			configFile >> m_config.font.name;
			configFile >> m_config.font.size;
			configFile >> r >> g >> b;

			m_config.font.color.r = r;
			m_config.font.color.g = g;
			m_config.font.color.b = b;
			m_config.font.color.a = 255;
		}
		else if (identifier == "Player")
		{
			int r, g, b;

			configFile >> m_config.player.shapeRadius;
			configFile >> m_config.player.collisionRadius;
			configFile >> m_config.player.speed;
			configFile >> r >> g >> b;

			m_config.player.fillColor.r = r;
			m_config.player.fillColor.g = g;
			m_config.player.fillColor.b = b;
			m_config.player.fillColor.a = 255;

			configFile >> r >> g >> b;

			m_config.player.outlineColor.r = r;
			m_config.player.outlineColor.g = g;
			m_config.player.outlineColor.b = b;
			m_config.player.outlineColor.a = 255;

			configFile >> m_config.player.thickness;
			configFile >> m_config.player.sidesNumber;
		}
		else if (identifier == "Enemy")
		{
			int r, g, b;

			configFile >> m_config.enemy.shapeRadius;
			configFile >> m_config.enemy.collisionRadius;
			configFile >> m_config.enemy.minSpeed;
			configFile >> m_config.enemy.maxSpeed;
			configFile >> r >> g >> b;

			m_config.enemy.outlineColor.r = r;
			m_config.enemy.outlineColor.g = g;
			m_config.enemy.outlineColor.b = b;
			m_config.enemy.outlineColor.a = 255;

			configFile >> m_config.enemy.outlineThickness;
			configFile >> m_config.enemy.minSidesNumber;
			configFile >> m_config.enemy.maxSidesNumber;
			configFile >> m_config.enemy.particleLifetime;
			configFile >> m_config.enemy.spawnInterval;
		}
		else if (identifier == "Bullet")
		{
			int r, g, b;

			configFile >> m_config.bullet.shapeRadius;
			configFile >> m_config.bullet.collisionRadius;
			configFile >> m_config.bullet.speed;
			configFile >> r >> g >> b;

			m_config.bullet.fillColor.r = r;
			m_config.bullet.fillColor.g = g;
			m_config.bullet.fillColor.b = b;
			m_config.bullet.fillColor.a = 255;

			configFile >> r >> g >> b;

			m_config.bullet.outlineColor.r = r;
			m_config.bullet.outlineColor.g = g;
			m_config.bullet.outlineColor.b = b;
			m_config.bullet.outlineColor.a = 255;

			configFile >> m_config.bullet.sidesNumber;
			configFile >> m_config.bullet.bulletLifetime;
		}
	}

	return true;
}

int Game::rand(int min, int max)
{
	return min + (::rand() % (max - min + 1));
}

void Game::spawnPlayer()
{
	auto player = m_manager.addEntity("Player");
	player->transform = std::make_shared<CTransform>(
		Vec2(m_config.window.width / 2, m_config.window.height / 2),
		Vec2(0, 0),
		0.f);
	player->shape = std::make_shared<CShape>(
		m_config.player.sidesNumber,
		m_config.player.outlineColor,
		m_config.player.fillColor,
		m_config.player.thickness,
		m_config.player.shapeRadius);

	player->collision = std::make_shared<CCollision>(m_config.player.collisionRadius);
	player->input = std::make_shared<CInput>();
}


void Game::systemRender()
{
	drawBackground();

	EntitiesVector entities = m_manager.getEntities();

	for (auto& entity : entities)
	{
		if (entity->shape && entity->transform)
		{
			Vector2 temp = {};
			temp.x = entity->transform->position.x;
			temp.y = entity->transform->position.y;
			DrawPoly(
				temp,
				entity->shape->numberVerticies,
				entity->shape->radius,
				entity->transform->angle,
				entity->shape->fill);
			DrawPolyLinesEx(
				temp,
				entity->shape->numberVerticies,
				entity->shape->radius,
				entity->transform->angle,
				entity->shape->thickness,
				entity->shape->outline);
		}
	}
}

void Game::systemMovement()
{
	EntitiesVector players = m_manager.getEntities("Player");

	for (auto& player : players)
	{
		if (player->transform)
		{
			player->transform->angle += 5.f;

			Vec2 playerDirection;

			player->transform->velocity = playerDirection * m_config.player.speed;

			if (player->input)
			{
				if (player->input->up)
					playerDirection.y = -1;
				if (player->input->down)
					playerDirection.y = +1;
				if (player->input->left)
					playerDirection.x = -1;
				if (player->input->right)
					playerDirection.x = +1;
			}

			player->transform->velocity = playerDirection * m_config.player.speed;
		}
	}
	
	EntitiesVector entities = m_manager.getEntities();

	for (auto& entity : entities)
	{
		if (entity->transform)
		{
			entity->transform->position += entity->transform->velocity;
		}
	}
}

void Game::systemPlayer()
{
	EntitiesVector entities = m_manager.getEntities("Player");

	for (auto& entity : entities)
	{
		if (entity->input)
		{
			entity->input->up = false;
			entity->input->down = false;
			entity->input->left = false;
			entity->input->right = false;

			if (IsKeyDown(KEY_W))
				entity->input->up = true;
			if (IsKeyDown(KEY_S))
				entity->input->down = true;
			if (IsKeyDown(KEY_A))
				entity->input->left = true;
			if (IsKeyDown(KEY_D))
				entity->input->right = true;
		}
	}
}

Game::Game(const char* currentWorkingDirectory)
	: m_currentWorkingDirectory(currentWorkingDirectory)
{

	if (!readConfigFile(std::string("\\Debug\\res\\config.txt")))
	{
		std::cerr << "Failed to create config" << std::endl;
	}

	// WINDOW
	InitWindow(m_config.window.width, m_config.window.height, "Geomentry Wars !!!");
	SetTargetFPS(m_config.window.FPSLimit);

	if (m_config.window.isFullScreen)
	{
		ToggleFullscreen();
	}

	// ENTITIES
	spawnPlayer();

	m_isRunning = true;
}

Game::~Game()
{
	CloseWindow();
}

void Game::run()
{
	while (!WindowShouldClose())
	{
		/* INPUT */
		if (IsKeyPressed(KEY_P))
		{
			m_isRunning = false;
		}

		/* UPDATE STATE */

		if (!m_isRunning)
			continue;

		systemPlayer();

		/* RENDERING */
		BeginDrawing();

		systemRender();
		systemMovement();

		EndDrawing();
	}
}
