#include "stdafx.h"
#include "PlayerBullet.h"

void PlayerBullet::initializeContent(const ContentManager& contentManager)
{
	Bullet::initializeContent(contentManager);
	Bullet::setSoundBuffer(contentManager.getPlayerGunSound());
	setTexture(contentManager.getGuardianAlyssaBmp());
	setTextureRect(sf::IntRect(264, 106, 15, 5));
	setRotation(90.0f);
}

void PlayerBullet::update(float elapsedTime)
{
	if (!isActive())
		return;

	move(sf::Vector2f(0, -Bullet::BULLET_SPEED * elapsedTime));
	Bullet::update(elapsedTime);
}
