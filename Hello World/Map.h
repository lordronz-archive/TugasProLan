#pragma once
#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Map : public sf::Drawable, public sf::Transformable
{
private:
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;

public:
	void load(const int* tiles);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif