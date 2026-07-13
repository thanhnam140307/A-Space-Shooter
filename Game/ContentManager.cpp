#include "stdafx.h"
#include "ContentManager.h"

const std::string ContentManager::VICTORY_END_SCREEN_TEXTURE_PATH = "Assets\\Sprites\\End\\VictoryEndGameScene.png";
const std::string ContentManager::DEFEATED_END_SCREEN_TEXTURE_PATH = "Assets\\Sprites\\End\\DefeatedEndGameScene.png";
const std::string ContentManager::GAME_SCREEN_TEXTURE_PATH = "Assets\\Sprites\\Level01\\SpaceBackground.png";
const std::string ContentManager::TITLE_SCREEN_TEXTURE_PATH = "Assets\\Sprites\\Title\\Title.png";
const std::string ContentManager::GUARDIAN_ALYSSA_BMP_PATH = "Assets\\Sprites\\Level01\\NES - The Guardian Legend - The Guardian Alyssa.bmp";
const std::string ContentManager::GUARDIAN_LEGEND_MISCELLANEOUS_BMP_PATH = "Assets\\Sprites\\Level01\\NES - The Guardian Legend - Miscellaneous.bmp";
const std::string ContentManager::SMART_GUN_TEXTURE_PATH = "Assets\\Sprites\\Level01\\smartgun.bmp";
const std::string ContentManager::ENEMIES_TEXTURE_PATH = "Assets\\Sprites\\Level01\\NES - The Guardian Legend - Bosses.bmp";
const std::string ContentManager::ENEMY_GUN_SOUND_PATH = "Assets\\SoundFX\\Level01\\enemyGun.wav";
const std::string ContentManager::ENEMY_KILLED_SOUND_PATH = "Assets\\SoundFX\\Level01\\enemyKilled.wav";
const std::string ContentManager::GUN_BONUS_SOUND_PATH = "Assets\\SoundFX\\Level01\\gunBonus.wav";
const std::string ContentManager::HEALTH_BONUS_SOUND_PATH = "Assets\\SoundFX\\Level01\\healthBonus.wav";
const std::string ContentManager::PLAYER_GUN_SOUND_PATH = "Assets\\SoundFX\\Level01\\playerGun.wav";
const std::string ContentManager::FONT_PATH = "Assets\\Fonts\\Level01\\emulogic.ttf";

ContentManager::ContentManager()
{
}

bool ContentManager::loadContent()
{
	if (!victoryEndScreenTexture.loadFromFile(VICTORY_END_SCREEN_TEXTURE_PATH))
		return false;

	if (!defeatedEndScreenTexture.loadFromFile(DEFEATED_END_SCREEN_TEXTURE_PATH))
		return false;

	if (!gameScreenTexture.loadFromFile(GAME_SCREEN_TEXTURE_PATH))
		return false;

	gameScreenTexture.setRepeated(true);

	if (!titleScreenTexture.loadFromFile(TITLE_SCREEN_TEXTURE_PATH))
		return false;

	if (!guardianAlyssaBmp.loadFromFile(GUARDIAN_ALYSSA_BMP_PATH))
		return false;

	if (!guardianLegendMiscellaneousBmp.loadFromFile(GUARDIAN_LEGEND_MISCELLANEOUS_BMP_PATH))
		return false;

	if (!smartGunTexture.loadFromFile(SMART_GUN_TEXTURE_PATH))
		return false;

	if (!enemiesTexture.loadFromFile(ENEMIES_TEXTURE_PATH))
		return false;

	if (!enemyGunSound.loadFromFile(ENEMY_GUN_SOUND_PATH))
		return false;

	if (!enemyKilledSound.loadFromFile(ENEMY_KILLED_SOUND_PATH))
		return false;

	if (!gunBonusSound.loadFromFile(GUN_BONUS_SOUND_PATH))
		return false;

	if (!healthBonusSound.loadFromFile(HEALTH_BONUS_SOUND_PATH))
		return false;

	if (!playerGunSound.loadFromFile(PLAYER_GUN_SOUND_PATH))
		return false;

	if (!font.loadFromFile(FONT_PATH))
		return false;

	return true;
}

const sf::Texture& ContentManager::getVictoryEndScreenTexture() const
{
	return victoryEndScreenTexture;
}

const sf::Texture& ContentManager::getDefeatedEndScreenTexture() const
{
	return defeatedEndScreenTexture;
}

const sf::Texture& ContentManager::getGameScreenTexture() const
{
	return gameScreenTexture;
}

const sf::Texture& ContentManager::getTitleScreenTexture() const
{
	return titleScreenTexture;
}

const sf::Texture& ContentManager::getGuardianAlyssaBmp() const
{
	return guardianAlyssaBmp;
}

const sf::Texture& ContentManager::getGuardianLegendMiscellaneousBmp() const
{
	return guardianLegendMiscellaneousBmp;
}

const sf::Texture& ContentManager::getSmartGunTexture() const
{
	return smartGunTexture;
}

const sf::Texture& ContentManager::getEnemiesTexture() const
{
	return enemiesTexture;
}

const sf::SoundBuffer& ContentManager::getEnemyGunSound() const
{
	return enemyGunSound;
}

const sf::SoundBuffer& ContentManager::getEnemyKilledSound() const
{
	return enemyKilledSound;
}

const sf::SoundBuffer& ContentManager::getGunBonusSound() const
{
	return gunBonusSound;
}

const sf::SoundBuffer& ContentManager::getHealthBonusSound() const
{
	return healthBonusSound;
}

const sf::SoundBuffer& ContentManager::getPlayerGunSound() const
{
	return playerGunSound;
}

const sf::Font& ContentManager::getFont() const
{
	return font;
}