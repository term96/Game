#pragma once
#include <string>
#include "SFML\Graphics.hpp"
#include "Text.h"

class CHint
{
public:
	CHint(std::wstring const & hint, sf::Vector2f position, int characterSize, float time);
	void Update(float deltaTime);
	bool IsStopped() const;
	sf::Text & GetShape();
private:
	CText m_text;
	float m_hintTime;
	float m_time;
	bool m_stopped = false;
};

