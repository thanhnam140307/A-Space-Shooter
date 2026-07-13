#include "stdafx.h"
#include "SmartGunBonus.h"

SmartGunBonus::~SmartGunBonus()
{
}

void SmartGunBonus::initializeContent(const ContentManager& contentManager)
{
	Bonus::initializeContent(contentManager);
	Bonus::setSoundBuffer(contentManager.getGunBonusSound());
	setTexture(contentManager.getGuardianLegendMiscellaneousBmp());
	setTextureRect(sf::IntRect(247, 103, 18, 18));
	setScale(Bonus::SCALE, Bonus::SCALE);
}

void SmartGunBonus::collidesWithPlayer()
{
	Bonus::collision(Event::GetSmartGunBonus);
}