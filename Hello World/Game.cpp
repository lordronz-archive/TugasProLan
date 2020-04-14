#include "Game.h"

Game::Game() :
	view(sf::View(sf::FloatRect(640, 360, 256, 144))), walls {wall, wall ,wall}
{
	if (!cursorText.loadFromFile("Textures/pointer.png"))
	{
		std::cout << "ERROR LOADING CURSOR TEXTURE" << std::endl;
	}
	sf::Vector2u textSize = cursorText.getSize();
	textSize.x /= 2;
	textSize.y /= 2;
	cursor.setTexture(cursorText);
	cursor.setTextureRect(sf::IntRect(textSize.x * 0, textSize.y * 0, textSize.x, textSize.y));
	cursor.setOrigin(textSize.x / 2, textSize.y / 2);
	cursor.setScale(0.25, 0.25);
	walls[0].initWall(sf::Vector2f(64.0f, 96.0f), sf::Vector2f(416.0f, 656.0f));
	walls[1].initWall(sf::Vector2f(64.0f, 64.0f), sf::Vector2f(32.0f, 672.0f));
	walls[2].initWall(sf::Vector2f(128.0f, 480.0f), sf::Vector2f(192.0f, 464.0f));
	
	const int tiles[] =
	{
		21, 21, 21, 21, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 66, 67, 66, 67, 66, 67, 66, 67, 20, 1 , 1 , 1 , 1 , 1 , 1 , 1 , 61, 62,
		21, 21, 21, 21, 1 , 1 , 1 , 25, 25, 26, 26, 27, 27, 27, 27, 27, 25, 25, 35, 36, 36, 36, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 66, 67,
		21, 21, 21, 21, 1 , 25, 26, 27, 25, 13, 13, 3 , 3 , 3 , 3 , 3 , 8 , 9 , 8 , 9 , 8 , 9 , 1 , 1 , 1 , 51, 9 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 78,
		22, 1 , 4 , 4 , 2 , 75, 3 , 3 , 3 , 12, 1 , 1 , 1 , 27, 27, 25, 8 , 9 , 8 , 9 , 9 , 8 , 1 , 1 , 1 , 9 , 10, 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 77,
		2 , 1 , 1 , 2 , 3 , 3 , 3 , 12, 12, 12, 1 , 1 , 1 , 2 , 8 , 9 , 8 , 8 , 9 , 9 , 10, 10, 4 , 6 , 7 , 16, 8 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 78,
		21, 5 , 1 , 10, 12, 12, 11, 12, 10, 10, 1 , 1 , 1 , 1 , 2 , 10, 10, 10, 10, 10, 10, 10, 16, 16, 16, 52, 16, 8 , 15, 15, 9 , 24, 53, 53, 16, 16, 9 , 10, 3 , 78,
		21, 26, 25, 21, 3 , 8 , 2 , 2 , 2 , 8 , 1 , 1 , 1 , 1 , 1 , 1 , 10, 10, 10, 10, 10, 10, 16, 16, 8 , 16, 51, 8 , 9 , 9 , 8 , 24, 52, 52, 8 , 10, 10, 14, 4 , 78,
		21, 25, 25, 21, 3 , 2 , 2 , 2 , 8 , 8 , 10, 8 , 1 , 1 , 1 , 1 , 10, 10, 10, 21, 8 , 8 , 1 , 6 , 1 , 7 , 3 , 4 , 3 , 10, 9 , 1 , 61, 62, 8 , 16, 1 , 1 , 1 , 76,
		76, 27, 26, 21, 3 , 2 , 2 , 2 , 16, 8 , 10, 8 , 1 , 1 , 1 , 1 , 9 , 9 , 10, 51, 52, 9 , 1 , 2 , 3 , 5 , 3 , 1 , 2 , 10, 8 , 1 , 66, 67, 8 , 54, 1 , 1 , 1 , 75,
		74, 25, 27, 21, 3 , 2 , 2 , 2 , 16, 8 , 10, 8 , 1 , 1 , 1 , 1 , 8 , 9 , 10, 24, 24, 8 , 8 , 8 , 4 , 4 , 1 , 7 , 1 , 16, 16, 1 , 1 , 1 , 16, 52, 1 , 1 , 1 , 79,
		75, 31, 27, 21, 3 , 2 , 2 , 2 , 16, 8 , 10, 8 , 1 , 1 , 1 , 1 , 8 , 9 , 10, 28, 29, 24, 16, 16, 16, 16, 8 , 1 , 74, 10, 10, 1 , 1 , 1 , 16, 16, 1 , 1 , 1 , 21,
		21, 31, 48, 22, 3 , 2 , 2 , 2 , 16, 8 , 10, 8 , 1 , 1 , 1 , 1 , 8 , 9 , 10, 30, 31, 8 , 16, 16, 16, 16, 8 , 7 , 3 , 24, 54, 1 , 1 , 1 , 10, 8 , 1 , 1 , 1 , 21,
		21, 29, 49, 10, 3 , 2 , 2 , 2 , 16, 8 , 10, 8 , 1 , 1 , 1 , 1 , 9 , 8 , 10, 20, 11, 16, 5 , 1 , 5 , 16, 16, 3 , 1 , 9 , 10, 1 , 1 , 1 , 16, 10, 1 , 1 , 1 , 21,
		12, 29, 49, 10, 3 , 2 , 2 , 2 , 16, 8 , 10, 8 , 1 , 1 , 1 , 1 , 8 , 25, 10, 8 , 53, 52, 4 , 1 , 3 , 16, 16, 1 , 5 , 9 , 10, 1 , 1 , 1 , 10, 9 , 1 , 1 , 1 , 21,
		21, 29, 49, 10, 3 , 2 , 2 , 2 , 16, 8 , 10, 8 , 1 , 1 , 1 , 1 , 8 , 25, 10, 16, 16, 16, 4 , 5 , 1 , 16, 16, 2 , 6 , 10, 10, 1 , 1 , 1 , 10, 9 , 1 , 1 , 1 , 21,
		21, 29, 49, 10, 3 , 2 , 2 , 2 , 25, 8 , 10, 8 , 1 , 1 , 1 , 1 , 8 , 24, 10, 16, 16, 16, 1 , 1 , 1 , 16, 16, 1 , 6 , 9 , 10, 76, 1 , 1 , 8 , 10, 1 , 1 , 1 , 21,
		21, 29, 49, 10, 3 , 2 , 2 , 2 , 26, 8 , 10, 8 , 10, 1 , 1 , 1 , 24, 24, 10, 8 , 16, 16, 4 , 6 , 4 , 16, 16, 4 , 20, 15, 15, 1 , 1 , 1 , 9 , 16, 1 , 1 , 1 , 21,
		21, 29, 49, 10, 3 , 2 , 2 , 2 , 9 , 9 , 8 , 9 , 10, 10, 1 , 1 , 24, 24, 10, 27, 16, 16, 1 , 7 , 1 , 8 , 8 , 51, 57, 24, 25, 1 , 1 , 1 , 8 , 16, 1 , 1 , 1 , 16,
		21, 47, 49, 10, 3 , 2 , 2 , 2 , 8 , 8 , 9 , 8 , 9 , 9 , 1 , 1 , 24, 24, 24, 10, 25, 16, 1 , 1 , 1 , 52, 51, 56, 52, 25, 24, 1 , 1 , 1 , 9 , 8 , 1 , 1 , 1 , 16,
		21, 48, 49, 12, 3 , 2 , 2 , 2 , 8 , 9 , 8 , 8 , 22, 22, 1 , 1 , 25, 25, 24, 10, 25, 16, 7 , 5 , 3 , 2 , 5 , 6 , 2 , 3 , 2 , 1 , 1 , 1 , 9 , 8 , 1 , 1 , 1 , 16,
		61, 62, 49, 12, 3 , 2 , 2 , 2 , 9 , 9 , 9 , 9 , 23, 23, 1 , 1 , 24, 24, 25, 10, 25, 16, 3 , 3 , 1 , 1 , 2 , 4 , 1 , 7 , 1 , 1 , 1 , 1 , 10, 16, 1 , 1 , 1 , 16,
		66, 67, 49, 12, 3 , 2 , 2 , 2 , 8 , 8 , 8 , 9 , 22, 23, 1 , 1 , 25, 26, 27, 10, 26, 26, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
		47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 46,
	};
	map.load(tiles);
}

