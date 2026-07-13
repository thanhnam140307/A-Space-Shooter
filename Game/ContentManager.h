#pragma once
class ContentManager
{
public:
	ContentManager();
	virtual bool loadContent();
	const sf::Texture& getVictoryEndScreenTexture() const;
	const sf::Texture& getDefeatedEndScreenTexture() const;
	const sf::Texture& getGameScreenTexture() const;
	const sf::Texture& getTitleScreenTexture() const;

	const sf::Texture& getGuardianAlyssaBmp() const;
	const sf::Texture& getGuardianLegendMiscellaneousBmp() const;
	const sf::Texture& getSmartGunTexture() const;
	const sf::Texture& getEnemiesTexture() const;

	const sf::SoundBuffer& getEnemyGunSound() const;
	const sf::SoundBuffer& getEnemyKilledSound() const;
	const sf::SoundBuffer& getGunBonusSound() const;
	const sf::SoundBuffer& getHealthBonusSound() const;
	const sf::SoundBuffer& getPlayerGunSound() const;

	const sf::Font& getFont() const;

private:
	sf::Texture victoryEndScreenTexture;
	sf::Texture defeatedEndScreenTexture;
	sf::Texture gameScreenTexture;
	sf::Texture titleScreenTexture;

	sf::Texture guardianAlyssaBmp; //Vaisseau
	sf::Texture guardianLegendMiscellaneousBmp; //Bonus
	sf::Texture smartGunTexture;
	sf::Texture enemiesTexture;

	sf::SoundBuffer playerGunSound;
	sf::SoundBuffer enemyGunSound;
	sf::SoundBuffer enemyKilledSound;
	sf::SoundBuffer gunBonusSound;
	sf::SoundBuffer healthBonusSound;

	sf::Font font;

	// Textures
	static const std::string VICTORY_END_SCREEN_TEXTURE_PATH;
	static const std::string DEFEATED_END_SCREEN_TEXTURE_PATH;
	static const std::string GAME_SCREEN_TEXTURE_PATH;
	static const std::string TITLE_SCREEN_TEXTURE_PATH;
	static const std::string GUARDIAN_ALYSSA_BMP_PATH;
	static const std::string GUARDIAN_LEGEND_MISCELLANEOUS_BMP_PATH;
	static const std::string SMART_GUN_TEXTURE_PATH;
	static const std::string ENEMIES_TEXTURE_PATH;

	// Sounds
	static const std::string ENEMY_GUN_SOUND_PATH;
	static const std::string ENEMY_KILLED_SOUND_PATH;
	static const std::string GUN_BONUS_SOUND_PATH;
	static const std::string HEALTH_BONUS_SOUND_PATH;
	static const std::string PLAYER_GUN_SOUND_PATH;

	// Fonts
	static const std::string FONT_PATH;
};



