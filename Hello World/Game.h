#pragma once
#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "Player.h"
#include "Map.h"
#include "Bullet.h"
#include "Wall.h"
#include "NormalZombie.h"
#include "BigZombie.h"
#include "GUI.h"
#include "GameOverHelp.h"

#include <array>

class Game
{
private:
	Player player;
	Window window;
	Bullet b1;
	NormalZombie zombie;
	BigZombie b_zombie;
	GUI GUI;
	GameOverHelp gOver;
	std::vector<NormalZombie> n_zombies;
	std::vector<BigZombie> b_zombies;
	std::vector<Bullet> bullets;
	Map map;
	std::array<Wall, 25> walls;
	Wall wall;
	sf::View view;
	sf::Texture cursorText;
	sf::Sprite cursor;
	sf::Sprite healthPickup;
	sf::Texture healthPickText;
	std::vector<sf::Sprite> healthPickups;
	sf::Vector2f checkViewCenter();
	void updatePlayer();
	void updateWalls();
	void updateZombie(const sf::Vector2f& playerPos);
	sf::Sound bgSound;
	sf::SoundBuffer bgSoundBuffer;
	sf::Sound ricochetSfx;
	sf::SoundBuffer ricochetBuffer;
	sf::Sound attacked;
	sf::SoundBuffer attackedBuffer;
	bool zombieShot;
	bool gameOver;
	unsigned int score;

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