Game::~Game()
{}

void Game::Update() {
	sf::Vector2f playerPos = player.getCharCoord();
	sf::RenderWindow* win = window.getWindow();
	float dt = clock.getElapsedTime().asSeconds();
	window.Update(); // Update window events.
	cursor.setPosition(player.getMousePos());

	if (window.checkIfBegin())
	{
		player.updatePlayer(win);
		if (dt > 2)
		{
			//fire
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				b1.fire(win, playerPos);
				bullets.push_back(Bullet(b1));

				clock.restart();
			}
		}
		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i].projectile.move(bullets[i].currVelocity);
			if (bullets[i].projectile.getPosition().x < 0 || bullets[i].projectile.getPosition().x > 1280
				|| bullets[i].projectile.getPosition().y < 0 || bullets[i].projectile.getPosition().y > 720)
			{
				//removing bullets out of the map
				bullets.erase(bullets.begin() + i);
				bullets.shrink_to_fit();
			}
		}
	}

	for (size_t i = 0; i < walls.size(); i++)
	{
		walls[i].GetCollider().checkCollision(player.GetCollider(), 1.0f);
	}
		
	if (!window.checkIfBegin())
	{
		view.setSize(sf::Vector2f(1280, 720));
		view.setCenter(sf::Vector2f(640, 360));
	}
		
	else if (window.checkIfBegin())
	{
		view.setSize(sf::Vector2f(256, 144));
		view.setCenter(playerPos);
	}
}

void Game::Render()
{
	window.View(view);
	window.BeginDraw();
	window.Draw(map);
	window.Draw(*player.getPlayerSprite());
	window.Draw(*player.getGunSprite());
	if (player.getFireStatus())
		window.Draw(*player.getGunshotSprite());
	for (size_t i = 0; i < bullets.size(); i++)
	{
		window.Draw(bullets[i].projectile);
	}
	window.Draw(cursor);
	window.EndDraw();
}

Window* Game::GetWindow()
{
	return &window;
}

void Game::Run()
{
	while (!window.IsDone())
	{
		Update();
		Render();
	}
}

