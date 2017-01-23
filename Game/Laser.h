#pragma once
#include "Constants.h"
#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "IObject.h"

enum LaserType
{
	RED = -1, BLUE = 1
};

class CLaser : public IObject
{
public:
	CLaser(sf::Vector2f position, LaserType direction);
	~CLaser() = default;

	void Update(float deltaTime) override;
	sf::Vector2f GetPosition() const override;
	sf::RectangleShape & GetShape() override;

	LaserType GetType() const;
private:
	void Move(float deltaTime);

	LaserType m_type;
	sf::RectangleShape m_shape;
};

