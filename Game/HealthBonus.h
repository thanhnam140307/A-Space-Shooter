#pragma once
#include "Bonus.h"
#include "ContentManager.h"

class HealthBonus : public Bonus
{
public:
	~HealthBonus();
	virtual void initializeContent(const ContentManager& contentManager) override;
	void handleCollisionWithPlayer();
};