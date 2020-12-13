#pragma once
#ifndef BULLET_H
#define BULLET_H
#include <vector>
#include <math.h>
#include <SFML/Graphics.hpp>

class Bullet
{
private:
	sf::Vector2f aimDir;
	sf::Vector2f aimDirNorm;
	float maxSpeed;

public:
	Bullet();
	void fire(sf::RenderWindow *window, const sf::Vector2f &playerCenter);
	sf::CircleShape &getBullet();
	sf::CircleShape projectile;
	sf::Vector2f currVelocity;
};

#endif

