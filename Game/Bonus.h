#pragma once
#include "SFML\Graphics.hpp"
#include "Constants.h"
#include "IObject.h"

enum BonusType
{
	HEALTH, SLOW_MO
};

class CBonus : public IObject
{
public:
	CBonus(sf::Vector2f position);
	
	void Update(float deltaTime) override;
	sf::Vector2f GetPosition() const override;
	sf::RectangleShape & GetShape() override;

	BonusType GetType() const;
private:
	void SetBonusType();
	sf::RectangleShape m_shape;
	BonusType m_type;

	static BonusType nextBonusType;
};

