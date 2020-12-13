#include "Map.h"

void Map::load(const int *tiles)
{
    sf::Vector2f tileSize(32, 32);
    if (!m_tileset.loadFromFile("Textures/dust.png"))
        std::cout << "ERROR LOADING MAP TEXTURE\n";
    m_tileset.setSmooth(true);
    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(40 * 23 * 4);

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < 40; ++i)
        for (unsigned int j = 0; j < 23; ++j)
        {
            // get the current tile number
            int tileNumber = tiles[i + j * 40];

            // find its position in the tileset texture
            int tu = static_cast<int>(std::fmod(tileNumber, (m_tileset.getSize().x / tileSize.x)));
            int tv = static_cast<int>(tileNumber / (m_tileset.getSize().x / (tileSize.x)));

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &m_vertices[(i + j * 40) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_tileset;

    // draw the vertex array
    target.draw(m_vertices, states);
}
