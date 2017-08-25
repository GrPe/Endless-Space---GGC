#pragma once
#include <map>
#include "SFML\Graphics.hpp"

enum class Types { Enemy1, Enemy2, Enemy3, Enemy4, Player, Bullet, Building};

class ResourceManager
{
private:
	std::map<Types, sf::Texture> resourcesMap;

public:
	explicit ResourceManager() {};
	sf::Texture getRes(Types type);
	~ResourceManager();
};