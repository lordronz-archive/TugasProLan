#include "Zombie.h"

Zombie::Zombie() :speed(0.5), xPos(0), yPos(0), tiles{0}, healthPoints(100), bloodCount(0), bloodSplattered(false), attackCount(0), dead(false), reallyDead(false)
{
	if (!zombieTexture.loadFromFile("Textures/zombie.png"))
		std::cout << "ERROR LOADING ZOMBIE TEXTURE" << std::endl;

	zombieTexture.setSmooth(true);
	sf::Vector2u textSize = zombieTexture.getSize();
	textSize.x /= 2;
	textSize.y /= 3;
	zombieSprite.setOrigin(sf::Vector2f(textSize.x / 2.0f, textSize.y / 2.0f));
	zombieSprite.setTexture(zombieTexture);
	zombieSprite.setTextureRect(sf::IntRect(textSize.x * 0, textSize.y * 1, textSize.x, textSize.y));

	if (!bloodText.loadFromFile("Textures/blood.png"))
		std::cout << "ERROR LOADING BLOOD TEXTURE" << std::endl;

	bloodTextSize = bloodText.getSize();
	bloodTextSize.x /= 6;
	blood.setOrigin(sf::Vector2f(bloodTextSize.x / 2.0f, bloodTextSize.y / 2.0f));
	blood.setTexture(bloodText);
	blood.setTextureRect(sf::IntRect(bloodTextSize.x * 0, bloodTextSize.y * 0, bloodTextSize.x, bloodTextSize.y));
	blood.setPosition(zombieSprite.getPosition());

	if (!zombieHurtBuffer.loadFromFile("Sound/ZombieHurt.ogg"))
		std::cout << "ERROR LOADING ZOMBIE SOUND" << std::endl;
	zombieHurt.setBuffer(zombieHurtBuffer);

	srand(static_cast<unsigned int>(time(NULL)));

	std::ifstream file("tiles.txt");
	if (file.is_open()) {
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

Zombie::~Zombie()
{

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

void Zombie::death()
{
	if (!dead)
		zombieSprite.setTextureRect(sf::IntRect(zombieTexture.getSize().x / 2 * 1, zombieTexture.getSize().y / 3 * 0, zombieTexture.getSize().x / 2, zombieTexture.getSize().y / 3));
	this->dead = true;
	reallyDead = deathTimer.getElapsedTime().asSeconds() > 2.0f ? true : false;
}

void Zombie::Move(sf::Vector2f playerPosition)
{
	// Make movement
	if (!dead) {
		zombiePosition = zombieSprite.getPosition();

		float dx = zombiePosition.x - playerPosition.x;
		float dy = zombiePosition.y - playerPosition.y;

		float distance = sqrt((dx * dx) + (dy * dy));

		if (distance < 200.f && !wallCheck(playerPosition)) {
			playerLocB4Lost = playerPosition;
			direction = playerPosition - zombiePosition;
			normalizedDir = direction / sqrt(pow(direction.x, 2) + pow(direction.y, 2));

			speed = .8f;

			//Rotate the Zombie relative to player position
			const float PI = 3.14159265f;

			float rotation = (atan2(dy, dx)) * 180 / PI;

			zombieSprite.setRotation(rotation - 90);

			sf::Vector2f currentSpeed = normalizedDir * speed;

			zombieSprite.move(currentSpeed);
		}
		else if (distance < 200.f && wallCheck(playerPosition)) {
			dx = zombiePosition.x - playerLocB4Lost.x;
			dy = zombiePosition.y - playerLocB4Lost.y;
			direction = playerLocB4Lost - zombiePosition;
			normalizedDir = direction / sqrt(pow(direction.x, 2) + pow(direction.y, 2));

			speed = .8f;

			const float PI = 3.14159265f;

			float rotation = (atan2(dy, dx)) * 180 / PI;

			zombieSprite.setRotation(rotation - 90);

			sf::Vector2f currentSpeed = normalizedDir * speed;

			zombieSprite.move(currentSpeed);
		}
		/*else if (distance > 220.f) {
			if (clock0.getElapsedTime().asSeconds() > 4.f) {
				do
				{
					randomLoc = sf::Vector2f(zombiePosition.x + (rand() % 2 == 0 ? rand() % 101 + 50 : rand() % 101 - 150), zombiePosition.y + (rand() % 2 == 0 ? rand() % 101 + 50 : rand() % 101 - 150));
				} while (wallCheck(randomLoc));
				clock0.restart();
			}
			dx = zombiePosition.x - randomLoc.x;
			dy = zombiePosition.y - randomLoc.y;
			direction = randomLoc - zombiePosition;
			normalizedDir = direction / sqrt(pow(direction.x, 2) + pow(direction.y, 2));

			speed = .5f;

			const float PI = 3.14159265f;

			float rotation = (atan2(dy, dx)) * 180 / PI;

			zombieSprite.setRotation(rotation - 90);

			sf::Vector2f currentSpeed = normalizedDir * speed;

			zombieSprite.move(currentSpeed);
		}*/
		zombieSprite.setTextureRect(sf::IntRect(zombieTexture.getSize().x / 2 * 0, zombieTexture.getSize().y / 3 * 1, zombieTexture.getSize().x / 2, zombieTexture.getSize().y / 3));

	}
}

void Zombie::update(bool shot, sf::Vector2f playerPosition, bool midNight)
{
	float distance = sqrt(pow((playerPosition.x - zombieSprite.getPosition().x), 2) + pow((playerPosition.y - zombieSprite.getPosition().y), 2));

	bloodSplattered = bloodSplattered && shotTimer.getElapsedTime().asSeconds() > 1.0f ? false : bloodSplattered;
	
	blood.setPosition(zombieSprite.getPosition());
	if (bloodTimer.getElapsedTime().asSeconds() > .2f) {
		++bloodCount;
		bloodTimer.restart();
	}
	bloodCount = bloodCount > 5 ? 0 : bloodCount;
	blood.setTextureRect(sf::IntRect(bloodTextSize.x * bloodCount, bloodTextSize.y * 0, bloodTextSize.x, bloodTextSize.y));
	if (shot) {
		healthPoints = midNight ? healthPoints -= 35 : healthPoints -=50;
		bloodSplattered = true;
		shotTimer.restart();
		zombieHurt.setVolume(std::min(std::max((100.f - distance / 5.f), 1.f), 100.f));
		zombieHurt.play();
	}
	if (healthPoints <= 0)
		death();
	else
		deathTimer.restart();
}

void Zombie::setLocation()
{
	sf::Vector2f zombieLoc[12];
	zombieLoc[0] = sf::Vector2f(352.f, 64.f);
	zombieLoc[1] = sf::Vector2f(64.f, 352.f);
	zombieLoc[2] = sf::Vector2f(320.f, 384.f);
	zombieLoc[3] = sf::Vector2f(320.f, 400.f);
	zombieLoc[4] = sf::Vector2f(544.f, 672.f);
	zombieLoc[5] = sf::Vector2f(644.f, 672.f);
	zombieLoc[6] = sf::Vector2f(832.f, 480.f);
	zombieLoc[7] = sf::Vector2f(832.f, 64.f);
	zombieLoc[8] = sf::Vector2f(960.f, 360.f);
	zombieLoc[9] = sf::Vector2f(544.f, 64.f);
	zombieLoc[10] = sf::Vector2f(64.f, 300.f);
	zombieLoc[11] = sf::Vector2f(1152.f, 32.f);
	zombieSprite.setPosition(zombieLoc[rand() % 12]);
}

bool Zombie::attack()
{
	if (!dead) {
		bool attacking = false;
		if (attackTimer.getElapsedTime().asSeconds() > .5f) {
			++attackCount;
			attackTimer.restart();
			attacking = true;
		}
		attackCount = attackCount > 1 ? 0 : attackCount;
		zombieSprite.setTextureRect(sf::IntRect(zombieTexture.getSize().x / 2 * attackCount, zombieTexture.getSize().y / 3 * 1, zombieTexture.getSize().x / 2, zombieTexture.getSize().y / 3));
		return attacking;
	}
}

Collider Zombie::GetCollider()
{
	sf::Vector2f spriteSize(
		zombieTexture.getSize().x / 2.0f,
		zombieTexture.getSize().y / 3.0f);
	return Collider(spriteSize / 2.0f, zombieSprite.getPosition(), nullptr, &zombieSprite);
}

sf::Sprite* Zombie::getSprite()
{
	return &zombieSprite;
}
