#pragma once


struct Level01Result
{
	int score;
	int healthPoints;
};

union SceneResult
{
	Level01Result level01Result;
};