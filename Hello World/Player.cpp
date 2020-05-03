#include "Player.h"

Player::Player() : fire(false), isFiring(false), dt1(0), dt2(0), healthPoints(500), isDead(false), stepCount(0)
{
	// Setting up class members.
	if (!playerTexture.loadFromFile("Textures/ct1.bmp"))
		std::cout << "ERROR LOADING PLAYER TEXTURE" << std::endl;

	playerTexture.setSmooth(true);
	textSize = playerTexture.getSize();
	textSize.x /= 2;
	textSize.y /= 3;
	playerCenter = sf::Vector2f(textSize.x / 2.0f, textSize.y / 2.0f);
	player.setScale(sf::Vector2f(0.5, 0.5));
	player.setOrigin(playerCenter);
	player.setTexture(playerTexture);
	player.setTextureRect(sf::IntRect(textSize.x * 0, textSize.y * 2, textSize.x, textSize.y));
	player.setPosition(sf::Vector2f(640, 360));

	if (!gunTexture.loadFromFile("Textures/awpfinal.png"))
		std::cout << "ERROR LOADING GUN TEXTURE" << std::endl;

	gunTexture.setSmooth(true);
	gun.setTexture(gunTexture);
	gun.setTextureRect(sf::IntRect((gunTexture.getSize().x / 2) * 1, gunTexture.getSize().y * 0, gunTexture.getSize().x / 2, gunTexture.getSize().y));
	gun.setScale(sf::Vector2f(.4f, .4f));
	gun.setOrigin(sf::Vector2f((gunTexture.getSize().x / 4.f), (gunTexture.getSize().y / 2.f + 50.f)));
	gun.setPosition(player.getPosition());

	if (!legsText.loadFromFile("Textures/legs.bmp"))
		std::cout << "ERROR LOADING PLAYER TEXTURE" << std::endl;
	legsTSize = legsText.getSize();
	legsTSize.x /= 8;
	legsTSize.y /= 2;
	legs.setScale(sf::Vector2f(.3f, .3f));
	legs.setOrigin(sf::Vector2f(legsTSize.x / 2.0f, legsTSize.y / 2.0f));
	legs.setTexture(legsText);
	legs.setTextureRect(sf::IntRect(textSize.x * 0, textSize.y * 0, legsTSize.x, legsTSize.y));
	legs.setPosition(sf::Vector2f(640, 360));

	if (!weaponSfxBuffer.loadFromFile("Sound/galil.wav"))
		std::cout << "ERROR LOADING WEAPON SOUND" << std::endl;

	weaponSfx.setBuffer(weaponSfxBuffer);

	if (!walkSfxBuffer.loadFromFile("Sound/pl_dirt1.wav"))
		std::cout << "ERROR LOADING WALKING SOUND" << std::endl;

	walkSfx.setBuffer(walkSfxBuffer);
	walkSfx.setVolume(80.f);
}

sf::Vector2f Player::getPlayerCenter()
{
	return playerCenter;
}

bool Player::Move(float moveX, float moveY)
{
	float elapsed = movementTime.getElapsedTime().asSeconds() * 50.f;
	float stepTime = stepTimer.getElapsedTime().asSeconds();
	sf::Vector2f pos = player.getPosition();
	if (moveX > 0 || moveY > 0) {
		moveX = pos.x + moveX >= 1280 ? 0 : moveX;
		moveY = pos.y + moveY >= 720 ? 0 : moveY;
	}
	if (moveX < 0 || moveY < 0) {
		moveX = pos.x + moveX <= 0 ? 0 : moveX;
		moveY = pos.y + moveY <= 0 ? 0 : moveY;
	}

	if (moveX == 0 && moveY == 0)
		return false;

	player.move(moveX * elapsed, moveY * elapsed);
	if (walkSfx.getStatus() == 0)
		walkSfx.play();
	
	if (stepTime > .1f) {
		++stepCount;
		stepTimer.restart();
	}
	stepCount = stepCount > 7 ? 0 : stepCount;
	legs.setTextureRect(sf::IntRect(textSize.x * stepCount, textSize.y * 0, legsTSize.x, legsTSize.y));
	return true;
}

void Player::movePlayer()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		Move(-.707f, -.707f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		Move(.707f, -.707f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		Move(-.707f, .707f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		Move(.707f, .707f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		Move(-1.f, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		Move(1.f, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		Move(0.f, -1.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		Move(0.f, 1.f);
	}
}

void Player::updatePlayer(sf::RenderWindow* window)
{
	dt1 = clock1.getElapsedTime().asSeconds();
	dt2 = clock2.getElapsedTime().asSeconds();
	isFiring = fire;

	sf::Vector2u windSize = sf::Vector2u(1280, 720);
	sf::Vector2f currentPosition = player.getPosition();
	mousePosition = sf::Mouse::getPosition(*window);
	worldPosition = window->mapPixelToCoords(mousePosition);

	const float PI = 3.141592653589793f;

	float a = worldPosition.x - currentPosition.x;
	float b = worldPosition.y - currentPosition.y;

	float rotation = (atan2(b, a)) * 180 / PI;

	if (dt2 > 0.2f)
	{
		fire = false;
		gun.setTextureRect(sf::IntRect((gunTexture.getSize().x / 2) * 1, gunTexture.getSize().y * 0, gunTexture.getSize().x / 2, gunTexture.getSize().y));
		clock2.restart();
	}

	movePlayer();

	movementTime.restart();

	player.setRotation(rotation + 90.f);
	gun.setRotation(rotation + 90.f);
	legs.setRotation(rotation + 90.f);

	if (dt1 > 2)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			fire = true;
			weaponSfx.play();
			gun.setTextureRect(sf::IntRect((gunTexture.getSize().x / 2) * 0, gunTexture.getSize().y * 0, gunTexture.getSize().x / 2, gunTexture.getSize().y));
			clock1.restart();
			clock2.restart();
		}
	}

	gun.setPosition(player.getPosition());
	legs.setPosition(player.getPosition());
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

sf::Sprite* Player::getLegsSprite()
{
	return &legs;
}

sf::Texture* Player::getPlayerTexture()
{
	return &playerTexture;
}