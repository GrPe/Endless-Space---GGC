#pragma once
#include "SFML\Graphics.hpp"
#include <vector>
#include "ResourceManager.hpp"

class Building
{
private:
	const int hpMax = 5;
	int hpCurrent;
	std::vector<sf::Texture> textures;
	sf::Sprite sprite;

public:
	Building(ResourceManager& rs);
	sf::Sprite& getSprite() { return sprite; };
	int getHPCurrent() const { return hpCurrent; };
	int getHPMax() const { return hpMax; };
	void getDamage();
};