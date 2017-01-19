#include "Text.h"
#include <string>

using namespace std;
using namespace sf;

CText::CText()
{
	m_text.setFont(Resources::GetFont());
	m_text.setCharacterSize(36);
	m_text.setFillColor(Color::White);
	m_text.setOutlineColor(Color::Black);
	m_text.setOutlineThickness(1);
}

void CText::SetString(wstring const & string)
{
	m_text.setString(string);
}

void CText::SetCharacterSize(int size)
{
	m_text.setCharacterSize(size);
}

void CText::SetFillColor(sf::Color color)
{
	m_text.setFillColor(color);
}

void CText::SetPosition(sf::Vector2f position)
{
	m_text.setPosition(position);
}

sf::Text & CText::GetShape()
{
	return m_text;
}

float CText::GetBottomBound() const
{
	return m_text.getPosition().y + m_text.getGlobalBounds().height;
}

float CText::GetUpperBound() const
{
	return m_text.getPosition().y;
}

float CText::GetWidth() const
{
	return m_text.getGlobalBounds().width;
}

float CText::GetHeight() const
{
	return m_text.getGlobalBounds().height;
}
