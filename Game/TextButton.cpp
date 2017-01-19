#include "TextButton.h"

using namespace sf;

void CTextButton::Highlight()
{
	m_text.setFillColor(Color(0, 0, 255, 128));
}

void CTextButton::Unhighlight()
{
	m_text.setFillColor(Color::White);
}

bool CTextButton::IsHovered(Vector2i const & position) const
{
	FloatRect mouse(static_cast<float>(position.x), static_cast<float>(position.y), 1.f, 1.f);
	return m_text.getGlobalBounds().intersects(mouse);
}
