#pragma once
#include <cstring>
#include <vector>
#include "SFML\Graphics.hpp"


class ResourceManager
{
private:
	sf::Texture* texturesTab;

public:
	explicit ResourceManager();
	sf::Texture& getRes(int x);
	~ResourceManager();
};