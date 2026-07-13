#include "stdafx.h"
#include "CyclicAnimation.h"


CyclicAnimation::CyclicAnimation(sf::Sprite& s, float length)
	: Animation(s, length)
	, timeOrientation(1.0f)
{

}

void CyclicAnimation::update(float deltaT)
{
	timeInCurrentState = std::min(lengthInSeconds * 0.5f, timeInCurrentState + deltaT * timeOrientation);
	if (timeInCurrentState == lengthInSeconds * 0.5f)
	{
		timeInCurrentState -= 0.00001f;
		timeOrientation = -1.0;
	}
	else if (timeInCurrentState < 0.0f)
	{
		timeInCurrentState = 0.0f;
		timeOrientation = 1.0f;
	}
	Animation::update(deltaT);
}

unsigned int CyclicAnimation::getNextFrame() const
{
	float retval = (float)frames.size() * timeInCurrentState / (lengthInSeconds * 0.5f);
	return (unsigned int)(retval);
}

float CyclicAnimation::getPercentage() const
{
	if (timeOrientation > 0)
		return (float)getNextFrame() / (2.0f * (float)frames.size());
	else
		return ((float)getNextFrame() + (float)frames.size()) / (2.0f * (float)frames.size());
}
