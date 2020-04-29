#include "Player.h"

Player::Player() : fire(false), dt1(0), dt2(0)
{
	// Setting up class members.
	if (!playerTexture.loadFromFile("Textures/ct1.bmp"))
		std::cout << "ERROR LOADING PLAYER TEXTURE" << std::endl;

	playerTexture.setSmooth(true);
	textSize = playerTexture.getSize();
	textSize.x /= 2;
	textSize.y /= 3;
	playerCenter = sf::Vector2f(textSize.x / 2, textSize.y / 2);
	player.setScale(sf::Vector2f(0.5, 0.5));
	player.setOrigin(playerCenter);
	player.setTexture(playerTexture);
	player.setTextureRect(sf::IntRect(textSize.x * 0, textSize.y * 2, textSize.x, textSize.y));
	player.setPosition(sf::Vector2f(640, 360));

	if (!gunTexture.loadFromFile("Textures/awp.png"))
		std::cout << "ERROR LOADING GUN TEXTURE" << std::endl;

	gunTexture.setSmooth(true);
	gun.setTexture(gunTexture);
	gun.setScale(sf::Vector2f(0.40, 0.40));
	gun.setOrigin(gunTexture.getSize().x / 2, gunTexture.getSize().y + 5);
	gun.setPosition(player.getPosition().x, player.getPosition().y);

	if (!gunshotTexture.loadFromFile("Textures/gunshot.png"))
		std::cout << "ERROR LOADING GUNSHOT TEXTURE" << std::endl;

	gunshot.setTexture(gunshotTexture);
	gunshot.setScale(sf::Vector2f(0.5, 0.5));
	gunshot.setOrigin(gunshotTexture.getSize().x / 2, gunshotTexture.getSize().y + 45);
	gunshot.setPosition(player.getPosition().x, player.getPosition().y);

	if (!weaponSfxBuffer.loadFromFile("Sound/galil.wav"))
		std::cout << "ERROR LOADING WEAPON SOUND" << std::endl;

	weaponSfx.setBuffer(weaponSfxBuffer);

	if (!walkSfxBuffer.loadFromFile("Sound/pl_dirt1.wav"))
		std::cout << "ERROR LOADING WALKING SOUND" << std::endl;

	walkSfx.setBuffer(walkSfxBuffer);

	/*std::ifstream file("tiles.txt");
	if (file.is_open())
	{
		int i = 0;
		int j = 0;
		while (file >> tiles[i][j])
		{
			++j;
			if (j % 40 == 0)
			{
				++i;
				j = 0;
			}
		}
	}
	file.close();*/
}

sf::Vector2f Player::getPlayerCenter()
{
	return playerCenter;
}

bool Player::Move(float moveX, float moveY)
{
	float elapsed = movementTime.getElapsedTime().asSeconds() * 50;
	sf::Vector2f pos = player.getPosition();
	if (moveX > 0 || moveY > 0) {
		if (pos.x + moveX >= 1280)
			moveX = 0;
		if (pos.y + moveY >= 720)
			moveY = 0;
	}
	if (moveX < 0 || moveY < 0) {
		if (pos.x + moveX <= 0)
			moveX = 0;
		if (pos.y + moveY <= 0)
			moveY = 0;
	}

	if (moveX == 0 && moveY == 0)
		return false;
	player.move(moveX * elapsed, moveY * elapsed);
	if (walkSfx.getStatus() == 0)
		walkSfx.play();
	return true;
}

void Player::movePlayer()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		Move(-.707f, -.707f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Move(.707f, -.707f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		Move(-.707f, .707f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Move(.707f, .707f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		Move(-1.f, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Move(1.f, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		Move(0.f, -1.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		Move(0.f, 1.f);
	}
}

void Player::updatePlayer(sf::RenderWindow* window)
{
	dt1 = clock1.getElapsedTime().asSeconds();
	dt2 = clock2.getElapsedTime().asSeconds();

	sf::Vector2u windSize = sf::Vector2u(1280, 720);
	sf::Vector2f currentPosition = player.getPosition();
	mousePosition = sf::Mouse::getPosition(*window);
	worldPosition = window->mapPixelToCoords(mousePosition);

	const float PI = float(3.141592653589793);

	float a = worldPosition.x - currentPosition.x;
	float b = worldPosition.y - currentPosition.y;

	float rotation = (atan2(b, a)) * 180 / PI;

	if (dt2 > 0.2)
	{
		fire = false;
		clock2.restart();
	}

	movePlayer();
	movementTime.restart();

	player.setRotation(rotation + 90);
	gun.setRotation(rotation + 90);
	gunshot.setRotation(rotation + 90);

	if (dt1 > 2)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			fire = true;
			weaponSfx.play();
			clock1.restart();
			clock2.restart();
		}
	}

	gun.setPosition(player.getPosition());
	gunshot.setPosition(player.getPosition());
}

bool Player::getFireStatus()
{
	return fire;
}

Collider Player::GetCollider()
{
	sf::Vector2f spriteSize(
		textSize.x * player.getScale().x,
		textSize.y * player.getScale().y);
	return Collider(spriteSize / 2.0f, player.getPosition(), nullptr, &player);
}

sf::Vector2f Player::getMousePos()
{
	return worldPosition;
}

sf::Vector2f Player::getCharCoord()
{
	return player.getPosition();
}

sf::Sprite* Player::getPlayerSprite() 
{
	return &player;
}

sf::Sprite* Player::getGunSprite()
{
	return &gun;
}

sf::Sprite* Player::getGunshotSprite()
{
	return &gunshot;
}