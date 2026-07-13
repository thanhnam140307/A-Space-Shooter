#pragma once

struct Inputs
{
	static const float CONTROLLER_DEAD_ZONE;

	bool shouldFire;
	float moveX;
	float moveY;
	bool isInvincible;

	Inputs();
	void reset();
	//Portée analogue -100 à 100
	static float eliminateVibration(float analogInput);
};

