#include "Emeny.hpp"

Enemy::Enemy(int _hp, float _speed, sf::Texture & texture) : SpaceShip(_hp, _speed, texture)
{
	sprite.setOrigin(texture.getSize().x*0.5f, texture.getSize().y*0.5f);
	sprite.setScale(0.35f, 0.35f);
}


void Enemy::shot(std::vector<Bullet>& listOfEnemyBullets, sf::Texture & tx)
{
	
}

void Enemy::moveLeft()
{
	sprite.move(-1.0f / 120.0f * speed, 0.0f);
}

void Enemy::moveRight()
{
	sprite.move(1.0f / 120.0f * speed,0.0f);
}

void Enemy::moveDown()
{
	sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 20.0f);
}
