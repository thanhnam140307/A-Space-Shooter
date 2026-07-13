#pragma once
#include "InputBasedAnimation.h"

class ShipAnimation : public InputBasedAnimation
{
public:
	ShipAnimation(sf::Sprite& s);
	virtual bool init(const ContentManager& contentManager) override;
	virtual void adjustNextFrame(const Inputs& inputs) override;
private:
	int roll;
};