#include "stdafx.h"
#include "EnemyBullet.h"

void EnemyBullet::initializeContent(const ContentManager& contentManager)
{
	Bullet::initializeContent(contentManager);
	Bullet::setSoundBuffer(contentManager.getEnemyGunSound());
	setTexture(contentManager.getGuardianAlyssaBmp());
	setTextureRect(sf::IntRect(287, 106, 15, 5));
	setScale(2.0f, 2.0f);
	setRotation(270.0f);
}

void EnemyBullet::update(float elapsedTime)
{
	if (!isActive())
		return;

	move(sf::Vector2f(0, Bullet::BULLET_SPEED * elapsedTime));
	Bullet::update(elapsedTime);
}