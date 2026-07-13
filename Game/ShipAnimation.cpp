#include "stdafx.h"
#include "ShipAnimation.h"
#include "ContentManager.h"
#include "Inputs.h"

ShipAnimation::ShipAnimation(sf::Sprite& s) : roll(0), InputBasedAnimation(s)
{
}

bool ShipAnimation::init(const ContentManager& contentManager)
{
	const sf::Texture& texture = contentManager.getGuardianAlyssaBmp();

	frames.push_back(AnimationFrame(texture, sf::IntRect(224, 46, 14, 30))); 
	frames.push_back(AnimationFrame(texture, sf::IntRect(300, 46, 18, 30)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(270, 46, 23, 30)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(246, 46, 18, 30))); 
	frames.push_back(AnimationFrame(texture, sf::IntRect(227, 46, 14, 30)));

	nextFrame = 2;

	return true;
}

void ShipAnimation::adjustNextFrame(const Inputs& inputs)
{
	if (inputs.moveX < 0)
	{
		roll += 1;

		if (roll > 49)
			roll = 49;
	}

	else if (inputs.moveX > 0)
	{
		roll -= 1;

		if (roll < 0)
			roll = 0;
	}

	else
	{
		if (roll > 24)
			roll -= 1;

		else if (roll < 24)
			roll += 1;
	}

	if (roll > 40)
		nextFrame = 4;

	else if (roll >= 30 && roll <= 40)
		nextFrame = 3;

	else if (roll >= 20 && roll <= 30)
		nextFrame = 2;

	else if (roll >= 10 && roll <= 20)
		nextFrame = 1;

	else if (roll >= 0 && roll <= 10)
		nextFrame = 0;
}
