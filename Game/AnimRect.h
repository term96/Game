#pragma once
#include "SFML\Graphics.hpp"
#include "Animation.h"

class CAnimRect
{
public:
	CAnimRect(sf::Vector2f position, std::vector<sf::Texture> const & textures, 
		float animationTime);
	void Update(float deltaTime);
	bool IsStopped() const;
	sf::RectangleShape & GetShape();
private:
	CAnimation m_animation;
	sf::RectangleShape m_shape;
	float m_animationTime;
	float m_time = 0;
};

