#include "stdafx.h"
#include "Hud.h"
#include "ContentManager.h"
#include "game.h"

Hud::Hud()
{

}

void Hud::initialize(const ContentManager& contentManager)
{
	float mapLimit = float(Level01::LIMIT);

	hudView = sf::View(sf::FloatRect(0, 0, (float)Game::GAME_WIDTH, (float)Game::GAME_HEIGHT));
	font = contentManager.getFont();

	scoreText.setFont(font);
	scoreText.setCharacterSize(20);
	scoreText.setOutlineColor(sf::Color::White);
	scoreText.setPosition(mapLimit, Game::GAME_HEIGHT - mapLimit);

	healthText.setFont(font);
	healthText.setCharacterSize(20);
	healthText.setOutlineColor(sf::Color::White);
	healthText.setPosition(Game::GAME_WIDTH - (mapLimit * 8), Game::GAME_HEIGHT - mapLimit);
	sf::FloatRect healthTextRect = healthText.getLocalBounds();
	healthText.setOrigin(healthTextRect.width / BaseGame::HALF, healthTextRect.height / BaseGame::HALF);

	heart.setTexture(contentManager.getGuardianLegendMiscellaneousBmp());
	heart.setTextureRect(sf::IntRect(226, 61, 17, 15));
	heart.setScale(Bonus::SCALE, Bonus::SCALE);
	sf::FloatRect heartRect = heart.getLocalBounds();
	heart.setOrigin(heartRect.width / BaseGame::HALF, heartRect.height / BaseGame::HALF);
	heart.setPosition(healthText.getPosition().x - 30.0f, healthText.getPosition().y + 10.0f);

	nbOfSmartGunText.setFont(font);
	nbOfSmartGunText.setCharacterSize(20);
	nbOfSmartGunText.setOutlineColor(sf::Color::White);
	nbOfSmartGunText.setPosition(Game::GAME_WIDTH - (mapLimit), Game::GAME_HEIGHT - mapLimit);
	sf::FloatRect nbOfSmartGunTextRect = nbOfSmartGunText.getLocalBounds();
	nbOfSmartGunText.setOrigin(nbOfSmartGunTextRect.width / BaseGame::HALF, nbOfSmartGunTextRect.height / BaseGame::HALF);

	smartGunBonus.setTexture(contentManager.getGuardianLegendMiscellaneousBmp());
	smartGunBonus.setTextureRect(sf::IntRect(247, 103, 18, 18));
	smartGunBonus.setScale(Bonus::SCALE, Bonus::SCALE);
	sf::FloatRect smartGunBonusRect = smartGunBonus.getLocalBounds();
	smartGunBonus.setOrigin(smartGunBonusRect.width / BaseGame::HALF, smartGunBonusRect.height / BaseGame::HALF);
	smartGunBonus.setPosition(nbOfSmartGunText.getPosition().x - 30.0f, nbOfSmartGunText.getPosition().y + 10.0f);
}

void Hud::setScoreText(const int score)
{
	scoreText.setString("Score: " + std::to_string(score));
}

void Hud::setHealthText(const int healthPoints)
{
	healthText.setString(std::to_string(healthPoints));
}

void Hud::setNbOfSmartGunText(const int nbOfSmartGun)
{
	nbOfSmartGunText.setString(std::to_string(nbOfSmartGun));
}

void Hud::draw(sf::RenderWindow& window) const
{
	window.setView(hudView);
	window.draw(scoreText);
	window.draw(heart);
	window.draw(healthText);
	window.draw(smartGunBonus);
	window.draw(nbOfSmartGunText);
}