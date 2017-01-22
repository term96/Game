#pragma once
#include "IObject.h"
#include "Constants.h"

enum Direction
{
	LEFT = -1, RIGHT = 1
};

class CAsteroid :
	public IObject
{
public:
	CAsteroid(sf::Vector2f position);
	~CAsteroid() = default;
	
	void Update(float deltaTime) override;
	sf::Vector2f GetPosition() const override;
	sf::RectangleShape & GetShape() override;

	float GetHorizontalSpeed() const;
private:
	sf::RectangleShape m_shape;
	Direction m_direction;
	float m_horizontalSpeed;
};

