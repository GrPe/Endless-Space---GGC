#include "Building.hpp"

Building::Building(ResourceManager & rs)
{
	hpCurrent = hpMax;
	for (int i = 0; i < 5; i++) textures.push_back(sf::Texture(rs.getTexture(6 + i)));
	sprite.setTexture(textures[0]);
	sprite.setOrigin(textures[0].getSize().x * 0.5f, textures[0].getSize().y*0.5f);
	sprite.setScale(1.2f, 1.2f);
}

void Building::getDamage()
{
	hpCurrent--;
	if (hpCurrent > 0) sprite.setTexture(textures[5 - hpCurrent]);
}
