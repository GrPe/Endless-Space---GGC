#pragma once
#include <cstring>
#include <vector>
#include "SFML\Graphics.hpp"


class ResourceManager
{
private:
	sf::Texture* texturesTab;
	const unsigned int MAXAMOUNTOFTEXTURES;

public:
	explicit ResourceManager() : MAXAMOUNTOFTEXTURES(0) {};
	explicit ResourceManager(int i);
	sf::Texture& getRes(unsigned int x);
	~ResourceManager();
};