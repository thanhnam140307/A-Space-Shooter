#include "stdafx.h"
#include "EndScene.h"
#include "BaseGame.h"

EndScene::EndScene() : Scene(SceneType::END_SCENE)
{
}

EndScene::~EndScene()
{
}

void EndScene::init(SceneInfo *_previousSceneInfo)
{
	Scene::init();

	if (_previousSceneInfo->result.level01Result.healthPoints > 0)
	{
		endScreenImage.setTexture(contentManager.getVictoryEndScreenTexture());
		resultText.setPosition(420.0f, 418.0f);
		returnText.setPosition(430.0f, 500.0f);
	}
	else
	{
		endScreenImage.setTexture(contentManager.getDefeatedEndScreenTexture());
		resultText.setPosition(BaseGame::GAME_WIDTH / BaseGame::HALF, 920.0f);
		returnText.setPosition(BaseGame::GAME_WIDTH / BaseGame::HALF, 960.0f);
	}

	const sf::IntRect &rect = endScreenImage.getTextureRect();
	endScreenImage.setOrigin(sf::Vector2f(rect.width / BaseGame::HALF, rect.height / BaseGame::HALF));
	endScreenImage.setPosition(BaseGame::GAME_WIDTH / BaseGame::HALF, BaseGame::GAME_HEIGHT / BaseGame::HALF);

	resultText.setFont(contentManager.getFont());
	resultText.setCharacterSize(Scene::TEXT_SIZE);
	resultText.setOutlineColor(sf::Color::White);
	resultText.setString(std::to_string(_previousSceneInfo->result.level01Result.score));
	sf::FloatRect resultTextRect = resultText.getLocalBounds();
	resultText.setOrigin(resultTextRect.width / BaseGame::HALF, resultTextRect.height / BaseGame::HALF);

	returnText.setFont(contentManager.getFont());
	returnText.setCharacterSize(Scene::TEXT_SIZE - 25);
	returnText.setOutlineColor(sf::Color::White);
	returnText.setString("Click to return");
	sf::FloatRect returnTextRect = returnText.getLocalBounds();
	returnText.setOrigin(returnTextRect.width / BaseGame::HALF, returnTextRect.height / BaseGame::HALF);
}

void EndScene::uninit()
{
}

void EndScene::draw(sf::RenderWindow &window) const
{
	window.draw(endScreenImage);
	window.draw(resultText);
	window.draw(returnText);
}

void EndScene::handleEvent()
{
	if (event.type == sf::Event::KeyReleased || event.type == sf::Event::JoystickButtonReleased)
	{
		sceneInfo.discardActiveScene = true;
		sceneInfo.result.level01Result.score = 0;
		sceneInfo.result.level01Result.healthPoints = 0;
		sceneInfo.nextSceneType = SceneType::TITLE_SCENE;
	}
}

void EndScene::pause()
{
}

void EndScene::unPause()
{
}
