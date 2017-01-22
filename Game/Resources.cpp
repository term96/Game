#include "Resources.h"
#include <math.h>

using namespace sf;
using namespace std;

vector<Texture> Resources::m_shooterAnimation;
vector<Texture> Resources::m_playerAnimation;
vector<Texture> Resources::m_shooterExplosion;
vector<Texture> Resources::m_asteroidExplosion;
vector<Texture> Resources::m_redDamage;
vector<Texture> Resources::m_blueDamage;

Texture Resources::m_laserUp;
Texture Resources::m_laserDown;

Texture Resources::m_asteroid1;
Texture Resources::m_asteroid2;
Texture Resources::m_asteroid3;

Texture Resources::m_healthStar;
Texture Resources::m_slowStar;
Texture Resources::m_background;

Font Resources::m_font;

void Resources::Init()
{
	Texture texture;
	for (int i = 1; i <= 8; ++i)
	{
		texture.loadFromFile("resources/shooter/" + to_string(i) + ".png");
		m_shooterAnimation.push_back(texture);
	}
	for (int i = 1; i <= 8; ++i)
	{
		texture.loadFromFile("resources/player/" + to_string(i) + ".png");
		m_playerAnimation.push_back(texture);
	}
	for (int i = 0; i <= 8; ++i)
	{
		texture.loadFromFile("resources/shooter_explosion/explosion0" + to_string(i) + ".png");
		m_shooterExplosion.push_back(texture);
	}
	for (int i = 0; i <= 14; ++i)
	{
		texture.loadFromFile("resources/asteroid_explosion/" + to_string(i) + ".png");
		m_asteroidExplosion.push_back(texture);
	}
	for (int i = 0; i <= 16; ++i)
	{
		texture.loadFromFile("resources/red_damage/1_" + to_string(i) + ".png");
		m_redDamage.push_back(texture);
	}
	for (int i = 0; i <= 16; ++i)
	{
		texture.loadFromFile("resources/blue_damage/1_" + to_string(i) + ".png");
		m_blueDamage.push_back(texture);
	}

	m_laserUp.loadFromFile("resources/laserUp.png");
	m_laserDown.loadFromFile("resources/laserDown.png");

	m_asteroid1.loadFromFile("resources/asteroid1.png");
	m_asteroid2.loadFromFile("resources/asteroid2.png");
	m_asteroid3.loadFromFile("resources/asteroid3.png");

	m_healthStar.loadFromFile("resources/healthStar.png");
	m_slowStar.loadFromFile("resources/slowStar.png");
	m_background.loadFromFile("resources/background.jpg");

	m_font.loadFromFile("resources/font.ttf");
}

const vector<Texture> & Resources::GetShooterAnimation()
{
	return m_shooterAnimation;
}

const vector<Texture> & Resources::GetPlayerAnimation()
{
	return m_playerAnimation;
}

const vector<Texture> & Resources::GetShooterExplosion()
{
	return m_shooterExplosion;
}

const vector<Texture> & Resources::GetAsteroidExplosion()
{
	return m_asteroidExplosion;
}

const vector<Texture> & Resources::GetRedDamage()
{
	return m_redDamage;
}

const vector<Texture> & Resources::GetBlueDamage()
{
	return m_blueDamage;
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

const sf::Texture * Resources::GetRandomAsteroidTexture()
{
	int meteor = rand() % 3;
	switch (meteor)
	{
	case 0:
		return &m_asteroid1;
	case 1:
		return &m_asteroid2;
	default:
		return &m_asteroid3;
	}
}

const sf::Font & Resources::GetFont()
{
	return m_font;
}
