#include "Menu.h"

Menu::Menu()
	:selectedItemIndex(0), exit(false), play(false), mouseClick(false), help(false), menuBar(sf::Quads, 4)
{

	if (!font.loadFromFile("DoubleFeature.ttf"))
		std::cout << "ERROR LOADING FONT" << std::endl;

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("PLAY");
	menu[0].setOrigin(sf::Vector2f(30, 0));
	menu[0].setPosition(sf::Vector2f(1280 / 2.0f, 720 / (MAX + 1) * 1.5f));
	menu[0].setOutlineThickness(3.f);

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("HELP");
	menu[1].setOrigin(sf::Vector2f(30, 0));
	menu[1].setPosition(sf::Vector2f(1280 / 2.0f, 720 / (MAX + 1) * 2.5f));
	menu[1].setOutlineThickness(3.f);

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("EXIT");
	menu[2].setOrigin(sf::Vector2f(30, 0));
	menu[2].setPosition(sf::Vector2f(1280 / 2.0f, 720 / (MAX + 1) * 3.5f));
	menu[2].setOutlineThickness(3.f);

	menuBar[0].position = sf::Vector2f(0, menu[0].getPosition().y);
	menuBar[0].color = sf::Color(49, 247, 148, 128);

	menuBar[1].position = sf::Vector2f(1280, menu[0].getPosition().y);
	menuBar[1].color = sf::Color(49, 247, 148, 128);

	menuBar[2].position = sf::Vector2f(1280, menu[0].getPosition().y + 1.5f * menu[0].getCharacterSize());
	menuBar[2].color = sf::Color(43, 126, 227, 128);

	menuBar[3].position = sf::Vector2f(0, menu[0].getPosition().y + 1.5f * menu[0].getCharacterSize());
	menuBar[3].color = sf::Color(43, 126, 227, 128);

	if (!menuSfxBuffer.loadFromFile("Sound/dmc_menu_select.wav"))
		std::cout << "ERROR LOADING MENU SOUND" << std::endl;

	menuSfx.setBuffer(menuSfxBuffer);

	if (!menuClickBuffer.loadFromFile("Sound/devil-may-cry-menu-sound.ogg"))
		std::cout << "ERROR LOADING MENU SOUND" << std::endl;

	menuClick.setBuffer(menuClickBuffer);

	if (!menuBg.loadFromFile("Textures/Desert.png"))
		std::cout << "ERROR LOADING MENU BG IMAGE" << std::endl;
}

Menu::~Menu() {}

sf::VertexArray* Menu::drawMenuBar()
{
	return &menuBar;
}

sf::Text* Menu::menuDraw()
{
	return menu;
}

sf::Texture* Menu::drawMenuBg()
{
	return &menuBg;
}

int Menu::getPressedItem()
{
	menuClick.play();
	return selectedItemIndex;
}

bool Menu::checkMenuPlay()
{
	return play;
}

bool Menu::checkExit()
{
	return exit;
}

bool Menu::checkHelp()
{
	return help;
}

void Menu::moveUp()
{
	if (selectedItemIndex - 1 >= 0) {
		menuSfx.play();
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		--selectedItemIndex;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
		menuBar[0].position = sf::Vector2f(0, menu[selectedItemIndex].getPosition().y);
		menuBar[0].color = sf::Color(49, 247, 148, 128);

		menuBar[1].position = sf::Vector2f(1280, menu[selectedItemIndex].getPosition().y);
		menuBar[1].color = sf::Color(49, 247, 148, 128);

		menuBar[2].position = sf::Vector2f(1280, menu[selectedItemIndex].getPosition().y + 1.5f * menu[selectedItemIndex].getCharacterSize());
		menuBar[2].color = sf::Color(43, 126, 227, 128);

		menuBar[3].position = sf::Vector2f(0, menu[selectedItemIndex].getPosition().y + 1.5f * menu[selectedItemIndex].getCharacterSize());
		menuBar[3].color = sf::Color(43, 126, 227, 128);
	}
	else {
		menuSfx.play();
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex = 2;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
		menuBar[0].position = sf::Vector2f(0, menu[selectedItemIndex].getPosition().y);
		menuBar[0].color = sf::Color(49, 247, 148, 128);

		menuBar[1].position = sf::Vector2f(1280, menu[selectedItemIndex].getPosition().y);
		menuBar[1].color = sf::Color(49, 247, 148, 128);

		menuBar[2].position = sf::Vector2f(1280, menu[selectedItemIndex].getPosition().y + 1.5f * menu[selectedItemIndex].getCharacterSize());
		menuBar[2].color = sf::Color(43, 126, 227, 128);

		menuBar[3].position = sf::Vector2f(0, menu[selectedItemIndex].getPosition().y + 1.5f * menu[selectedItemIndex].getCharacterSize());
		menuBar[3].color = sf::Color(43, 126, 227, 128);
	}
}

