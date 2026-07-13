#pragma once
#include "GameObject.h"
#include "BossEnemyAnimation.h"
#include "Enemy.h"

class BossEnemy : public Enemy, public GameObject
{
public:
	static const float HORIZONTAL_SPEED;

public:
	BossEnemy();
	~BossEnemy();
	virtual void initializeContent(const ContentManager& contentManager) override;
	void draw(sf::RenderWindow& window) const override;
	void displace(float playerPositionX) override;
	void update(float elaspedTime = 0) override;
	void onHitBullet() override;
	bool shoot() override;

private:
	BossEnemyAnimation* bossEnemyAnimation;
	int health;
	sf::Text healthText;
};