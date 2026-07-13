#pragma once
#include "CyclicAnimation.h"
#include "ContentManager.h"

class BossEnemyAnimation : public CyclicAnimation
{
	static const float ANIMATION_LENGTH;

public:
	BossEnemyAnimation(sf::Sprite& s);
	virtual bool init(const ContentManager& contentManager) override;
};