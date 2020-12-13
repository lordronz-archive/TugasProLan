#pragma once
#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <iostream>
#include "Collider.h"
#include <fstream>
#include <SFML/Audio.hpp>

class Zombie
{
public:
    Zombie();
    sf::Sprite zombieSprite;
    sf::Sprite blood;
    void Move(const sf::Vector2f &playerPosition);
    void update(bool &shot, const sf::Vector2f &playerPosition, bool &midNight);
    void setLocation();
    bool attack();
    sf::Vector2f zombiePosition;
    Collider GetCollider();
    sf::Sprite* getSprite();
    int tiles[23][40];
    int healthPoints;
    bool bloodSplattered;
    bool reallyDead;

protected:
    int xPos;
    int yPos;
    float speed;
    sf::Texture zombieTexture;
    sf::Texture bloodText;
    sf::Vector2f direction;
    sf::Vector2f normalizedDir;
    bool wallCheck(const sf::Vector2f& destination);
    sf::Vector2f playerLocB4Lost;
    sf::Vector2f randomLoc;
    sf::Vector2u bloodTextSize;
    sf::Clock clock0;
    sf::Clock bloodTimer;
    sf::Clock shotTimer;
    sf::Clock attackTimer;
    sf::Clock deathTimer;
    sf::SoundBuffer zombieHurtBuffer;
    sf::Sound zombieHurt;
    int bloodCount;
    int attackCount;
    bool dead;
    void death();
};

#endif // !ZOMBIE_H