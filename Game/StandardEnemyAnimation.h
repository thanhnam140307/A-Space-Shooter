#pragma once
#include "CyclicAnimation.h"
#include "ContentManager.h"

class StandardEnemyAnimation : public CyclicAnimation
{
	static const float ANIMATION_LENGTH;

public:
	StandardEnemyAnimation(sf::Sprite& s);
	virtual bool init(const ContentManager& contentManager) override;
};