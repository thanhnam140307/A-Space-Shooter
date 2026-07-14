#include "stdafx.h"
#include "Player.h"
#include "Inputs.h"
#include "game.h"
#include "Publisher.h"

Player::Player() :
	GameObject(),
	shipAnimation(new ShipAnimation(*this)),
	healthPoints(1000),
	score(0),
	isAlive(true),
	isInvincible(false),
	nbOfSmartGun(0),
	timeWhileDead(0.0f),
	timeWhileGolden(0.0f)
{
}

Player::~Player()
{
	delete shipAnimation;
}

void Player::initializeContent(const ContentManager& contentManager)
{
	setPosition(float(Game::GAME_WIDTH / 2), float(Game::GAME_HEIGHT / 2 + 100));
	GameObject::initializeContent(contentManager);

	bool retval = shipAnimation->init(contentManager);

	if (retval)
		activate(true);

	setScale(3.0f, 3.0f);
}

void Player::activate(bool _active)
{
	GameObject::activate(_active);

	if (_active)
	{
		Publisher::addSubscriber(*this, Event::EnemyDied);
		Publisher::addSubscriber(*this, Event::GetSmartGunBonus);
		Publisher::addSubscriber(*this, Event::GetHealthBonus);
		Publisher::addSubscriber(*this, Event::BossShot);
	}
	else
	{
		Publisher::removeSubscriber(*this, Event::EnemyDied);
		Publisher::removeSubscriber(*this, Event::GetSmartGunBonus);
		Publisher::removeSubscriber(*this, Event::GetHealthBonus);
		Publisher::removeSubscriber(*this, Event::BossShot);
	}
}

void Player::update(float deltaT)
{
	if (timeWhileDead > 0.0f)
	{
		timeWhileDead -= deltaT;
	}

	else if (timeWhileDead <= 0.0f && !isAlive)
	{
		setColor(sf::Color::White);
		isAlive = true;
	}

	if (timeWhileGolden > 0.0f)
	{
		timeWhileGolden -= deltaT;
	}

	else if (timeWhileGolden <= 0.0f && isAlive && getColor() != sf::Color::White)
	{
		setColor(sf::Color::White);
	}
}

void Player::updateInputs(float deltaT, const Inputs& inputs)
{
	float moveX = inputs.moveX;
	float moveY = inputs.moveY;

	if ((getPosition().x <= Level01::LIMIT && moveX < Level01::SPEED) || (getPosition().x >= Game::GAME_WIDTH - Level01::LIMIT && moveX >= Level01::SPEED))
		moveX = 0.0f;

	if ((getPosition().y <= Level01::LIMIT && moveY < Level01::SPEED) || (getPosition().y >= Game::GAME_HEIGHT - (Level01::LIMIT * 2) - 20.0f && moveY >= Level01::SPEED))
		moveY = 0.0f;

	move(sf::Vector2f(moveX, moveY));
	shipAnimation->update(deltaT, inputs);

	isInvincible = inputs.isInvincible;
}

void Player::died(int damage)
{
	if (!isAlive || isInvincible)
		return;

	if (nbOfSmartGun > 0)
		nbOfSmartGun--;

	else if (nbOfSmartGun == 0)
	{
		timeWhileDead = 2.0f;
		timeWhileGolden = 0.0f;
		isAlive = false;
		setColor(sf::Color(255, 255, 255, 128));

		healthPoints -= damage;
	}
}

bool Player::getCanBeKilled() const
{
	return (isAlive && !isInvincible);
}

bool Player::hasHealthPoints() const
{
	return healthPoints > 0;
}

int Player::getHealthPoints() const
{
	return healthPoints;
}

void Player::setHealthPoints(int health)
{
	healthPoints = health;
}

int Player::getScore() const
{
	return score;
}

int Player::getNbOfSmartGun() const
{
	return nbOfSmartGun;
}

void Player::notify(Event event, const void* data)
{
	if (event == Event::EnemyDied)
	{
		addScore(10);

		const StandardEnemy* standardEnemy = (const StandardEnemy*)data;

		if (standardEnemy->getIsKamikaze())
			addScore(10);

		if (collidesWith(*standardEnemy))
			died(StandardEnemy::STANDARD_ENEMY_DAMAGE);
	}

	if (event == Event::BossShot)
	{
		addScore(20);
	}

	if (event == Event::GetHealthBonus)
	{
		if (healthPoints < 1000)
			healthPoints += 10;

		addScore(5);
		setGolden();
	}

	if (event == Event::GetSmartGunBonus)
	{
		nbOfSmartGun += 1;
		addScore(5);
		setGolden();
	}
}

void Player::setGolden()
{
	if (isAlive) 
	{
		timeWhileGolden = 2.0f;

		if (getColor() != sf::Color(255, 215, 0))
		{
			setColor(sf::Color(255, 215, 0));
		}
	}
}

void Player::addScore(int amount)
{
	score += amount;
}
