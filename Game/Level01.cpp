#include "stdafx.h"
#include "Level01.h"
#include "game.h"
#include <iostream>
#include "ContentManager.h"
#include "Publisher.h"

const float Level01::TIME_PER_FRAME = 1.0f / (float)Game::FRAME_RATE;
const float Level01::GAMEPAD_SPEEDRATIO = 1000.0f;
const float Level01::SPEED = 10.0f;
const int Level01::LIMIT = 45;
const int Level01::INITIAL_AMOUNT = 10;
const int Level01::MAX_NB_OF_ENEMIES_TO_GENERATE = 40;

Level01::Level01()
	: Scene(SceneType::LEVEL01),
	playerTimePerShot(0.0f),
	timePerEnemy(0.0f),
	nbOfEnemiesToGenerate(0)
{
}

Level01::~Level01()
{
	for (Bonus* bonus : bonuses)
	{
		delete bonus;
	}
}

void Level01::update(float _deltaT)
{
	//std::cout << "Position: " << player.getPosition().x << ", " << player.getPosition().y << std::endl;
	//std::cout << "playerBullets: " << playerBullets.size() << ", enemyBullets:" << enemyBullets.size() << std::endl;
	//std::cout << "standardsEnemies: " << standardsEnemies.size() << " " << nbOfEnemyToKill << std::endl;
	//std::cout << "bonuses: " << bonuses.size() << std::endl;

	static int cptScrollBackground = 0;
	backgroundSprite.setTextureRect(sf::IntRect(0, (int)(-1.0f * cptScrollBackground++), Game::GAME_WIDTH, Game::GAME_HEIGHT));
	player.update(_deltaT);
	player.updateInputs(_deltaT, inputs);

	if (inputs.shouldFire && playerTimePerShot <= 0.0f)
	{
		getAvailablePlayerBullet().fire(sf::Vector2f(player.getPosition().x + 22, player.getPosition().y));
		getAvailablePlayerBullet().fire(sf::Vector2f(player.getPosition().x - 22, player.getPosition().y));

		for (SmartGun& currentSmartGun : smartGuns)
		{
			if (currentSmartGun.isActive())
				getAvailablePlayerBullet().fire(sf::Vector2f(currentSmartGun.getPosition()));
		}

		playerTimePerShot = 0.1f;
	}

	handleBullets(_deltaT);

	handleBonuses(_deltaT);

	handleEnemies(player.getPosition().x);

	handleBoss(player.getPosition().x);

	playerTimePerShot -= TIME_PER_FRAME;
	timePerEnemy -= TIME_PER_FRAME;

	hud.setHealthText(player.getHealthPoints());
	hud.setScoreText(player.getScore());
	hud.setNbOfSmartGunText(player.getNbOfSmartGun());

	if (!player.hasHealthPoints())
	{
		gameOver();
	}
}

void Level01::notify(Event gameEvent, const void* data)
{
	if (gameEvent == Event::GetSmartGunBonus)
	{
		getAvailableSmartGun();
	}
	else if (gameEvent == Event::EnemyDied)
	{
		const StandardEnemy* deadStandardEnemy = (const StandardEnemy*)data;
		getAvailableBonuses()->spawn(deadStandardEnemy->getPosition());
	}
	else if (gameEvent == Event::BossDied)
	{
		gameOver();
	}
}

void Level01::draw(sf::RenderWindow& window) const
{
	window.draw(backgroundSprite);

	for (const SmartGun& currentSmartGun : smartGuns)
	{
		currentSmartGun.draw(window);
	}

	for (const Bonus* bonus : bonuses)
	{
		bonus->draw(window);
	}

	for (const PlayerBullet& currentPlayerBullet : playerBullets)
	{
		currentPlayerBullet.draw(window);
	}

	for (const EnemyBullet& currentEnemyBullet : enemyBullets)
	{
		currentEnemyBullet.draw(window);
	}

	for (const StandardEnemy& currentStandardEnemy : standardsEnemies)
	{
		currentStandardEnemy.draw(window);
	}

	player.draw(window);
	bossEnemy.draw(window);
	hud.draw(window);
}

void Level01::uninit()
{
	Publisher::removeSubscriber(*this, Event::GetSmartGunBonus);
	Publisher::removeSubscriber(*this, Event::EnemyDied);
	Publisher::removeSubscriber(*this, Event::BossDied);

	player.activate(false);
}

