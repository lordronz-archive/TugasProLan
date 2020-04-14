#include "Wall.h"

void Wall::initWall(sf::Vector2f size, sf::Vector2f position)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setPosition(position);
	body.setFillColor(sf::Color::Red);
}

sf::RectangleShape Wall::getShape()
{
	return sf::RectangleShape(body);
}

Collider Wall::GetCollider()
{
	sf::Vector2f HalfSize = body.getSize() / 2.0f;
	sf::Vector2f Pos = body.getPosition();
	return Collider(HalfSize, Pos, &body, nullptr);
}
