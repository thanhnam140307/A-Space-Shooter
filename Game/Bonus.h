#pragma once
#include "GameObject.h"
#include "IUpdatable.h"
#include "ISoundPlayer.h"
#include "random.h"
#include "event.h"

class Bonus : public GameObject, public IUpdatable, public ISoundPlayer
{
public:
	static const float SCALE;
	static const int CHANCE_TO_SPAWN;

public:
	Bonus(const sf::Vector2f& initialPosition = sf::Vector2f(0, 0), const sf::Vector2f& initialThrust = sf::Vector2f(0, 0));
	Bonus(const Bonus& src);
	virtual ~Bonus();
	virtual void initializeContent(const ContentManager& contentManager) override;
	void setSoundBuffer(const sf::SoundBuffer& soundbuffer) override;
	virtual void update(float elapsedTime) override;
	void spawn(const sf::Vector2f& spritePosition);
	virtual void collidesWithPlayer() = 0;
	void collision(Event event);

private:
	sf::Sound bonusSound;
	Random random;
};