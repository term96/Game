#pragma once

#include "SFML\Graphics.hpp"
#include <vector>

class Resources
{
public:
	static void Init();

	static const std::vector<sf::Texture> & GetShooterAnimation();
	static const std::vector<sf::Texture> & GetPlayerAnimation();
	static const std::vector<sf::Texture> & GetAsteroidExplosion();
	static const std::vector<sf::Texture> & GetShooterExplosion();
	static const std::vector<sf::Texture> & GetRedDamage();
	static const std::vector<sf::Texture> & GetBlueDamage();

	static const sf::Texture * GetRandomAsteroidTexture();
	static const sf::Texture & GetBackgroundTexture();

	static const sf::Texture * GetLaserUpTexture();
	static const sf::Texture * GetLaserDownTexture();

	static const sf::Texture * GetHealthStarTexture();
	static const sf::Texture * GetSlowStarTexture();

	static const sf::Font & GetFont();
private:
	static std::vector<sf::Texture> m_shooterAnimation;
	static std::vector<sf::Texture> m_playerAnimation;
	static std::vector<sf::Texture> m_asteroidExplosion;
	static std::vector<sf::Texture> m_shooterExplosion;
	static std::vector<sf::Texture> m_redDamage;
	static std::vector<sf::Texture> m_blueDamage;

	static sf::Texture m_laserUp;
	static sf::Texture m_laserDown;

	static sf::Texture m_asteroid1;
	static sf::Texture m_asteroid2;
	static sf::Texture m_asteroid3;

	static sf::Texture m_healthStar;
	static sf::Texture m_slowStar;
	static sf::Texture m_background;

	static sf::Font m_font;
};

