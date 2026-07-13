#pragma once
#include "Bullet.h"
#include "ContentManager.h"

class EnemyBullet : public Bullet
{
public:
	virtual void initializeContent(const ContentManager& contentManager) override;
	void update(float elapsedTime) override;
};
