#pragma once
#include "SFML\Graphics.hpp"
#include "SpaceShip.hpp"
#include "Bullet.hpp"

class Player : public SpaceShip
{
public:
	Player() {};
	Player(int _hp, float _speed, sf::Texture& texture);

	// return true is player is dead
	// positive value -> heal
	// negative value -> damage
	bool damageOrHeal(int x);

	//Movement
	void moveLeft();
	void moveRight();

	//Shot
	void shot(std::vector<Bullet>& listofBullets, sf::Texture& tx);


	//Reset stats of player
	void deadEnd(int _hp, float _speed);
	void deadEnd(int _hp, float _speed, sf::Texture& texture);
};