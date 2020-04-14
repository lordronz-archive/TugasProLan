#include "Collider.h"

Collider::Collider(sf::Vector2f HalfSize, sf::Vector2f Position, sf::RectangleShape *body, sf::Sprite *sprite):
	HalfSize(HalfSize), Position(Position), body(*body), sprite(*sprite)
{
}

bool Collider::checkCollision(Collider other, float push)
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
		push = std::min(std::max(push, 0.0f), 1.0f);
		if (intersectX > intersectY)
		{
			if (deltaX > 0.0f)
			{
				Move(intersectX * (1.0f - push), 0.0f);
				other.MoveSprite(-intersectX * push, 0.0f);
			}
			else
			{
				Move(-intersectX * (1.0f - push), 0.0f);
				other.MoveSprite(intersectX * push, 0.0f);
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				Move(0.0f, intersectY * (1.0f - push));
				other.MoveSprite(0.0f, -intersectY * push);
			}
			else
			{
				Move(0.0f, -intersectY * (1.0f - push));
				other.MoveSprite(0.0f, intersectY * push);
			}
		}
	}
	return false;
}
