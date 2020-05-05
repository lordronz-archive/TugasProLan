#include "Window.h"

Window::Window() :m_isDone(false), play(false), help(false)
{
	Setup("Hello World", sf::Vector2u(1280, 720));
	sf::Image icon;
	icon.loadFromFile("Textures/icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void Window::BeginDraw()
{
	window.clear();
}

void Window::EndDraw(bool gameOver)
{
	window.display();
	play ? window.setMouseCursorVisible(false) : window.setMouseCursorVisible(true);
	if (gameOver || help)
		window.setMouseCursorVisible(true);
}

void Window::Update()
{
	menu.mouseSelect(&window, play, help);
	play = menu.checkMenuPlay();
	m_isDone = menu.checkExit();
	help = menu.checkHelp();
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				if (!play && !help)
					menu.moveUp();
				break;

			case sf::Keyboard::Down:
				if (!play && !help)
					menu.moveDown();
				break;

			case sf::Keyboard::W:
				if (!play && !help)
					menu.moveUp();
				break;

			case sf::Keyboard::S:
				if (!play && !help)
					menu.moveDown();
				break;

			case sf::Keyboard::Enter:
				switch (menu.getPressedItem())
				{
				case 0:
					if (!play && !help)
						play = true;
					break;
				case 1:
					if (!play && !help)
						help = true;
					break;
				case 2:
					if (!play &&!help)
						m_isDone = true;
					break;
				}
				break;

			case sf::Keyboard::Escape:
				if (!help)
					play = !play;
				break;

			}
			break;
		case sf::Event::Closed:
			m_isDone = true;
			break;
		}
	}
}

bool Window::IsDone()
{
	return m_isDone;
}

bool Window::IsFullscreen()
{
	return m_isFullscreen;
}

void Window::View(sf::View& view)
{
	window.setView(view);
}

sf::Vector2u Window::GetWindowSize()
{
	return winSize;
}

void Window::ToggleFullscreen()
{
	m_isFullscreen = !m_isFullscreen;
	Destroy();
	Create();
}

sf::RenderWindow* Window::getWindow()
{
	return &window;
}

void Window::Draw(sf::Drawable& l_drawable)
{
	if (!play && !help)
	{
		window.draw(sf::Sprite(*menu.drawMenuBg()));
		window.draw(*menu.drawMenuBar());
		for (int i = 0; i < 3; ++i)
			window.draw(menu.menuDraw()[i]);
	}
	else
		window.draw(l_drawable);
}

bool Window::checkIfBegin()
{
	return play;
}

void Window::togglePlay()
{
	play = false;
}

void Window::Setup(const std::string& l_title, const sf::Vector2u& l_size)
{
	winTitle = l_title;
	winSize = l_size;
	m_isFullscreen = false;
	m_isDone = false;
	Create();
}

void Window::Destroy()
{
	window.close();
}

void Window::Create()
{
	auto style = (m_isFullscreen ? sf::Style::Fullscreen
		: sf::Style::Titlebar | sf::Style::Close);
	window.create({ winSize.x, winSize.y, 32 },
		winTitle, style);
	window.setFramerateLimit(60);
}