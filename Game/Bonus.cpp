#include "stdafx.h"
#include "Bonus.h"
#include "game.h"
#include "Publisher.h"

const float Bonus::SCALE = 3.0f;
const int Bonus::CHANCE_TO_SPAWN = 3;

Bonus::Bonus(const sf::Vector2f& initialPosition, const sf::Vector2f& initialThrust) : GameObject()
{
	setPosition(initialPosition);
	move(initialThrust);
}

Bonus::Bonus(const Bonus& src) : GameObject(src)
{
	setPosition(src.getPosition());

	if (src.bonusSound.getBuffer())
		setSoundBuffer(*src.bonusSound.getBuffer());
}

Bonus::~Bonus()
{
}

void Bonus::initializeContent(const ContentManager& contentManager)
{
	GameObject::initializeContent(contentManager);
}

void Bonus::setSoundBuffer(const sf::SoundBuffer& soundbuffer)
{
	bonusSound.setBuffer(soundbuffer);
}

void Bonus::update(float /*elapsedTime*/)
{
	if (!isActive())
		return;

	move(sf::Vector2f(0, StandardEnemy::VERTICAL_SPEED));

	if (getPosition().y < 0 || getPosition().y > Game::GAME_HEIGHT)
	{
		activate(false);
	}
}

void Bonus::spawn(const sf::Vector2f& spritePosition)
{
	if (random.next(1, 10) <= CHANCE_TO_SPAWN)
	{
		setPosition(spritePosition);
		activate(true);
	}
}

void Bonus::handleCollision(Event event)
{
	bonusSound.play();
	Publisher::notifySubscribers(event, this);
	activate(false);
}
