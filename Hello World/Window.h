#pragma once

#include <math.h>

#include "Menu.h"

#ifndef WINDOW_H
#define WINDOW_H

class Window
{
private:
	void Setup(const std::string& l_title, const sf::Vector2u& l_size);
	void Destroy();
	void Create();
	sf::Vector2u winSize;
	std::string winTitle;
	bool m_isDone;
	bool m_isFullscreen;
	Menu menu;
	bool play;

public:
	Window();
	~Window();
	sf::RenderWindow window;
	void BeginDraw(); // Clear the window.
	void EndDraw(); // Display the changes.
	void Update();
	bool IsDone();
	bool IsFullscreen();
	sf::RenderWindow* getWindow();
	sf::Vector2u GetWindowSize();
	void ToggleFullscreen();
	void Draw(sf::Drawable& l_drawable);
	void View(sf::View &view);
	bool checkIfBegin();
};

#endif