void Menu::moveDown()
{
	if (selectedItemIndex + 1 < MAX) {
		menuSfx.play();
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		++selectedItemIndex;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
		menuBar[0].position = sf::Vector2f(0, menu[selectedItemIndex].getPosition().y);

		menuBar[1].position = sf::Vector2f(1280, menu[selectedItemIndex].getPosition().y);

		menuBar[2].position = sf::Vector2f(1280, menu[selectedItemIndex].getPosition().y + 1.5f * menu[selectedItemIndex].getCharacterSize());

		menuBar[3].position = sf::Vector2f(0, menu[selectedItemIndex].getPosition().y + 1.5f * menu[selectedItemIndex].getCharacterSize());
	}
	else {
		menuSfx.play();
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex = 0;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
		menuBar[0].position = sf::Vector2f(0, menu[selectedItemIndex].getPosition().y);

		menuBar[1].position = sf::Vector2f(1280, menu[selectedItemIndex].getPosition().y);

		menuBar[2].position = sf::Vector2f(1280, menu[selectedItemIndex].getPosition().y + 1.5f * menu[selectedItemIndex].getCharacterSize());

		menuBar[3].position = sf::Vector2f(0, menu[selectedItemIndex].getPosition().y + 1.5f * menu[selectedItemIndex].getCharacterSize());
	}
}

void Menu::mouseSelect(sf::RenderWindow* window, bool play, bool help)
{
	this->play = play;
	this->help = help;

	if (play) {
		selectedItemIndex = 0;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
		menu[1].setFillColor(sf::Color::White);
		menu[2].setFillColor(sf::Color::White);
		menuBar[0].position = sf::Vector2f(0, menu[selectedItemIndex].getPosition().y);

		menuBar[1].position = sf::Vector2f(1280, menu[selectedItemIndex].getPosition().y);

		menuBar[2].position = sf::Vector2f(1280, menu[selectedItemIndex].getPosition().y + 1.5f * menu[selectedItemIndex].getCharacterSize());

		menuBar[3].position = sf::Vector2f(0, menu[selectedItemIndex].getPosition().y + 1.5f * menu[selectedItemIndex].getCharacterSize());
	}

	if (!play) {
		sf::Vector2f mousePixelPos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
		if (menu[0].getGlobalBounds().contains(mousePixelPos)) {
			if (selectedItemIndex != 0)
				menuSfx.play();
			selectedItemIndex = 0;
			menu[selectedItemIndex].setFillColor(sf::Color::Red);
			menuBar[0].position = sf::Vector2f(0, menu[selectedItemIndex].getPosition().y);

			menuBar[1].position = sf::Vector2f(1280, menu[selectedItemIndex].getPosition().y);

			menuBar[2].position = sf::Vector2f(1280, menu[selectedItemIndex].getPosition().y + 1.5f * menu[selectedItemIndex].getCharacterSize());

			menuBar[3].position = sf::Vector2f(0, menu[selectedItemIndex].getPosition().y + 1.5f * menu[selectedItemIndex].getCharacterSize());

			menu[1].setFillColor(sf::Color::White);
			menu[2].setFillColor(sf::Color::White);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				mouseClick = true;
			else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseClick) {
				this->play = true;
				menuClick.play();
				mouseClick = false;
			}
		}
		else if (menu[1].getGlobalBounds().contains(mousePixelPos)) {
			if (selectedItemIndex != 1)
				menuSfx.play();
			selectedItemIndex = 1;
			menuBar[0].position = sf::Vector2f(0, menu[selectedItemIndex].getPosition().y);

			menuBar[1].position = sf::Vector2f(1280, menu[selectedItemIndex].getPosition().y);

			menuBar[2].position = sf::Vector2f(1280, menu[selectedItemIndex].getPosition().y + 1.5f * menu[selectedItemIndex].getCharacterSize());

			menuBar[3].position = sf::Vector2f(0, menu[selectedItemIndex].getPosition().y + 1.5f * menu[selectedItemIndex].getCharacterSize());

			menu[selectedItemIndex].setFillColor(sf::Color::Red);
			menu[0].setFillColor(sf::Color::White);
			menu[2].setFillColor(sf::Color::White);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				mouseClick = true;
			else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseClick) {
				this->help = true;
				menuClick.play();
				mouseClick = false;
			}
		}
		else if (menu[2].getGlobalBounds().contains(mousePixelPos)) {
			if (selectedItemIndex != 2)
				menuSfx.play();
			selectedItemIndex = 2;
			menuBar[0].position = sf::Vector2f(0, menu[selectedItemIndex].getPosition().y);

			menuBar[1].position = sf::Vector2f(1280, menu[selectedItemIndex].getPosition().y);

			menuBar[2].position = sf::Vector2f(1280, menu[selectedItemIndex].getPosition().y + 1.5f * menu[selectedItemIndex].getCharacterSize());

			menuBar[3].position = sf::Vector2f(0, menu[selectedItemIndex].getPosition().y + 1.5f * menu[selectedItemIndex].getCharacterSize());

			menu[selectedItemIndex].setFillColor(sf::Color::Red);
			menu[0].setFillColor(sf::Color::White);
			menu[1].setFillColor(sf::Color::White);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				mouseClick = true;
			else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseClick) {
				exit = true;
				mouseClick = false;
			}
		}
		else
			mouseClick = false;
	}
}