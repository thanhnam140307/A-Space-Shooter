#include "stdafx.h"
#include "TitleScene.h"
#include "Scene.h"
#include "BaseGame.h"

TitleScene::TitleScene() : Scene(SceneType::TITLE_SCENE)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::init(SceneInfo * /*_previousSceneInfo*/)
{
	Scene::init();

	titleScreenImage.setTexture(contentManager.getTitleScreenTexture());
	const sf::IntRect &titleScreenRect = titleScreenImage.getTextureRect();
	titleScreenImage.setOrigin(sf::Vector2f(titleScreenRect.width / BaseGame::HALF, titleScreenRect.height / BaseGame::HALF));
	titleScreenImage.setPosition(BaseGame::GAME_WIDTH / BaseGame::HALF, 300);

	titleText.setFont(contentManager.getFont());
	titleText.setCharacterSize(Scene::TEXT_SIZE);
	titleText.setOutlineColor(sf::Color::White);
	titleText.setString("Click to play");
	sf::FloatRect shortGameTextRect = titleText.getLocalBounds();
	titleText.setOrigin(shortGameTextRect.width / BaseGame::HALF, shortGameTextRect.height / BaseGame::HALF);
	titleText.setPosition(BaseGame::GAME_WIDTH / BaseGame::HALF, 550);
}

void TitleScene::uninit()
{
}

void TitleScene::draw(sf::RenderWindow &window) const
{
	window.draw(titleScreenImage);
	window.draw(titleText);
}

void TitleScene::handleEvent()
{
	if (event.type == sf::Event::KeyPressed || event.type == sf::Event::JoystickButtonPressed)
	{
		sceneInfo.nextSceneType = SceneType::LEVEL01;
	}
}

void TitleScene::pause()
{
}

void TitleScene::unPause()
{
	Scene::unPause();
}
