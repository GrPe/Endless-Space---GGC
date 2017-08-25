#pragma once
#include "SFML\Graphics.hpp"
#include "SpaceShip.hpp"

class Player : SpaceShip
{
public:
	Player(int _hp, float _speed, sf::Texture& texture);
	
	// return true is player is dead
	// positive value -> heal
	// negative value -> damage
	bool damageOrHeal(int x);

	//Reset stats of player
	void deadEnd(int _hp, float _speed);
	void deadEnd(int _hp, float _speed, sf::Texture texture);
};