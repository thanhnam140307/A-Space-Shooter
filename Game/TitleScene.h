#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
public:
	TitleScene();
	~TitleScene();

	void init(SceneInfo* _previousSceneInfo = nullptr) override;
	void uninit() override;

	void draw(sf::RenderWindow& window) const override;
	void handleEvents(sf::RenderWindow& window) override;
	void handleEvent() override;
	void pause() override;
	void unPause() override;
private:
	sf::Text titleText;
	sf::Sprite titleScreenImage;
};