#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Window.h"
#include "Collider.h"

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
	sf::Texture legsText;
	sf::Sprite legs;
	sf::Vector2u legsTSize;
	sf::Clock clock1;
	sf::Clock clock2;
	sf::Clock stepTimer;
	sf::Clock movementTime;
	sf::SoundBuffer weaponSfxBuffer;
	sf::Sound weaponSfx;
	sf::SoundBuffer walkSfxBuffer;
	sf::Sound walkSfx;
	int stepCount;
	void movePlayer();
	bool Move(float moveX, float moveY);
	float dt1;
	float dt2;

public:
	Player();
	void updatePlayer(sf::RenderWindow* window);
	sf::Sprite* getPlayerSprite();
	sf::Sprite* getGunSprite();
	sf::Sprite* getLegsSprite();
	sf::Texture* getPlayerTexture();
	sf::Vector2f getCharCoord();
	sf::Vector2f getPlayerCenter();
	sf::Vector2f getMousePos();
	Collider GetCollider();
	int healthPoints;
	bool isDead;
	bool isFiring;
	bool fire;
};

#endif