void Level01::init(SceneInfo* /*_previousSceneInfo*/)
{
	Scene::init();

	Publisher::addSubscriber(*this, Event::GetSmartGunBonus);
	Publisher::addSubscriber(*this, Event::EnemyDied);
	Publisher::addSubscriber(*this, Event::BossDied);

	inputs.reset();

	if (contentManager.loadContent() == false)
		return;

	backgroundSprite.setTexture(contentManager.getGameScreenTexture());
	hud.initialize(contentManager);
	srand((unsigned)time(nullptr));

	player.initializeContent(contentManager);

	PlayerBullet playerBullet;
	playerBullet.initializeContent(contentManager);
	EnemyBullet enemyBullet;
	enemyBullet.initializeContent(contentManager);
	StandardEnemy standardEnemy;
	standardEnemy.initializeContent(contentManager);

	for (int i = 0; i < INITIAL_AMOUNT; i++)
	{
		playerBullets.push_back(playerBullet);
		enemyBullets.push_back(enemyBullet);
		standardsEnemies.push_back(standardEnemy);
	}

	HealthBonus healthBonus;
	healthBonus.initializeContent(contentManager);
	SmartGunBonus smartGunBonus;
	smartGunBonus.initializeContent(contentManager);
	SmartGun smartGun;
	smartGun.initializeContent(contentManager);

	for (int i = 0; i < INITIAL_AMOUNT / BaseGame::HALF; i++)
	{
		if (random.next(1, 10) <= Bonus::CHANCE_TO_SPAWN)
		{
			bonuses.push_back(new SmartGunBonus(smartGunBonus));
			smartGuns.push_back(smartGun);
		}

		else
			bonuses.push_back(new HealthBonus(healthBonus));
	}

	gameIsInitialized = true;
}

SmartGun& Level01::getAvailableSmartGun()
{
	//Le premier prend la position du joueur
	sf::Vector2f position = player.getPosition();

	for (SmartGun& currentSmartGun : smartGuns)
	{
		if (!currentSmartGun.isActive())
		{
			currentSmartGun.spawn(position);
			return currentSmartGun;
		}

		//Sinon, le prochain prend la position du smart gun d'avant
		position = currentSmartGun.getPosition();
	}

	SmartGun smartGun;
	smartGun.initializeContent(contentManager);
	smartGun.spawn(position);
	smartGuns.push_back(smartGun);

	return smartGuns.back();
}

Bonus* Level01::getAvailableBonuses()
{
	for (Bonus* bonus : bonuses)
	{
		if (!bonus->isActive())
		{
			return bonus;
		}
	}

	if (random.next(1, 10) <= Bonus::CHANCE_TO_SPAWN)
	{
		SmartGunBonus smartGunBonus;
		smartGunBonus.initializeContent(contentManager);
		bonuses.push_back(new SmartGunBonus(smartGunBonus));
	}
	else
	{
		HealthBonus healthBonus;
		healthBonus.initializeContent(contentManager);
		bonuses.push_back(new HealthBonus(healthBonus));
	}

	return bonuses.back();
}

StandardEnemy& Level01::getAvailableEnemy()
{
	for (StandardEnemy& currentStandardEnemy : standardsEnemies)
	{
		if (!currentStandardEnemy.isActive())
		{
			currentStandardEnemy.spawn();
			return currentStandardEnemy;
		}
	}

	StandardEnemy standardEnemy;
	standardEnemy.initializeContent(contentManager);
	standardEnemy.spawn();
	standardsEnemies.push_back(standardEnemy);

	return standardsEnemies.back();
}

PlayerBullet& Level01::getAvailablePlayerBullet()
{
	for (PlayerBullet& currentPlayerBullet : playerBullets)
	{
		if (!currentPlayerBullet.isActive())
		{
			return currentPlayerBullet;
		}
	}

	PlayerBullet playerBullet;
	playerBullet.initializeContent(contentManager);
	playerBullets.push_back(playerBullet);

	return playerBullets.back();
}

EnemyBullet& Level01::getAvailableEnemyBullet()
{
	for (EnemyBullet& currentEnemyBullet : enemyBullets)
	{
		if (!currentEnemyBullet.isActive())
		{
			return currentEnemyBullet;
		}
	}

	EnemyBullet enemyBullet;
	enemyBullet.initializeContent(contentManager);
	enemyBullets.push_back(EnemyBullet(enemyBullet));

	return enemyBullets.back();
}

void Level01::gameOver()
{
	gameIsOver = true;
	sceneInfo.nextSceneType = SceneType::END_SCENE;
	sceneInfo.discardActiveScene = true;
	sceneInfo.result.level01Result.score = player.getScore();
	sceneInfo.result.level01Result.healthPoints = player.getHealthPoints();
}

void Level01::removeSmartGun()
{
	if (player.getCanBeKilled())
	{
		// https://www.w3tutorials.net/blog/how-do-you-iterate-backwards-through-an-stl-list/#2-1-using-rbegin-and-rend
		for (auto it = smartGuns.rbegin(); it != smartGuns.rend(); ++it)
		{
			SmartGun& currentSmartGun = *it;
			if (currentSmartGun.isActive())
			{
				currentSmartGun.activate(false);
				break;
			}
		}
	}
}

