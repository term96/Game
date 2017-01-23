#include "Hint.h"

using namespace std;
using namespace sf;

CHint::CHint(wstring const & hint, Vector2f position, int characterSize, float time)
{
	m_text.SetString(hint);
	m_text.SetCharacterSize(characterSize);
	Vector2f hintPos;
	hintPos.x = position.x - m_text.GetWidth() / 2;
	hintPos.y = position.y - m_text.GetHeight() / 2;
	m_text.SetPosition(hintPos);
	m_time = time;
	m_hintTime = time;
}

void CHint::Update(float deltaTime)
{
	m_time -= deltaTime;
	if (m_time <= 0)
	{
		m_stopped = true;
	}
	int alpha = static_cast<int>(255 * m_time / m_hintTime);
	m_text.SetFillColor(Color(255, 255, 255, alpha));
}

bool CHint::IsStopped() const
{
	return m_stopped;
}

Text & CHint::GetShape()
{
	return m_text.GetShape();
}
