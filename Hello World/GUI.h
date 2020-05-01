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
	sf::Font font;
	std::stringstream ss;

public:
	GUI();
	int score;
	void setHealth(int health, sf::Vector2f pos);
	sf::Text* getHealthGUI();
};

#endif // !GUI_H