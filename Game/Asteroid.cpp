#include "Asteroid.h"
#include "Resources.h"

using namespace sf;
using namespace std;

CAsteroid::CAsteroid(Vector2f position)
{
	const Texture * texture = Resources::GetRandomAsteroidTexture();
	Vector2f size;
	size.x = static_cast<float>(texture->getSize().x);
	size.y = static_cast<float>(texture->getSize().y);
	
	m_shape.setSize(size);
	m_shape.setTexture(texture);
	m_shape.setOrigin(size.x / 2, size.y / 2);
	m_shape.setPosition(position.x + size.x / 2, position.y + size.y / 2);

	m_horizontalSpeed = static_cast<float>(WINDOW_WIDTH) / 
		(rand() % (ASTEROID_MAX_HOR_TIME - ASTEROID_MIN_HOR_TIME) + ASTEROID_MIN_HOR_TIME);
	if (rand() % 2 == 0)
		m_direction = Direction::LEFT;
	else
		m_direction = Direction::RIGHT;
}

void CAsteroid::Update(float deltaTime)
{
	m_shape.move(m_direction * m_horizontalSpeed * deltaTime, ASTEROID_VERT_SPEED * deltaTime);
	m_shape.rotate(m_direction * ASTEROID_ROTATION * deltaTime);
}

sf::Vector2f CAsteroid::GetPosition() const
{
	return m_shape.getPosition();
}

sf::RectangleShape & CAsteroid::GetShape()
{
	return m_shape;
}

float CAsteroid::GetHorizontalSpeed() const
{
	return m_horizontalSpeed * m_direction;
}