void Level01::handleBullets(float _deltaT)
{
	for (PlayerBullet& currentPlayerBullet : playerBullets)
	{
		currentPlayerBullet.update(_deltaT);
	}

	for (EnemyBullet& currentEnemyBullet : enemyBullets)
	{
		currentEnemyBullet.update(_deltaT);

		if (currentEnemyBullet.collidesWith(player))
		{
			currentEnemyBullet.activate(false);
			removeSmartGun();

			if (bossEnemy.isActive())
				player.died(StandardEnemy::STANDARD_ENEMY_DAMAGE * 2);
			else
				player.died(StandardEnemy::STANDARD_ENEMY_DAMAGE);
		}
	}
}

void Level01::handleBonuses(float _deltaT)
{
	//Le premier prend la position du joueur
	sf::Vector2f position = player.getPosition();

	for (SmartGun& currentSmartGun : smartGuns)
	{
		currentSmartGun.follow(position);

		//Le prochain prend la position du smart gun d'avant
		position = currentSmartGun.getPosition();
	}

	for (Bonus* bonus : bonuses)
	{
		bonus->update(_deltaT);

		if (bonus->collidesWith(player))
		{
			bonus->handleCollisionWithPlayer();
		}
	}
}

void Level01::handleEnemies(float playerPositionX)
{
	if (bossEnemy.isActive())
		return;

	if (timePerEnemy <= 0.0f && nbOfEnemiesToGenerate <= MAX_NB_OF_ENEMIES_TO_GENERATE)
	{
		getAvailableEnemy();
		timePerEnemy = 1.0f;
		nbOfEnemiesToGenerate += 1;
	}

	for (StandardEnemy& currentStandardEnemy : standardsEnemies)
	{
		//std::cout << "Position: " << standardEnemy.getPosition().x << ", " << standardEnemy.getPosition().y << std::endl;

		currentStandardEnemy.displace(playerPositionX);
		currentStandardEnemy.update();

		if (currentStandardEnemy.canShoot())
		{
			getAvailableEnemyBullet().fire(currentStandardEnemy.getPosition());
		}

		if (currentStandardEnemy.collidesWith(player))
		{
			removeSmartGun();
			currentStandardEnemy.died();
		}

		else
		{
			for (PlayerBullet& currentPlayerBullet : playerBullets)
			{
				if (currentPlayerBullet.collidesWith(currentStandardEnemy))
				{
					currentStandardEnemy.onHitBullet();
					currentPlayerBullet.activate(false);
					break;
				}
			}
		}
	}
}

void Level01::handleBoss(float playerPositionX)
{
	if (!bossEnemy.isActive())
	{
		spawnBoss();
	}

	bossEnemy.displace(playerPositionX);
	bossEnemy.update();

	if (bossEnemy.canShoot())
	{
		getAvailableEnemyBullet().fire(bossEnemy.getPosition());
	}

	if (bossEnemy.isActive())
	{
		for (PlayerBullet& currentPlayerBullet : playerBullets)
		{
			if (currentPlayerBullet.collidesWith(bossEnemy))
			{
				bossEnemy.onHitBullet();
				currentPlayerBullet.activate(false);
			}
		}
	}

	if (bossEnemy.collidesWith(player) && player.getCanBeKilled())
	{
		player.setHealthPoints(0);
	}
}

void Level01::spawnBoss()
{
	if (nbOfEnemiesToGenerate <= MAX_NB_OF_ENEMIES_TO_GENERATE)
		return;

	for (StandardEnemy& currentStandardEnemy : standardsEnemies)
	{
		if (currentStandardEnemy.isActive())
		{
			return;
		}
	}

	bossEnemy.initializeContent(contentManager);
}

void Level01::handleEvent()
{
	inputs.reset();

	if (sf::Joystick::isConnected(0))
	{
		inputs.moveY = inputs.eliminateVibration(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y)) / GAMEPAD_SPEEDRATIO;
		inputs.moveX = inputs.eliminateVibration(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X)) / GAMEPAD_SPEEDRATIO;
		inputs.shouldFire = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Z) < -50;

		if (event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 3)
			inputs.isInvincible = !inputs.isInvincible;

		//Convertir les données du contrôleur en SPEED
		if (inputs.moveX > 0.0f)
			inputs.moveX = SPEED;

		else if (inputs.moveX < 0.0f)
			inputs.moveX = -SPEED;

		if (inputs.moveY > 0.0f)
			inputs.moveY = SPEED;

		else if (inputs.moveY < 0.0f)
			inputs.moveY = -SPEED;
	}
	else
	{
		inputs.moveX += sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ? SPEED : 0.0f;
		inputs.moveX += sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ? -SPEED : 0.0f;
		inputs.moveY += sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) ? SPEED : 0.0f;
		inputs.moveY += sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ? -SPEED : 0.0f;

		inputs.shouldFire = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::BackSpace)
				inputs.isInvincible = !inputs.isInvincible;
		}
	}

	//std::cout << "Speed: " << inputs.moveX << ", " << inputs.moveY << std::endl;
	//std::cout << "isInvincible: " << inputs.isInvincible << std::endl;
}
