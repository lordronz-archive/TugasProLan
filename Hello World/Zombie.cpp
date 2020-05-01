#include "Zombie.h"

Zombie::Zombie() :speed(0.5), xPos(0), yPos(0), tiles{0}, healthPoints(100), bloodCount(0), bloodSplattered(false)
{
	if (!zombieTexture.loadFromFile("Textures/zombie.png"))
		std::cout << "ERROR LOADING PLAYER TEXTURE" << std::endl;

	zombieTexture.setSmooth(true);
	sf::Vector2u textSize = zombieTexture.getSize();
	textSize.x /= 2;
	textSize.y /= 3;
	zombieSprite.setOrigin(sf::Vector2f(textSize.x / 2.0f, textSize.y / 2.0f));
	zombieSprite.setTexture(zombieTexture);
	zombieSprite.setTextureRect(sf::IntRect(textSize.x * 0, textSize.y * 1, textSize.x, textSize.y));
	zombieSprite.setPosition(sf::Vector2f(640, 300));


	if (!bloodText.loadFromFile("Textures/blood.png"))
		std::cout << "ERROR LOADING BLOOD TEXTURE" << std::endl;

	bloodTextSize = bloodText.getSize();
	bloodTextSize.x /= 6;
	blood.setOrigin(sf::Vector2f(bloodTextSize.x / 2.0f, bloodTextSize.y / 2.0f));
	blood.setTexture(bloodText);
	blood.setTextureRect(sf::IntRect(bloodTextSize.x * 0, bloodTextSize.y * 0, bloodTextSize.x, bloodTextSize.y));
	blood.setPosition(zombieSprite.getPosition());
	blood.setScale(0.5f, 0.5f);

	srand(static_cast<unsigned int>(time(NULL)));

	std::ifstream file("tiles.txt");
	if (file.is_open())
	{
		int i = 0;
		int j = 0;
		while (file >> this->tiles[i][j])
		{
			++j;
			if (j % 40 == 0)
			{
				++i;
				j = 0;
			}
		}
	}
	file.close();
}

bool Zombie::wallCheck(sf::Vector2f destination)
{
	if (destination.x >= 1280 || destination.x <= 0 || destination.y >= 720 || destination.y <= 0)
		return true;

	float deltaX = zombieSprite.getPosition().x - destination.x;
	float deltaY = zombieSprite.getPosition().y - destination.y;
	int zombieTileX = static_cast<int>(zombieSprite.getPosition().x / 32);
	int zombieTileY = static_cast<int>(zombieSprite.getPosition().y / 32);
	int playerTileX = static_cast<int>(destination.x / 32);
	int playerTileY = static_cast<int>(destination.y / 32);
	int obs[] = {1, 2, 3, 4, 5, 6, 7};

	if (deltaX > 0)
	{
		for (int i = zombieTileX; i > playerTileX; --i)
		{
			for (int x : obs)
			{
				if (tiles[zombieTileY][i] == x)
					return true;
			}	
		}
	}
	else if (deltaX < 0)
	{
		for (int i = zombieTileX; i < playerTileX; ++i)
		{
			for (int x : obs)
			{
				if (tiles[zombieTileY][i] == x)
					return true;
			}
		}
	}
	if (deltaY > 0)
	{
		for (int i = zombieTileY; i > playerTileY; --i)
		{
			for (int x : obs)
			{
				if (tiles[i][zombieTileX] == x)
					return true;
			}
		}
	}
	else if (deltaY < 0)
	{
		for (int i = zombieTileY; i < playerTileY; ++i)
		{
			for (int x : obs)
			{
				if (tiles[i][zombieTileX] == x)
					return true;
			}
		}
	}
	return false;
}

void Zombie::Move(sf::Vector2f playerPosition)
{
	// Make movement
	zombiePosition = zombieSprite.getPosition();

	float dx = zombiePosition.x - playerPosition.x;
	float dy = zombiePosition.y - playerPosition.y;

	float distance = sqrt((dx * dx) + (dy * dy));

	if (distance < 300 && !wallCheck(playerPosition))
	{
		playerLocB4Lost = playerPosition;
		direction = playerPosition - zombiePosition;
		normalizedDir = direction / sqrt(pow(direction.x, 2) + pow(direction.y, 2));

		speed = 0.5;

		//Rotate the Zombie relative to player position
		const float PI = 3.14159265f;

		float rotation = (atan2(dy, dx)) * 180 / PI;

		zombieSprite.setRotation(rotation - 90);

		sf::Vector2f currentSpeed = normalizedDir * speed;

		zombieSprite.move(currentSpeed);
	}
	else if (distance < 300 && wallCheck(playerPosition))
	{
		dx = zombiePosition.x - playerLocB4Lost.x;
		dy = zombiePosition.y - playerLocB4Lost.y;
		direction = playerLocB4Lost - zombiePosition;
		normalizedDir = direction / sqrt(pow(direction.x, 2) + pow(direction.y, 2));

		speed = 0.5;

		const float PI = 3.14159265f;

		float rotation = (atan2(dy, dx)) * 180 / PI;

		zombieSprite.setRotation(rotation - 90);

		sf::Vector2f currentSpeed = normalizedDir * speed;

		zombieSprite.move(currentSpeed);
	}
	else
	{
		float walkTime = clock0.getElapsedTime().asSeconds();
		if (walkTime > 4)
		{
			do
			{
				randomLoc = sf::Vector2f(zombiePosition.x + (rand() % 2 == 0 ? rand() % 101 + 50 : rand() % 101 - 150), zombiePosition.y + (rand() % 2 == 0 ? rand() % 101 + 50 : rand() % 101 - 150));
			} while (wallCheck(randomLoc));
			clock0.restart();
		}
		std::cout << randomLoc.x << " " << randomLoc.y << std::endl;
		dx = zombiePosition.x - randomLoc.x;
		dy = zombiePosition.y - randomLoc.y;
		direction = randomLoc - zombiePosition;
		normalizedDir = direction / sqrt(pow(direction.x, 2) + pow(direction.y, 2));

		speed = 0.5;

		const float PI = 3.14159265f;

		float rotation = (atan2(dy, dx)) * 180 / PI;

		zombieSprite.setRotation(rotation - 90);

		sf::Vector2f currentSpeed = normalizedDir * speed;

		zombieSprite.move(currentSpeed);
	}
}

void Zombie::update(bool shot)
{
	bloodSplattered = shotTimer.getElapsedTime().asSeconds() > 1.0f && !shot ? false : true;
	
	blood.setPosition(zombieSprite.getPosition());
	if (bloodTimer.getElapsedTime().asSeconds() > .2f) {
		++bloodCount;
		bloodTimer.restart();
	}
	bloodCount = bloodCount > 5 ? 0 : bloodCount;
	blood.setTextureRect(sf::IntRect(bloodTextSize.x * bloodCount, bloodTextSize.y * 0, bloodTextSize.x, bloodTextSize.y));
	if (shot) {
		bloodSplattered = true;
		shotTimer.restart();
	}
}

Collider Zombie::GetCollider()
{
	sf::Vector2f spriteSize(
		zombieTexture.getSize().x / 2.0f,
		zombieTexture.getSize().y / 3.0f);
	return Collider(spriteSize / 2.0f, zombieSprite.getPosition(), nullptr, &zombieSprite);
}