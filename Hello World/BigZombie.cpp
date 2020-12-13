#include "BigZombie.h"

BigZombie::BigZombie()
{
	healthPoints = 120;
	speed = 1.f;
	if (!zombieTexture.loadFromFile("Textures/zombie_peradaban.png"))
		std::cout << "ERROR LOADING BIG ZOMBIE TEXTURE\n";

	zombieTexture.setSmooth(true);
	sf::Vector2u textSize = zombieTexture.getSize();
	textSize.x /= 2;
	textSize.y /= 3;
	zombieSprite.setOrigin(sf::Vector2f(textSize.x / 2.0f, textSize.y / 2.0f));
	zombieSprite.setTexture(zombieTexture);
	zombieSprite.setTextureRect(sf::IntRect(textSize.x * 0, textSize.y * 1, textSize.x, textSize.y));
}