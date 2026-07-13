#pragma once
#include "ContentManager.h"

using namespace std;

class Hud
{
public:
	Hud();
	void draw(sf::RenderWindow& window)  const;
	void initialize(const ContentManager& contentManager);
	void setScoreText(const int score);
	void setHealthText(const int healthPoints);
	void setNbOfSmartGunText(const int healthPoints);

private:
	sf::View hudView;
	sf::Text scoreText;
	sf::Sprite heart;
	sf::Text healthText;
	sf::Sprite smartGunBonus;
	sf::Text nbOfSmartGunText;
	sf::Font font;
};

