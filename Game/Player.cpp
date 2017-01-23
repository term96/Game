#include "Player.h"
#include "Resources.h"

using namespace std;
using namespace sf;

CPlayer::CPlayer(Vector2f position, vector<CLaser *> & lasers)
	:m_lasers(lasers)
	,m_animation(Resources::GetPlayerAnimation(), PLAYER_ANIM_TIME, true)
{
	m_shape.setSize(Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT));
	m_shape.setOrigin(Vector2f(PLAYER_WIDTH / 2, PLAYER_HEIGHT / 2));
	m_shape.setPosition(position.x + PLAYER_WIDTH / 2, position.y + PLAYER_HEIGHT / 2);
}

void CPlayer::Update(float deltaTime)
{
	static int directionX;
	static int directionY;

	m_reloadTime -= deltaTime;
	if (Keyboard::isKeyPressed(sf::Keyboard::Space))
		Shoot();

	directionX = 0;
	directionY = 0;
	if (Keyboard::isKeyPressed(sf::Keyboard::D) || Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		directionX = 1;
	}
	else if (Keyboard::isKeyPressed(sf::Keyboard::A) || Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		directionX = -1;
	}
	if (Keyboard::isKeyPressed(sf::Keyboard::W) || Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		directionY = -1;
	}
	else if (Keyboard::isKeyPressed(sf::Keyboard::S) || Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		directionY = 1;
	}
	Move(directionX, directionY, deltaTime);
	m_animation.Update(deltaTime);
	m_shape.setTexture(m_animation.GetTexture());
}

void CPlayer::Hit(int damage)
{
	m_health -= damage;
}

int CPlayer::GetHealth() const
{
	return m_health;
}

sf::Vector2f CPlayer::GetPosition() const
{
	return m_shape.getPosition();
}

sf::RectangleShape & CPlayer::GetShape()
{
	return m_shape;
}

void CPlayer::GiveHealth(int health)
{
	m_health += health;
	if (m_health > PLAYER_HEALTH)
	{
		m_health = PLAYER_HEALTH;
	}
}

void CPlayer::SetPosition(Vector2f position)
{
	m_shape.setPosition(position);
}

void CPlayer::Move(int directionX, int directionY, float deltaTime)
{
	float posX = m_shape.getGlobalBounds().left;
	float deltaX = directionX * PLAYER_SPEED * deltaTime;
	if (posX + deltaX <= 0 || posX + PLAYER_WIDTH + deltaX >= WINDOW_WIDTH)
	{
		deltaX = 0;
	}
	float posY = m_shape.getGlobalBounds().top;
	float deltaY = directionY * PLAYER_SPEED * deltaTime;
	if (posY + deltaY <= 0 || posY + PLAYER_HEIGHT + deltaY >= WINDOW_HEIGHT)
	{
		deltaY = 0;
	}

	m_shape.move(deltaX, deltaY);
	m_shape.setRotation(directionX * PLAYER_ROTATION);
}

void CPlayer::Shoot()
{
	if (m_reloadTime > 0)
		return;

	Vector2f position;
	position.x = m_shape.getPosition().x - LASER_WIDTH / 2;
	position.y = m_shape.getGlobalBounds().top - 20.f;

	CLaser * laser = new CLaser(position, LaserType::RED);
	m_lasers.push_back(laser);

	m_reloadTime = PLAYER_RELOAD;
}