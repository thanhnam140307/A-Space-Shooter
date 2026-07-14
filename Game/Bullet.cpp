#include "stdafx.h"
#include "Bullet.h"
#include "ContentManager.h"
#include "game.h"

const float Bullet::BULLET_SPEED = 600;
const unsigned long long Bullet::TIME_TO_LIVE = 2000;

Bullet::Bullet(const sf::Vector2f& initialPosition, const sf::Vector2f& initialThrust)
	: GameObject()
{
	setPosition(initialPosition);
	move(initialThrust);
}

Bullet::Bullet(const Bullet& src)
	:GameObject(src)
{
	setPosition(src.getPosition());

	if (src.bulletSound.getBuffer())
		setSoundBuffer(*src.bulletSound.getBuffer());
}

void Bullet::update(float /*elapsedTime*/)
{
	if (getPosition().y < 0 || getPosition().y > Game::GAME_HEIGHT)
	{
		activate(false);
	}
}

void Bullet::fire(const sf::Vector2f& spritePosition)
{
	activate(true);
	setPosition(spritePosition);

	if (getPosition().y >= 0.0f)
		bulletSound.play();
}

void Bullet::initializeContent(const ContentManager& contentManager)
{
	GameObject::initializeContent(contentManager);
	setScale(2.0f, 2.0f);
}

void Bullet::setSoundBuffer(const sf::SoundBuffer& soundbuffer)
{
	bulletSound.setBuffer(soundbuffer);
}

