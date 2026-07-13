#include "stdafx.h"
#include "StandardEnemyAnimation.h"

const float StandardEnemyAnimation::ANIMATION_LENGTH = 0.5f;

StandardEnemyAnimation::StandardEnemyAnimation(sf::Sprite& s)
	: CyclicAnimation(s, ANIMATION_LENGTH)
{
}

bool StandardEnemyAnimation::init(const ContentManager& contentManager)
{
	const sf::Texture& texture = contentManager.getEnemiesTexture();
	sf::IntRect rect(28, 917, 65, 96);
	frames.push_back(AnimationFrame(texture, rect));
	rect.left += 73;
	frames.push_back(AnimationFrame(texture, rect));
	rect.left += 73;
	frames.push_back(AnimationFrame(texture, rect));
	rect.left += 73;
	frames.push_back(AnimationFrame(texture, rect));
	rect.left += 73;
	frames.push_back(AnimationFrame(texture, rect));
	rect.left += 73;
	frames.push_back(AnimationFrame(texture, rect));
	rect.left += 73;
	frames.push_back(AnimationFrame(texture, rect));
	rect.left += 73;
	frames.push_back(AnimationFrame(texture, rect));
	rect.left += 73;
	frames.push_back(AnimationFrame(texture, rect));
	return true;
}
