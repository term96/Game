#include "AnimRect.h"
#include "Constants.h"
#include "Resources.h"
#include <vector>

using namespace std;
using namespace sf;

CAnimRect::CAnimRect(Vector2f position, vector<Texture> const & textures, float animationTime)
	:m_animation(textures, animationTime, false)
{
	m_animationTime = animationTime;
	Vector2u size = m_animation.GetTexture()->getSize();
	m_shape.setOrigin(static_cast<float>(size.x) / 2, static_cast<float>(size.y) / 2);
	m_shape.setPosition(position);
	m_shape.setSize(Vector2f(static_cast<float>(size.x), static_cast<float>(size.y)));
	m_shape.setTexture(m_animation.GetTexture());
}

void CAnimRect::Update(float deltaTime)
{
	m_time += deltaTime;
	int alpha = static_cast<int>(255 * (m_animationTime - m_time));
	m_shape.setFillColor(Color(255, 255, 255, alpha));

	m_animation.Update(deltaTime);
	m_shape.setTexture(m_animation.GetTexture());
}

bool CAnimRect::IsStopped() const
{
	return m_animation.IsStopped();
}

RectangleShape & CAnimRect::GetShape()
{
	return m_shape;
}
