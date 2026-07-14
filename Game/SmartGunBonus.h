#pragma once
#include "Bonus.h"
#include "ContentManager.h"

class SmartGunBonus : public Bonus
{
public:
	~SmartGunBonus();
	virtual void initializeContent(const ContentManager& contentManager) override;
	void handleCollisionWithPlayer();
};