#pragma once
#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics.hpp>
#include "Collider.h"

class Wall
{
public:
	void initWall(sf::Vector2f size, sf::Vector2f position);
	sf::RectangleShape getShape();
	Collider GetCollider();
	sf::RectangleShape body;

private:

};

#endif

