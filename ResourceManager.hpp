#pragma once
#include <map>
#include "SFML\Graphics.hpp"


class ResourceManager
{
private:
	std::map<std::string, sf::Texture> texturesMap;

public:
	explicit ResourceManager() {};
	sf::Texture& getRes(std::string type);
	~ResourceManager();
};