#include "stdafx.h"
#include "game.h"
#include "scenetype.h" 
#include "TitleScene.h"
#include "SceneFactory.h"
#include "Publisher.h"

const unsigned int Game::DEFAULT_GAME_TIME = 30;


Game::Game(std::string windowName)
	: BaseGame(windowName)
{
}

Game::~Game()
{
	uninit();
}

void Game::handleEvents()
{
	if (!scenes.empty())
		scenes.top()->handleEvents(window);
}


void Game::update()
{
	bool gameMustEnd = scenes.empty();
	if (!gameMustEnd)
	{
		scenes.top()->update(TIME_PER_FRAME);
		SceneInfo nextSceneInfo = scenes.top()->getSceneInfo();

		if (nextSceneInfo.currentSceneType == SceneType::TITLE_SCENE)
		{
			if (music.Playing != music.getStatus())
			{
				music.play();
			}
		}
		else if (nextSceneInfo.currentSceneType == SceneType::END_SCENE)
		{
			if (music.Playing == music.getStatus() || music.Paused == music.getStatus())
			{
				music.stop();
			}
		}

		// Si la nouvelle scène attendue est différente de l'ancienne...
		if (nextSceneInfo.nextSceneType != nextSceneInfo.currentSceneType)
		{
			Scene* nextScene = nullptr;
			// ... soit on veut retirer la scène courant de la pile
			if (SceneType::NONE == nextSceneInfo.nextSceneType)
			{
				popScene(true);
			}
			else
			{
				if (nextSceneInfo.discardActiveScene)
					popScene(false);
				// ... soit on veut en ajouter une nouvelle

				nextScene = getNextScene(nextSceneInfo.nextSceneType);
			}
			if (nextScene != nullptr)
				pushScene(nextScene, &nextSceneInfo);
		}
	}
}

void Game::draw()  const
{
	if (!scenes.empty())
	{
		scenes.top()->draw(window);
	}
}

void Game::notify(Event event, const void* /*data*/)
{
	if (event == Event::PlayOrPause)
	{
		if (music.Playing != music.getStatus())
		{
			music.play();
		}
		else
		{
			music.pause();
		}
	}
}

void Game::init()
{
	BaseGame::init();

	pushScene(new TitleScene(), nullptr);

	music.openFromFile("Assets\\Music\\Title\\SkyFire (Title Screen).ogg");
	music.setLoop(true);

	Publisher::addSubscriber(*this, Event::PlayOrPause);
}

void Game::uninit()
{
	while (!scenes.empty())
	{
		popScene(false);
	}

	Publisher::removeSubscriber(*this, Event::PlayOrPause);
}

Scene* Game::getNextScene(SceneType type) const
{
	return SceneFactory::createScene(type);
}