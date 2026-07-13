#pragma once
#include "Animation.h"
class InputBasedAnimation :
	public Animation
{
public:
	void update(float deltaT, const Inputs& inputs);
	virtual unsigned int getNextFrame() const override;
	virtual float getPercentage() const override;
protected:
	InputBasedAnimation(sf::Sprite& s);
	virtual void adjustNextFrame(const Inputs& inputs) = 0;
	unsigned int nextFrame;
};

