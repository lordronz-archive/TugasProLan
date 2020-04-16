#pragma once
#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "Player.h"
#include "Menu.h"
#include "Map.h"
#include "Bullet.h"
#include "Wall.h"
#include <array>

class Game
{
private:
	Player player;
	Window window;
	Bullet b1;
	std::vector<Bullet> bullets;
	Map map;
	std::array<Wall, 3> walls;
	Wall wall;
	sf::View view;
	sf::Clock clock;
	sf::Texture cursorText;
	sf::Sprite cursor;
	sf::Vector2f checkView();

public:
	Game();
	~Game();
	void HandleInput();
	void Update();
	void Render();
	Window* GetWindow();
	void Run();
};

#endif

