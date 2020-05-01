#include "GUI.h"

GUI::GUI() : score(0)
{
	if (!font.loadFromFile("DigitalMono.ttf"))
		std::cout << "ERROR LOADING FONT" << std::endl;

	health.setFont(font);
	health.setFillColor(sf::Color::Green);
	health.setOutlineThickness(1.f);
	health.setOrigin(10.f, 10.f);
	health.setCharacterSize(15);
}

void GUI::setHealth(int health, sf::Vector2f pos)
{
	std::stringstream ss;
	ss << health;
	this->health.setPosition(pos.x - 110, pos.y + 60);
	this->health.setString("HP:" + ss.str());	
}

sf::Text* GUI::getHealthGUI()
{
	return &health;
}
