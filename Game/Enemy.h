#pragma once
#include "IUpdatable.h"

class Enemy : public IUpdatable
{
public:
	Enemy();
	float followPlayer(float horizontalSpeed, float playerPositionX, float currentPositionX);
	virtual void displace(float playerPositionX) = 0;
	void update(float elaspedTime = 0) override = 0;
	virtual void onHitBullet() = 0;
	virtual bool shoot() = 0;
};