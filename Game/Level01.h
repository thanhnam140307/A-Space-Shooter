#pragma once
#include "Scene.h"
#include "Inputs.h"
#include "Player.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"
#include "HealthBonus.h"
#include "SmartGunBonus.h"
#include "Bonus.h"
#include "ContentManager.h"
#include "StandardEnemy.h"
#include "BossEnemy.h"
#include "Hud.h"
#include <list>
#include "random.h"
#include "SmartGun.h"
#include "Subscriber.h"

class Level01 : public Scene, public Subscriber
{
public:
	static const float TIME_PER_FRAME;
	static const float GAMEPAD_SPEEDRATIO;
	static const float SPEED;
	static const int LIMIT;
	static const int INITIAL_AMOUNT;
	static const int MAX_NB_OF_ENEMIES_TO_GENERATE;

public:
	// Héritées via Scene
	Level01();
	~Level01();
	virtual void update(float _deltaT) override;
	void notify(Event event, const void* data) override;
	virtual void draw(sf::RenderWindow& window) const override;
	virtual void init(SceneInfo* _previousSceneInfo = nullptr) override;
	virtual void uninit() override;
	void handleEvent() override;
private:
	Inputs inputs;
	Player player;
	sf::Sprite backgroundSprite;

	std::list<PlayerBullet> playerBullets;
	float playerTimePerShot;

	std::list<EnemyBullet> enemyBullets;

	BossEnemy bossEnemy;

	std::list<StandardEnemy> standardsEnemies;
	float timePerEnemy;
	int nbOfEnemiesToGenerate;

	std::list<SmartGunBonus> smartGunBonuses;
	std::list<HealthBonus> healthBonuses;

	std::list<SmartGun> smartGuns;

	Hud hud;

	Random random;

	SmartGun& getAvailableSmartGun();
	SmartGunBonus& getAvailableSmartGunBonus();
	HealthBonus& getAvailableHealthBonus();
	StandardEnemy& getAvailableEnemy();
	PlayerBullet& getAvailablePlayerBullet();
	EnemyBullet& getAvailableEnemyBullet();

	bool isInPause;

	void gameOver();
	void removeSmartGun();
	void spawnBoss();
	void handleBullets(float _deltaT);
	void handleBonuses(float _deltaT);
	void handleEnemies(float playerPositionX);
	void handleBoss(float playerPositionX);
};