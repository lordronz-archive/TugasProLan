#pragma once
#ifndef GAMEOVERHELP_H
#define GAMEOVERHELP_H
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

class GameOverHelp
{
public:
	GameOverHelp();
	void setScore();
	sf::Text text[3];
	void help();
	bool helpSelect(bool gameOver, sf::RenderWindow* window);
	bool select(bool gameOver, sf::RenderWindow* window);
	void setScore(unsigned int score);
	bool toggler;
	bool helpToggler;

private:
	sf::Font font;
	bool mouseClick;
};

#endif