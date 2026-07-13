#pragma once
#include "scenetype.h"
#include "SceneResult.h"
struct SceneInfo
{
	SceneType currentSceneType;
	SceneType nextSceneType;
	bool discardActiveScene;
	SceneResult result;

	SceneInfo(SceneType current = SceneType::NONE, SceneType next = SceneType::NONE, bool discard = false)
		: currentSceneType(current)
		, nextSceneType(next)
		, discardActiveScene(discard)
	{
		result.level01Result.score = 0;
	}
};