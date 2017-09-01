#include "Player.hpp"
#include "Render.hpp"

Player::Player(int _hp, float _speed, sf::Texture& texture) : SpaceShip(_hp, _speed, texture)
{}

bool Player::damageOrHeal(int x)
{
	hp += x;
	if (hp > 0) return false;
	else return true;
}

void Player::moveLeft()
{
	sprite.move(-(1.0f/120.0f*speed),0);
}

void Player::moveRight()
{
	sprite.move(1.0f/120.0f*speed, 0);
}

void Player::shot(std::vector<Bullet>& listofBullets, sf::Texture& tx)
{
	Bullet tempbullet(sprite.getPosition().x, sprite.getPosition().y - sprite.getTexture()->getSize().y * 0.20f,tx,-1);
	listofBullets.push_back(tempbullet);
}

void Player::deadEnd(int _hp, float _speed)
{
	hp = _hp;
	speed = _speed;
}

void Player::deadEnd(int _hp, float _speed, sf::Texture& texture)
{
	hp = _hp;
	speed = _speed;
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x*0.5f, texture.getSize().y*0.5f);
	sprite.setScale(0.4f, 0.4f);
}
