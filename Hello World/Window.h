#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <math.h>
#include "Menu.h"

class Window
{
private:
	void Setup(const std::string& l_title, const sf::Vector2u& l_size);
	void Create();
	sf::Vector2u winSize;
	std::string winTitle;
	bool m_isDone;
	bool m_isFullscreen;
	Menu menu;
	bool play;

public:
	Window();
	sf::RenderWindow window;
	void BeginDraw(); // Clear the window.
	void EndDraw(bool gameOver); // Display the changes.
	void Update();
	bool IsDone();
	sf::RenderWindow* getWindow();
	sf::Vector2u GetWindowSize();
	void Draw(sf::Drawable& l_drawable);
	void View(sf::View& view);
	bool checkIfBegin();
	void togglePlay();
	bool help;
};

#endif

