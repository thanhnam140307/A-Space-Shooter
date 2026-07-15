#include "stdafx.h"
#include "StandardEnemy.h"
#include "game.h"
#include <iostream>
#include "Publisher.h"

const float StandardEnemy::VERTICAL_SPEED = 4.0f;
const int StandardEnemy::STANDARD_ENEMY_DAMAGE = 50;

StandardEnemy::StandardEnemy() :
	Enemy(),
	GameObject(),
	contentManager(nullptr),
	standardEnemyAnimation(new StandardEnemyAnimation(*this)),
	health(5),
	hadShot(false),
	isKamikaze(false),
	horizontalSpeed(0.0f)
{
}

StandardEnemy::StandardEnemy(const StandardEnemy& src) :
	GameObject(src),
	standardEnemyAnimation(new StandardEnemyAnimation(*this)),
	contentManager(src.contentManager),
	health(src.health),
	hadShot(src.hadShot),
	isKamikaze(src.isKamikaze),
	horizontalSpeed(src.horizontalSpeed)
{
	initializeContent(*contentManager);
	setSoundBuffer(*src.enemyKilledSound.getBuffer());
	setPosition(src.getPosition());
	activate(src.isActive());
}

StandardEnemy::~StandardEnemy()
{
	delete standardEnemyAnimation;
}

void StandardEnemy::initializeContent(const ContentManager& _contentManager)
{
	this->contentManager = (ContentManager*)(&_contentManager);
	GameObject::initializeContent(_contentManager);
	spawn();
	setSoundBuffer(_contentManager.getEnemyKilledSound());

	bool retval = standardEnemyAnimation->init(_contentManager);

	if (retval)
		activate(true);

	if (random.next(1, 30) <= 10)
	{
		isKamikaze = true;
		horizontalSpeed = (float)random.next(1, 4);
	}
}

void StandardEnemy::spawn()
{
	setPosition(sf::Vector2f(float(random.next(Level01::LIMIT, Game::GAME_WIDTH - (Level01::LIMIT * 2))), -30.0f * (float)(rand() % 100)));
	activate(true);
}

void StandardEnemy::displace(float playerPositionX)
{
	if (!isActive())
		return;

	float moveX = 0.0f;

	if (isKamikaze)
		moveX = Enemy::followPlayer(horizontalSpeed, playerPositionX, getPosition().x);

	move(sf::Vector2f(moveX, VERTICAL_SPEED));

	if (getGlobalBounds().top > Game::GAME_HEIGHT + getGlobalBounds().height * 0.5f)
		setPosition(float(random.next(Level01::LIMIT, Game::GAME_WIDTH - (Level01::LIMIT * 2))), 0.0f);
}

void StandardEnemy::update(float /*elaspedTime*/)
{
	if (isActive())
		standardEnemyAnimation->update(0.5f / (float)Game::FRAME_RATE);
}

void StandardEnemy::setSoundBuffer(const sf::SoundBuffer& soundbuffer)
{
	enemyKilledSound.setBuffer(soundbuffer);
}

void StandardEnemy::onHitBullet()
{
	health -= 1;

	if (health <= 0)
	{
		died();
	}
}

bool StandardEnemy::canShoot() // tirer un bullet seulement
{
	if (standardEnemyAnimation->getNextFrame() == 8 && !hadShot)
	{
		hadShot = true;
		return true;
	}
	else if (standardEnemyAnimation->getNextFrame() != 8)
	{
		hadShot = false;
	}

	return false;
}

void StandardEnemy::died()
{
	enemyKilledSound.play();
	health = 5;
	Publisher::notifySubscribers(Event::EnemyDied, this);
	activate(false);
}

bool StandardEnemy::getIsKamikaze() const
{
	return isKamikaze;
}
