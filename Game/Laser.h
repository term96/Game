#pragma once
#include "Constants.h"
#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "IObject.h"

enum LaserDirection
{
	UP = -1, DOWN = 1
};

class CLaser : public IObject
{
public:
	CLaser(sf::Vector2f position, LaserDirection direction);
	~CLaser() = default;

	void Update(float deltaTime) override;
	sf::Vector2f GetPosition() const override;
	sf::RectangleShape & GetShape() override;
private:
	void Move(float deltaTime);

	LaserDirection m_direction;
	float m_speed = 600.f;
	sf::RectangleShape m_shape;
};

