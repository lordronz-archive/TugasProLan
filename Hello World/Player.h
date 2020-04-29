#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Window.h"
#include "Collider.h"
#include <fstream>

class Player
{
private:
	sf::Texture playerTexture;
	sf::Sprite player;
	sf::Vector2i increment;
	sf::Vector2u textSize;
	sf::Vector2f playerCenter;
	sf::Vector2i mousePosition;
	sf::Vector2f worldPosition;
	sf::Texture gunTexture;
	sf::Sprite gun;
	sf::Texture gunshotTexture;
	sf::Sprite gunshot;
	sf::Clock clock1;
	sf::Clock clock2;
	sf::Clock movementTime;
	sf::SoundBuffer weaponSfxBuffer;
	sf::Sound weaponSfx;
	sf::SoundBuffer walkSfxBuffer;
	sf::Sound walkSfx;
	void movePlayer();
	bool Move(float moveX, float moveY);
	float dt1;
	float dt2;
	bool fire;
	int tiles[23][40];

public:
	Player();
	void updatePlayer(sf::RenderWindow* window);
	sf::Sprite* getPlayerSprite();
	sf::Sprite* getGunSprite();
	sf::Sprite* getGunshotSprite();
	sf::Vector2f getCharCoord();
	sf::Vector2f getPlayerCenter();
	sf::Vector2f getMousePos();
	bool getFireStatus();
	Collider GetCollider();
};

#endif

