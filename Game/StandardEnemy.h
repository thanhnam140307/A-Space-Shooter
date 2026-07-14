#pragma once
#include "GameObject.h"
#include "ISoundPlayer.h"
#include "StandardEnemyAnimation.h"
#include "random.h"
#include "Enemy.h"

class StandardEnemy : public Enemy, public GameObject, public ISoundPlayer
{
public:
	static const float VERTICAL_SPEED;
	static const int STANDARD_ENEMY_DAMAGE;

public:
	StandardEnemy();
	StandardEnemy(const StandardEnemy& src);
	~StandardEnemy();
	void initializeContent(const ContentManager& contentManager) override;
	void spawn();
	void displace(float playerPositionX) override;
	void update(float elaspedTime = 0) override;
	void onHitBullet() override;
	bool canShoot() override;
	void died();
	bool getIsKamikaze() const;

private:
	void setSoundBuffer(const sf::SoundBuffer& soundbuffer) override;

	StandardEnemyAnimation* standardEnemyAnimation;
	sf::Sound enemyKilledSound;
	ContentManager* contentManager;
	Random random;
	int health;
	bool hadShot;
	bool isKamikaze;
	float horizontalSpeed;
};