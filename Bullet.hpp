#pragma once
#include "SFML\Graphics.hpp"

class Bullet
{
private:
	sf::Sprite sprite;
	float speed;

public:
	explicit Bullet(const float x,float y,sf::Texture& tx, float s = 1200.0f);
	explicit Bullet() {};

	sf::Sprite& getSprite();
};