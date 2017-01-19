#include "Meteor.h"
#include "Resources.h"

using namespace sf;
using namespace std;

CMeteor::CMeteor(Vector2f position)
{
	const Texture * texture = Resources::GetRandomMeteorTexture();
	Vector2f size;
	size.x = static_cast<float>(texture->getSize().x);
	size.y = static_cast<float>(texture->getSize().y);
	
	m_shape.setSize(size);
	m_shape.setTexture(texture);
	m_shape.setPosition(position);

	m_horizontalSpeed = static_cast<float>(WINDOW_WIDTH) / 
		(rand() % (METEOR_MAX_HOR_SPEED - METEOR_MIN_HOR_SPEED) + METEOR_MIN_HOR_SPEED);
	if (rand() % 2 == 0)
		m_direction = Direction::LEFT;
	else
		m_direction = Direction::RIGHT;
}

void CMeteor::Update(float deltaTime)
{
	m_shape.move(m_direction * m_horizontalSpeed * deltaTime, METEOR_VERT_SPEED * deltaTime);
	m_shape.rotate(m_direction * METEOR_ROTATION * deltaTime);
}

sf::Vector2f CMeteor::GetPosition() const
{
	return m_shape.getPosition();
}

sf::RectangleShape & CMeteor::GetShape()
{
	return m_shape;
}
