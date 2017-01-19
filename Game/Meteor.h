#pragma once
#include "IObject.h"
#include "Constants.h"

enum Direction
{
	LEFT = -1, RIGHT = 1
};

class CMeteor :
	public IObject
{
public:
	CMeteor(sf::Vector2f position);
	~CMeteor() = default;
	
	void Update(float deltaTime) override;

	sf::Vector2f GetPosition() const override;
	sf::RectangleShape & GetShape() override;
private:
	sf::RectangleShape m_shape;
	Direction m_direction;
	float m_horizontalSpeed;
};

