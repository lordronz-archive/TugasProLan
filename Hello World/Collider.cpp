#include "Collider.h"

Collider::Collider(sf::Vector2f HalfSize, sf::Vector2f Position, sf::RectangleShape *body, sf::Sprite *sprite):
	HalfSize(HalfSize), Position(Position), body(*body), sprite(*sprite)
{
}

const bool &Collider::checkCollision(Collider other)
{
	sf::Vector2f otherPosition = other.Position;
	sf::Vector2f otherHalfSize = other.HalfSize;
	sf::Vector2f thisPosition = Position;
	sf::Vector2f thisHalfSize = HalfSize;

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;
	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		if (intersectX > intersectY)
		{
			if (deltaX > 0.0f)
			{
				Move(intersectX * (0.0f), 0.0f);
				other.MoveSprite(-intersectX, 0.0f);
			}
			else
			{
				Move(-intersectX * (0.0f), 0.0f);
				other.MoveSprite(intersectX, 0.0f);
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				Move(0.0f, intersectY * (0.0f));
				other.MoveSprite(0.0f, -intersectY);
			}
			else
			{
				Move(0.0f, -intersectY * (0.0f));
				other.MoveSprite(0.0f, intersectY);
			}
		}
	}
	return false;
}

void Collider::updatePos(const sf::Vector2f& pos)
{
	Position = pos;
}

void Collider::updateHalfSize(const sf::Vector2f& sz)
{
	HalfSize = sz;
}
