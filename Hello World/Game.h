#pragma once
#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "Player.h"
#include "Menu.h"
#include "Map.h"
#include "Bullet.h"
#include "Wall.h"
#include "Zombie.h"

#include <array>

class Game
{
private:
	Player player;
	Window window;
	Bullet b1;
	Zombie *zombie;
	std::vector<Zombie> zombies;
	std::vector<Bullet> bullets;
	Map map;
	std::array<Wall, 25> walls;
	Wall wall;
	sf::View view;
	sf::Clock clock;
	sf::Texture cursorText;
	sf::Sprite cursor;
	sf::Vector2f checkViewCenter();
	void updatePlayer();
	void updateWalls();

public:
	Game();
	~Game();
	void HandleInput();
	void Update();
	void Render();
	Window* GetWindow();
	void Run();
	int tiles[23][40];
};

#endif

