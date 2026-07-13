#pragma once
#include "Scene.h"

class EndScene : public Scene
{
public:
	EndScene();
	~EndScene();

	void init(SceneInfo* _previousSceneInfo = nullptr) override;
	void uninit() override;

	void draw(sf::RenderWindow& window) const override;
	void handleEvents(sf::RenderWindow& window) override;
	void handleEvent() override;
	void pause() override;
	void unPause() override;

private:
	sf::Sprite endScreenImage;
	sf::Text resultText;
	sf::Text returnText;
};