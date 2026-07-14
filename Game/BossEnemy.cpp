#include "stdafx.h"
#include "BossEnemy.h"
#include "game.h"
#include "Publisher.h"

const float BossEnemy::HORIZONTAL_SPEED = Level01::SPEED - 2;
const int BossEnemy::HEALTH_LOSS = 1;
const int BossEnemy::SHOOT_FRAME = 2;

BossEnemy::BossEnemy() :
	Enemy(),
	GameObject(),
	bossEnemyAnimation(new BossEnemyAnimation(*this)),
	health(100)
{
}

BossEnemy::~BossEnemy()
{
	delete bossEnemyAnimation;
}

void BossEnemy::initializeContent(const ContentManager& contentManager)
{
	setPosition(float(Game::GAME_WIDTH / 2), -150.0f);
	GameObject::initializeContent(contentManager);

	bool retval = bossEnemyAnimation->init(contentManager);

	if (retval)
		activate(true);

	healthText.setFont(contentManager.getFont());
	healthText.setCharacterSize(20);
	healthText.setOutlineColor(sf::Color::White);
}

void BossEnemy::draw(sf::RenderWindow& window) const
{
	GameObject::draw(window);
	window.draw(healthText);
}

void BossEnemy::displace(float playerPositionX)
{
	if (!isActive())
		return;

	float moveX = Enemy::followPlayer(HORIZONTAL_SPEED, playerPositionX, getPosition().x);
	float moveY = 0.0f;

	if (getPosition().y < 100.0f)
		moveY = 1.0f;

	move(moveX, moveY);
}

void BossEnemy::update(float /*elaspedTime*/)
{
	if (!isActive())
		return;

	bossEnemyAnimation->update(0.5f / (float)Game::FRAME_RATE);

	healthText.setString(std::to_string(health));
	healthText.setPosition(sf::Vector2f(getPosition().x - 30.0f, getPosition().y - 100.0f));
}

void BossEnemy::onHitBullet()
{
	if (getPosition().y < 100.0f)
		return;

	health -= HEALTH_LOSS;
	Publisher::notifySubscribers(Event::BossShot, this);

	if (health <= 0)
	{
		Publisher::notifySubscribers(Event::BossDied, this);
	}
}

bool BossEnemy::canShoot()
{
	if (bossEnemyAnimation->getNextFrame() <= SHOOT_FRAME && isActive())
		return true;

	return false;
}