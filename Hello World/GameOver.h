#pragma once
#ifndef GAMEOVER_H
#define GAMEOVER_H
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

class GameOver
{
public:
	GameOver();
	void setScore();
	sf::Text text[3];
	bool select(bool gameOver, sf::RenderWindow* window);
	void setScore(unsigned int score);
	bool toggler;

private:
	sf::Font font;
	bool mouseClick;
};

#endif