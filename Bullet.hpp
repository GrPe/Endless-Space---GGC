#pragma once
#include "SFML\Graphics.hpp"

class Bullet
{
private:
	sf::Sprite sprite;
	float speed;
	int direction; // two value (-1 or 1)

public:
	explicit Bullet(const float x,float y,sf::Texture& tx,int d, float s = 1200.0f);
	explicit Bullet() {};
	void move();

	sf::Sprite& getSprite();
};