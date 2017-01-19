#pragma once

#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"

class IObject
{
public:
	virtual void Update(float deltaTime) = 0;
	virtual sf::Vector2f GetPosition() const = 0;
	virtual sf::RectangleShape & GetShape() = 0;
};

