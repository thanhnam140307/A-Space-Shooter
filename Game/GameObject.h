#pragma once

class ContentManager;
class GameObject : public sf::Sprite
{
public:
	GameObject();
	GameObject(const GameObject& src);
	
	virtual void draw(sf::RenderWindow& window) const;
	
	virtual void activate(bool _active);

	bool isActive() const;

	sf::FloatRect getBoundingRectangle() const;
	bool collidesWith(const GameObject& other) const;
	bool collidesWith(const sf::Vector2f& other) const;

	float getRotationAngleInRadians() const;
	void setRotationAngleRadians(const float angle);
	virtual void rotateInRadians(const float angle);

	virtual void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition);
	virtual void initializeContent(const ContentManager& manager);
protected:
	
	float getAngleWith(const GameObject& other) const;
	bool active;
};

