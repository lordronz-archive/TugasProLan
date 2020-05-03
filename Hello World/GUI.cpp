#include "GUI.h"

GUI::GUI()
{
	if (!font.loadFromFile("DigitalMono.ttf"))
		std::cout << "ERROR LOADING FONT" << std::endl;

	health.setFont(font);
	health.setFillColor(sf::Color::Green);
	health.setOutlineThickness(1.f);
	health.setOrigin(10.f, 10.f);
	health.setCharacterSize(15);

	score.setFont(font);
	score.setFillColor(sf::Color(249, 224, 26));
	score.setOutlineThickness(1.f);
	score.setOrigin(10.f, 10.f);
	score.setCharacterSize(15);
}

void GUI::setHealthAndScore(int health, int score, sf::Vector2f pos)
{
	std::stringstream ss;
	ss << health;
	this->health.setPosition(pos.x - 110, pos.y + 60);
	this->health.setString("HP:" + ss.str());
	ss.str(std::string());
	ss.clear();
	ss << score;
	this->score.setPosition(pos.x + 50, pos.y + 60);
	this->score.setString("SCORE:" + ss.str());
}

sf::Text* GUI::getHealthGUI()
{
	return &health;
}

sf::Text* GUI::getScoreGUI()
{
	return &score;
}
