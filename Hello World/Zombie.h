#pragma once
#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <iostream>
#include "Collider.h"

class Zombie
{
public:
    Zombie();
    sf::Sprite zombieSprite;
    void Move(sf::Vector2f playerPosition);
    sf::Vector2f zombiePosition;
    Collider GetCollider();

private:
    int xPos;
    int yPos;
    float speed;
    sf::Texture zombieTexture;
    sf::Vector2f direction;
    sf::Vector2f normalizedDir;
};

#endif // !ZOMBIE_H