#pragma once
#include "SFML\Graphics.hpp"
#include "SpaceShip.hpp"

class Enemy : public SpaceShip
{
public:
	Enemy(int _hp, float _speed, sf::Texture & texture);
	void Destroy(sf::Time time);
};