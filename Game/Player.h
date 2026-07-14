#pragma once
#include "GameObject.h"
#include "IUpdatable.h"
#include "Inputs.h"
#include "ShipAnimation.h"
#include "Subscriber.h"

class Player : public GameObject, public IUpdatable, public Subscriber
{
public:
	Player();
	~Player();
	virtual void initializeContent(const ContentManager& contentManager) override;
	void activate(bool _active) override;
	void update(float elaspedTime = 0) override;
	void updateInputs(float deltaT, const Inputs& inputs);
	void died(int damage);
	bool getCanBeKilled() const;
	bool hasHealthPoints() const;
	int getHealthPoints() const;
	void setHealthPoints(int health);
	int getScore() const;
	int getNbOfSmartGun() const;
	void notify(Event event, const void* data) override;

private:
	void setGolden();
	void addScore(int amount);

	ShipAnimation* shipAnimation;
	int healthPoints;
	int score;
	bool isAlive;
	bool isInvincible;
	int nbOfSmartGun;
	float timeWhileDead;
	float timeWhileGolden;
};

