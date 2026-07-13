#pragma once
#include "GameObject.h"
#include "IUpdatable.h"
#include "ISoundPlayer.h"

class Bullet : public GameObject, public IUpdatable, public ISoundPlayer
{
public:
	static const float BULLET_SPEED;
	static const unsigned long long TIME_TO_LIVE;
public:
	Bullet(const sf::Vector2f& initialPosition = sf::Vector2f(0,0), const sf::Vector2f& initialThrust = sf::Vector2f(0, 0));
	Bullet(const Bullet& src);
	virtual void initializeContent(const ContentManager& manager) override;
	void setSoundBuffer(const sf::SoundBuffer& soundbuffer) override;
	virtual void update(float elapsedTime) override;
	void fire(const sf::Vector2f& spritePosition);

private:
	sf::Sound bulletSound;
};
