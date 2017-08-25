#pragma once
#include "SFML\Graphics.hpp"

class SpaceShip
{
protected:
	int hp;
	float speed;
	sf::Sprite sprite;

public:
	SpaceShip(int _hp, float _speed, sf::Texture& texture);


	//GET FUNCTION
	int getHP() const { return hp; }
	float getSpeed() const { return speed; }
	sf::Sprite& getSprite() { return sprite; }

	//SET FUNCTION

	void changeSpeed(float newSpeed) { speed = newSpeed; }
};