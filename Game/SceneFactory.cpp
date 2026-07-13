#include "stdafx.h"
#include "SceneFactory.h"
#include "Level01.h"
#include "TitleScene.h"
#include "EndScene.h"


Scene* SceneFactory::createScene(SceneType type)
{
	Scene* scene = nullptr;
	switch (type)
	{
	case SceneType::LEVEL01:
	{
		scene = new Level01();
		break;
	}
	case SceneType::TITLE_SCENE:
	{
		scene = new TitleScene();
		break;
	}
	case SceneType::END_SCENE:
	{
		scene = new EndScene();
		break;
	}
	default:
	{
		scene = nullptr;
		break;
	}
	}
	return scene;
}