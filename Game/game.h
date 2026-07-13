#pragma once
#include "BaseGame.h"
#include "Level01.h"

class Game : public BaseGame
{
public:
	static const unsigned int DEFAULT_GAME_TIME;
	typedef class Level01 InitialScene;
public:
	Game(std::string windowName);
	~Game();
	void update() override;
	void draw() const override;

protected:
	Scene* getNextScene(SceneType type) const override;

private:
	void init() override;
	void handleEvents() override;
	void uninit() override;
	sf::Music music;
};

