#include "stdafx.h"
#include "GameObject.h"
constexpr auto RADIANS_TO_DEGREE = 57.295779513f;

GameObject::GameObject()
	: Sprite()
	, active(false)
{
}

GameObject::GameObject(const GameObject& src)
	: Sprite(src)
	, active(src.active)
{
	if (nullptr != src.getTexture())
	{
		setTextureRect(src.getTextureRect());
		// Super important pour éviter le bogue du carré blanc
		// Attention au fait qu'on appelle une méthode virtuelle dans un 
		// constructeur: seule la méthode de la classe parent (GameObject)
		// sera appelée.
		initialize(*src.getTexture(), src.getPosition());
	}
}

float GameObject::getAngleWith(const GameObject& other) const
{
	return atan2f(other.getPosition().y - getPosition().y, other.getPosition().x - getPosition().x);
}

void GameObject::draw(sf::RenderWindow& window) const
{
	if (isActive())
		window.draw(*this);
}

void GameObject::activate(bool _active)
{
	active = _active;
}

bool GameObject::isActive() const
{
	return active;
}

sf::FloatRect GameObject::getBoundingRectangle() const
{
	return getGlobalBounds();
}

bool GameObject::collidesWith(const GameObject& other) const
{
	// Si l'un des GameObject n'est pas actif il ne peut pas entrer en collision
	return    isActive()
		&& other.isActive()
		&& getGlobalBounds().intersects(other.getGlobalBounds());
}

bool GameObject::collidesWith(const sf::Vector2f& other) const
{
	// Si l'un des GameObject n'est pas actif il ne peut pas entrer en collision
	return    isActive()
		&& getGlobalBounds().contains(other);
}


float GameObject::getRotationAngleInRadians() const
{
	return getRotation() / RADIANS_TO_DEGREE;
}


void GameObject::setRotationAngleRadians(const float angle)
{
	setRotation(angle * RADIANS_TO_DEGREE);
}

void GameObject::rotateInRadians(const float angle)
{
	rotate(angle * RADIANS_TO_DEGREE);
}

void GameObject::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition)
{
	setTexture(texture);
	const sf::IntRect& rect = getTextureRect();
	setOrigin(sf::Vector2f(rect.width / 2.0f, rect.height / 2.0f));
	setPosition(initialPosition);
}

void GameObject::initializeContent(const ContentManager& /*manager*/)
{
}
