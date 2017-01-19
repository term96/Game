#pragma once

#include "SFML\Graphics.hpp"

class Resources
{
public:
	static void Init();
	static const sf::Texture * GetShooterTexture();
	static const sf::Texture * GetPlayerTexture();
	static const sf::Texture * GetRandomMeteorTexture();
	static const sf::Texture & GetBackgroundTexture();

	static const sf::Texture * GetLaserUpTexture();
	static const sf::Texture * GetLaserDownTexture();

	static const sf::Texture * GetHealthStarTexture();
	static const sf::Texture * GetSlowStarTexture();

	static const sf::Font & GetFont();
private:
	static sf::Texture m_shooter;
	static sf::Texture m_player;
	static sf::Texture m_background;

	static sf::Texture m_laserUp;
	static sf::Texture m_laserDown;

	static sf::Texture m_meteor1;
	static sf::Texture m_meteor2;
	static sf::Texture m_meteor3;

	static sf::Texture m_healthStar;
	static sf::Texture m_slowStar;

	static sf::Font m_font;
};

