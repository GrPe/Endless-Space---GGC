#include "Bullet.hpp"

Bullet::Bullet(const float x,const float y,sf::Texture& tx, int d, float s)
{
	direction = d;
	sprite.setTexture(tx);
	sprite.setOrigin(tx.getSize().x*0.5f, tx.getSize().y*0.5f);
	sprite.setScale(0.5f, 0.5f);
	sprite.setPosition(x, y);
	speed = s;
}

void Bullet::move()
{
	sprite.move(0,direction*1.0f / 120.0f*speed);
}

sf::Sprite & Bullet::getSprite()
{
	return sprite;
}
