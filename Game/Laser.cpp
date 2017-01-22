#include "Laser.h"
#include "Resources.h"

using namespace sf;
using namespace std;

CLaser::CLaser(Vector2f position, LaserDirection direction)
{
	m_shape.setOrigin(LASER_WIDTH / 2, LASER_HEIGHT / 2);
	m_shape.setSize(Vector2f(LASER_WIDTH, LASER_HEIGHT));
	m_shape.setPosition(position.x + LASER_WIDTH / 2, position.y + LASER_HEIGHT / 2);
	m_direction = direction;

	if (direction == LaserDirection::UP)
	{
		m_shape.setTexture(Resources::GetLaserUpTexture());
	}
	else
	{
		m_shape.setTexture(Resources::GetLaserDownTexture());
	}
}

Vector2f CLaser::GetPosition() const
{
	return m_shape.getPosition();
}

void CLaser::Update(float deltaTime)
{
	Move(deltaTime);
}

sf::RectangleShape & CLaser::GetShape()
{
	return m_shape;
}

void CLaser::Move(float deltaTime)
{
	m_shape.move(0, m_direction * LASER_SPEED * deltaTime);
}