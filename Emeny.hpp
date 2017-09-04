#pragma once
#include "SFML\Graphics.hpp"
#include "SpaceShip.hpp"
#include "Bullet.hpp"
#include <list>

class Enemy : public SpaceShip
{
public:
	Enemy(int _hp, float _speed, sf::Texture & texture);
	explicit Enemy(bool log = false) {}; // This constructor do nothing -- Warning!!!!
	void Destroy();
	void shot(std::list<Bullet>& listOfEnemyBullets, sf::Texture& tx);
	void moveLeft();
	void moveRight();
	void moveDown();
};