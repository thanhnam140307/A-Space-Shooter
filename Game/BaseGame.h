#pragma once
#include <stack>
#include "ContentManager.h"
#include "Inputs.h"
#include "Scene.h"
class BaseGame
{
public:
	static const unsigned int FRAME_RATE;
	static const float TIME_PER_FRAME;
	static const unsigned int GAME_WIDTH;
	static const unsigned int GAME_HEIGHT;
	static const float HALF;

public:
	BaseGame(std::string windowName);
	virtual ~BaseGame() = default;
	void run();
	virtual void update()=0;
	virtual void draw() const = 0;


protected:
	ContentManager contentManager;
	Inputs inputs;

	std::string gameName;
	mutable sf::RenderWindow window;

	virtual void init();
	virtual void uninit();
	virtual void handleEvents() =0;

	// Gestion des scènes
	virtual Scene* getNextScene(SceneType type) const=0;
	void popScene(bool initScene = true);
	void pushScene(Scene* newScene, SceneInfo* nextSceneInfo);
	std::stack<Scene*> scenes;

};

