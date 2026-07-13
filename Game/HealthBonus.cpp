#include "stdafx.h"
#include "HealthBonus.h"

HealthBonus::~HealthBonus()
{
}

void HealthBonus::initializeContent(const ContentManager& contentManager)
{
	Bonus::initializeContent(contentManager);
	Bonus::setSoundBuffer(contentManager.getHealthBonusSound());
	setTexture(contentManager.getGuardianLegendMiscellaneousBmp());
	setTextureRect(sf::IntRect(226, 61, 17, 15));
	setScale(Bonus::SCALE, Bonus::SCALE);
}

void HealthBonus::collidesWithPlayer()
{
	Bonus::collision(Event::GetHealthBonus);
}