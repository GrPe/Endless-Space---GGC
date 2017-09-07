#include "SpaceShip.hpp"

SpaceShip::SpaceShip(int _hp, float _speed, sf::Texture & texture) : hpMax(_hp),hpCurrent(_hp), speed(_speed)
{
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x*0.5f, texture.getSize().y*0.5f);
}
