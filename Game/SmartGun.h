#pragma once
#include "GameObject.h"
#include "ContentManager.h"

class SmartGun : public GameObject
{
public:
	static const float GAP;
	static const float SPEED;

public:
	SmartGun();
	SmartGun(const SmartGun& src);
	virtual void initializeContent(const ContentManager& contentManager) override;
	void follow(const sf::Vector2f& position);
	void spawn(const sf::Vector2f& position);
};