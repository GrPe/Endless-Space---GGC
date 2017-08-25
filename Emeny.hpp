#pragma once
#include "SFML\Graphics.hpp"
#include "SpaceShip.hpp"

class Enemy : SpaceShip
{
public:
	Enemy(int _hp, float _speed, sf::Texture & texture);
};