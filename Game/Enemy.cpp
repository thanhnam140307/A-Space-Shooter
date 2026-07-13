#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{
}

float Enemy::followPlayer(float horizontalSpeed, float playerPositionX, float currentPositionX)
{
	float horizontalDistanceBetweenPlayer = currentPositionX - playerPositionX;
	float moveX = 0.0f;

	if (horizontalDistanceBetweenPlayer > 5.0f)
		moveX = -horizontalSpeed; //Va à gauche

	else if (horizontalDistanceBetweenPlayer < -5.0f)
		moveX = horizontalSpeed; //Va à droite

	return moveX;
}
