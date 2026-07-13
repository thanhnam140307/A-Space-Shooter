#pragma once
#include "Scene.h"
class SceneFactory
{
public:
	static Scene* createScene(SceneType type);
};

