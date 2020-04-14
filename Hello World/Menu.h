#pragma once

#ifndef MENU_H
#define MENU_H

#define MAX 3

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class Menu
{
public:
	Menu();
	~Menu();
	sf::Text* menuDraw();
	sf::Text* menuTitleDraw();
	void moveUp();
	void moveDown();
	void mouseSelect(sf::RenderWindow *window, bool play);
	int getPressedItem();
	bool checkMenuPlay();
	bool checkExit();
	sf::Texture* drawMenuBg();
	sf::VertexArray* drawMenuBar();

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX];
	sf::Text menuTitle;
	sf::SoundBuffer menuSfxBuffer;
	sf::Sound menuSfx;
	sf::Texture menuBg;
	sf::VertexArray menuBar;
	bool play;
	bool exit;
	bool mouseClick;
};

#endif

