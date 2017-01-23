#include "Bonus.h"
#include "Resources.h"
#include <math.h>

using namespace std;
using namespace sf;

BonusType CBonus::nextBonusType = BonusType::HEALTH;

CBonus::CBonus(sf::Vector2f position)
{
	m_shape.setOrigin(BONUS_WIDTH / 2, BONUS_HEIGHT / 2);
	m_shape.setSize(Vector2f(BONUS_WIDTH, BONUS_HEIGHT));
	m_shape.setPosition(position.x + BONUS_WIDTH / 2, position.y + BONUS_HEIGHT / 2);
	SetBonusType();
}

void CBonus::Update(float deltaTime)
{
	m_shape.move(0.f, BONUS_SPEED * deltaTime);
}

sf::Vector2f CBonus::GetPosition() const
{
	return m_shape.getPosition();
}

BonusType CBonus::GetType() const
{
	return m_type;
}

void CBonus::SetBonusType()
{
	m_type = nextBonusType;
	if (nextBonusType == BonusType::HEALTH)
	{
		m_shape.setTexture(Resources::GetHealthStarTexture());
		nextBonusType = BonusType::SLOW_MO;
	}
	else
	{
		m_shape.setTexture(Resources::GetSlowStarTexture());
		nextBonusType = BonusType::HEALTH;
	}
}

sf::RectangleShape & CBonus::GetShape()
{
	return m_shape;
}
