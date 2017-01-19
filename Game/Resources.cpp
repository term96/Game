#include "Resources.h"
#include <math.h>

using namespace sf;
Texture Resources::m_player;
Texture Resources::m_shooter;
Texture Resources::m_background;

Texture Resources::m_laserUp;
Texture Resources::m_laserDown;

Texture Resources::m_meteor1;
Texture Resources::m_meteor2;
Texture Resources::m_meteor3;

Texture Resources::m_healthStar;
Texture Resources::m_slowStar;

Font Resources::m_font;

void Resources::Init()
{
	m_player.loadFromFile("resources/player.png");
	m_shooter.loadFromFile("resources/shooter.png");
	m_background.loadFromFile("resources/background.jpg");

	m_laserUp.loadFromFile("resources/laserUp.png");
	m_laserDown.loadFromFile("resources/laserDown.png");

	m_meteor1.loadFromFile("resources/meteor1.png");
	m_meteor2.loadFromFile("resources/meteor2.png");
	m_meteor3.loadFromFile("resources/meteor3.png");

	m_healthStar.loadFromFile("resources/healthStar.png");
	m_slowStar.loadFromFile("resources/slowStar.png");

	m_font.loadFromFile("resources/font.ttf");

	m_background.setRepeated(true);
}

const sf::Texture * Resources::GetShooterTexture()
{
	return &m_shooter;
}

const sf::Texture * Resources::GetPlayerTexture()
{
	return &m_player;
}

const sf::Texture * Resources::GetLaserUpTexture()
{
	return &m_laserUp;
}

const sf::Texture * Resources::GetLaserDownTexture()
{
	return &m_laserDown;
}

const sf::Texture * Resources::GetHealthStarTexture()
{
	return &m_healthStar;
}

const sf::Texture * Resources::GetSlowStarTexture()
{
	return &m_slowStar;
}

const sf::Texture & Resources::GetBackgroundTexture()
{
	return m_background;
}

const sf::Texture * Resources::GetRandomMeteorTexture()
{
	int meteor = rand() % 3;
	switch (meteor)
	{
	case 0:
		return &m_meteor1;
	case 1:
		return &m_meteor2;
	default:
		return &m_meteor3;
	}
}

const sf::Font & Resources::GetFont()
{
	return m_font;
}
