#pragma once
#include <vector>
#include "SFML\Graphics.hpp"

class CAnimation
{
public:
	CAnimation(std::vector<sf::Texture> const & textures, float animationTime, bool repeated);
	const sf::Texture * GetTexture() const;
	void Update(float deltaTime);
	bool IsStopped() const;
	int GetFrame() const;
private:
	std::vector<sf::Texture> const & m_textures;
	int m_frame;
	float m_time;
	float m_animationTime;
	bool m_repeated;
	bool m_stopped = false;
};

