#include "Player.hpp"
#include "Game.hpp"

Player::Player(int _hp, float _speed, sf::Texture& texture) : SpaceShip(_hp, _speed, texture)
{}

void Player::getDamage()
{
	hpCurrent--;
}

void Player::getHeal()
{
	if (hpCurrent < hpMax) hpCurrent++;
}

void Player::getHeal(unsigned int x)
{
	hpCurrent += x;
	if (hpCurrent > hpMax) hpCurrent = hpMax;
}

void Player::moveLeft()
{
	//Movement Limit 
	if(sprite.getPosition().x > 60.0f)
	sprite.move(-(1.0f/120.0f*speed),0.0f);
}

void Player::moveRight()
{
	//Movement Limit
	if(sprite.getPosition().x < 1860.0f)
	sprite.move(1.0f/120.0f*speed, 0);
}

void Player::shot(std::vector<Bullet>& listofBullets, sf::Texture& tx)
{
	if (listofBullets.size() < 1)
	{
		Bullet tempbullet(sprite.getPosition().x, sprite.getPosition().y - sprite.getTexture()->getSize().y * 0.20f, tx, -1);
		listofBullets.push_back(tempbullet);
		soundShot.play();
	}
}

void Player::deadEnd(int _hp, float _speed)
{
	hpCurrent = _hp;
	hpMax = _hp;
	speed = _speed;
}

void Player::deadEnd(int _hp, float _speed, sf::Texture& texture, sf::SoundBuffer& sb)
{
	hpCurrent = _hp;
	hpMax = _hp;
	speed = _speed;
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x*0.5f, texture.getSize().y*0.5f);
	sprite.setScale(0.4f, 0.4f);
	soundShot.setBuffer(sb);
	soundShot.setVolume(50.0f);
}
