#pragma once
#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <iostream>

class GUI
{
private:
	sf::Text health;
	sf::Text score;
	sf::Font font;

public:
	GUI();
	void setHealthAndScore(int health, int score, sf::Vector2f pos);
	sf::Text* getHealthGUI();
	sf::Text* getScoreGUI();
};

#endif // !GUI_H