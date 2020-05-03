#include "GameOverHelp.h"

GameOverHelp::GameOverHelp() :toggler(false), mouseClick(false), helpToggler(false)
{
	if (!font.loadFromFile("DoubleFeature.ttf"))
		std::cout << "ERROR LOADING FONT" << std::endl;

	text[0].setFont(font);
	text[0].setFillColor(sf::Color::Red);
	text[0].setOutlineThickness(3.f);
	text[0].setCharacterSize(50);

	text[1].setFont(font);
	text[1].setFillColor(sf::Color::Red);
	text[1].setOutlineThickness(3.f);

	text[2].setFont(font);
	text[2].setFillColor(sf::Color::Red);
	text[2].setOutlineThickness(3.f);
}

void GameOverHelp::help()
{
	text[0].setString("JUST KILL THE ZOMBIES");
	text[0].setPosition(sf::Vector2f(1280 / 2.0f - 280.f, 720 / 2 - 300.f));
	text[1].setString("OK");
	text[1].setPosition(sf::Vector2f(1280 / 2.0f - 50.f, 720 / 2.f - 100.f));
}

bool GameOverHelp::helpSelect(bool gameOver, sf::RenderWindow* window)
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) ^ sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) && gameOver)
		helpToggler = true;
	if (helpToggler && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		return true;
	return false;
}

bool GameOverHelp::select(bool gameOver, sf::RenderWindow* window)
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) ^ sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) && gameOver)
		toggler = true;
	if (toggler && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		return true;
	if (text[2].getGlobalBounds().contains((sf::Vector2f)(sf::Mouse::getPosition(*window)))) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			mouseClick = true;
		if (mouseClick && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
			return true;
	}
	else
		mouseClick = false;
	return false;
}

void GameOverHelp::setScore(unsigned int score)
{
	text[0].setString("WASTED");
	text[0].setPosition(sf::Vector2f(1280 / 2.0f - 100.f, 720 / 2 - 300.f));
	std::stringstream ss;
	ss << score;
	this->text[1].setString("YOUR SCORE: " + ss.str());
	text[1].setPosition(sf::Vector2f(1280 / 2.0f - 120.f, 720 / 2.f - 100.f));
	text[2].setString("RETURN TO MAIN MENU");
	text[2].setPosition(sf::Vector2f(1280 / 2.0f - 150.f, 720 / 2.f + 50));
}



