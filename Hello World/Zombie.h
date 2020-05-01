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
    sf::Sprite blood;
    void Move(sf::Vector2f playerPosition);
    void update(bool shot);
    sf::Vector2f zombiePosition;
    Collider GetCollider();
    int tiles[23][40];
    int healthPoints;
    bool bloodSplattered;

private:
    int xPos;
    int yPos;
    float speed;
    sf::Texture zombieTexture;
    sf::Texture bloodText;
    sf::Vector2f direction;
    sf::Vector2f normalizedDir;
    bool wallCheck(sf::Vector2f destination);
    sf::Vector2f playerLocB4Lost;
    sf::Vector2f randomLoc;
    sf::Vector2u bloodTextSize;
    sf::Clock clock0;
    sf::Clock bloodTimer;
    sf::Clock shotTimer;
    int bloodCount;
};

#endif // !ZOMBIE_H