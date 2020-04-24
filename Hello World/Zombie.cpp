#include "Zombie.h"

Zombie::Zombie() :speed(0.5), xPos(0), yPos(0)
{
	if (!zombieTexture.loadFromFile("Textures/zombie.png"))
		std::cout << "ERROR LOADING PLAYER TEXTURE" << std::endl;

	zombieTexture.setSmooth(true);
	sf::Vector2u textSize = zombieTexture.getSize();
	textSize.x /= 2;
	textSize.y /= 3;
	zombieSprite.setOrigin(sf::Vector2f(textSize.x / 2, textSize.y / 2));
	zombieSprite.setTexture(zombieTexture);
	zombieSprite.setTextureRect(sf::IntRect(textSize.x * 0, textSize.y * 1, textSize.x, textSize.y));
	zombieSprite.setPosition(sf::Vector2f(640, 300));
}

void Zombie::Move(sf::Vector2f playerPosition)
{
	// Make movement
	zombiePosition = zombieSprite.getPosition();
	float dx = zombiePosition.x - playerPosition.x;
	float dy = zombiePosition.y - playerPosition.y;

	float distance = sqrt((dx * dx) + (dy * dy));

	if (distance < 100)
	{
		direction = playerPosition - zombiePosition;
		normalizedDir = direction / sqrt(pow(direction.x, 2) + pow(direction.y, 2));

		speed = 0.5;

		//Rotate the Zombie relative to player position
		const float PI = 3.14159265;

		float rotation = (atan2(dy, dx)) * 180 / PI;

		zombieSprite.setRotation(rotation - 90);

		sf::Vector2f currentSpeed = normalizedDir * speed;

		zombieSprite.move(currentSpeed);
	}
}

Collider Zombie::GetCollider()
{
	sf::Vector2f spriteSize(
		zombieTexture.getSize().x / 2,
		zombieTexture.getSize().y / 3);
	return Collider(spriteSize / 2.0f, zombieSprite.getPosition(), nullptr, &zombieSprite);
}