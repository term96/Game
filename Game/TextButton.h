#pragma once
#include "Text.h"
#include "SFML\Graphics.hpp"

class CTextButton
	: public CText
{
public:
	CTextButton() = default;
	void Highlight();
	void Unhighlight();
	bool IsHovered(sf::Vector2i const & position) const;
};

