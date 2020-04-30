#pragma once
#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <iostream>
#include "Collider.h"
#include <fstream>

class Zombie
{
public:
    Zombie();
    sf::Sprite zombieSprite;
    void Move(sf::Vector2f playerPosition);
    sf::Vector2f zombiePosition;
    Collider GetCollider();
    int tiles[23][40];
    int healthPoints;

private:
    int xPos;
    int yPos;
    float speed;
    sf::Texture zombieTexture;
    sf::Vector2f direction;
    sf::Vector2f normalizedDir;
    bool wallCheck(sf::Vector2f destination);
    sf::Vector2f playerLocB4Lost;
    sf::Vector2f randomLoc;
    sf::Clock clock0;
};

#endif // !ZOMBIE_H