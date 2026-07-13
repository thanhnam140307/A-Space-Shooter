#include "stdafx.h"
#include "SmartGun.h"
#include "game.h"

const float SmartGun::GAP = 50.0f;
const float SmartGun::SPEED = Level01::SPEED - 1.0f;

SmartGun::SmartGun() :
	GameObject()
{
}

SmartGun::SmartGun(const SmartGun& src) :
	GameObject(src)
{
	setPosition(src.getPosition());
}

void SmartGun::initializeContent(const ContentManager& contentManager)
{
	GameObject::initializeContent(contentManager);
	setTexture(contentManager.getSmartGunTexture());
}

void SmartGun::follow(const sf::Vector2f& position)
{
	if (!isActive())
		return;

	float dx = getPosition().x - position.x;
	float dy = getPosition().y - position.y;
	float distance = sqrt((dx * dx) + (dy * dy));

	if (distance > GAP)
	{
		float direction = atan2f(position.y - getPosition().y, position.x - getPosition().x);
		move(cos(direction) * SPEED, sin(direction) * SPEED);
	}
}

void SmartGun::spawn(const sf::Vector2f& position)
{
	setPosition(sf::Vector2f(position.x, position.y + GAP));
	activate(true);
}
