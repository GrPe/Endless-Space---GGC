#include "Player.hpp"

Player::Player(int _hp, float _speed, sf::Texture& texture) : SpaceShip(_hp, _speed, texture)
{}

bool Player::damageOrHeal(int x)
{
	hp += x;
	if (hp > 0) return false;
	else return true;
}

void Player::deadEnd(int _hp, float _speed)
{
	hp = _hp;
	speed = _speed;
}

void Player::deadEnd(int _hp, float _speed, sf::Texture texture)
{
	hp = _hp;
	speed = _speed;
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x*0.5f, texture.getSize().y*0.5f);
}
