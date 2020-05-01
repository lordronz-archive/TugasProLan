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
#include "GUI.h"

#include <array>

class Game
{
private:
	Player player;
	Window window;
	Bullet b1;
	Zombie *zombie;
	GUI GUI;
	std::vector<Zombie> zombies;
	std::vector<Bullet> bullets;
	Map map;
	std::array<Wall, 25> walls;
	Wall wall;
	sf::View view;
	sf::Texture cursorText;
	sf::Sprite cursor;
	sf::Vector2f checkViewCenter();
	void updatePlayer();
	void updateWalls();
	void updateZombie(sf::Vector2f playerPos);
	sf::Sound ricochetSfx;
	sf::SoundBuffer ricochetBuffer;
	bool zombieShot;

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

