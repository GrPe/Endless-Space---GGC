#pragma once
#include "SFML\Graphics.hpp"
#include "SpaceShip.hpp"
#include "Bullet.hpp"

class Enemy : public SpaceShip
{
public:
	Enemy(int _hp, float _speed, sf::Texture & texture);
	void Destroy();
	void shot(std::vector<Bullet>& listOfEnemyBullets, sf::Texture& tx);
};