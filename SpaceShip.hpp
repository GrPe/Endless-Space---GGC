#pragma once
#include "SFML\Graphics.hpp"

class SpaceShip
{
protected:
	int hpCurrent;
	int hpMax;
	float speed;
	sf::Sprite sprite;

public:
	SpaceShip() {};
	SpaceShip(int _hp, float _speed, sf::Texture& texture);


	//GET FUNCTION
	int getHPMax() const { return hpMax; }
	int getHPCurrent() const { return hpCurrent; }
	float getSpeed() const { return speed; }
	sf::Sprite& getSprite() { return sprite; }

	//SET FUNCTION

	void changeSpeed(float newSpeed) { speed = newSpeed; }
};