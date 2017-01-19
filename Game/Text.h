#pragma once
#include "Constants.h"
#include "Resources.h"
#include "SFML\Graphics.hpp"

class CText
{
public:
	CText();
	sf::Text & GetShape();
	float GetBottomBound() const;
	float GetUpperBound() const;
	float GetWidth() const;
	float GetHeight() const;

	void SetString(std::wstring const & string);
	void SetCharacterSize(int size);
	void SetFillColor(sf::Color color);
	void SetPosition(sf::Vector2f position);
protected:
	sf::Text m_text;
};

