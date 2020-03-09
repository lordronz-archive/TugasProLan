#pragma once
#ifndef GAME_H
#define GAME_H


#include <SFML/Graphics.hpp>
#include <cstdlib>

class Game
{
private:
	sf::RenderWindow *window;
	sf::Event sfEvent;
	void initWindow();

public:
	Game();
	void render();
	void run();
	void update();
	void updateSFMLEvents();
	~Game();
};

#endif
