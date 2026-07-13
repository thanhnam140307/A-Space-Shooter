#pragma once
#include "AnimationFrame.h"
struct Inputs;
class ContentManager;
class Animation
{
public:
	//Question : Pourquoi l'ajoût d'un destructeur virtuel est fortement recommandé ici ?
	//Votre réponse :
	virtual ~Animation();
	void reset();
	virtual void update(float deltaT);
	virtual unsigned int getNextFrame() const = 0;
	virtual bool init(const ContentManager& contentManager) = 0;
	float getTimeInCurrentState() const;
	virtual bool isOver() const;
	virtual float getPercentage() const = 0;
protected:

	Animation(sf::Sprite& s, float length);
	std::vector<AnimationFrame> frames;
	float lengthInSeconds;
	float timeInCurrentState;

private:
	sf::Sprite& sprite;
};

