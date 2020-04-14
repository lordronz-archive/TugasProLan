#pragma once
#ifndef COLLIDER_H
#define COLLIDER_H
#include <SFML/Graphics.hpp>

//collision between rectangle and a sprite
class Collider
{
public:
	//Collider(sf::RectangleShape& body);
	Collider(sf::Vector2f Halfsize, sf::Vector2f Position, sf::RectangleShape* body, sf::Sprite* sprite);
	bool checkCollision(Collider other, float push);
	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; }
	void Move(float dx, float dy) { body.move(dx, dy); }
	void MoveSprite(float dx, float dy) { sprite.move(dx, dy); }

private:
	sf::RectangleShape& body;
	sf::Sprite& sprite;
	sf::Vector2f HalfSize;
	sf::Vector2f Position;
};

#endif
