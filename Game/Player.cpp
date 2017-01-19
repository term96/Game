#include "Player.h"
#include "Resources.h"

using namespace std;
using namespace sf;

CPlayer::CPlayer(Vector2f position, vector<CLaser *> & lasers)
	:m_lasers(lasers)
{
	m_shape.setSize(Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT));
	m_shape.setPosition(position);
	m_shape.setTexture(Resources::GetPlayerTexture());
}

void CPlayer::Update(float deltaTime)
{
	m_reloadTime -= deltaTime;
	if (Keyboard::isKeyPressed(sf::Keyboard::D) || Keyboard::isKeyPressed(sf::Keyboard::Right))
		Move(1, deltaTime);
	else if (Keyboard::isKeyPressed(sf::Keyboard::A) || Keyboard::isKeyPressed(sf::Keyboard::Left))
		Move(-1, deltaTime);
	if (Keyboard::isKeyPressed(sf::Keyboard::Space))
		Shoot();
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

void CPlayer::Move(int direction, float deltaTime)
{
	float posX = m_shape.getPosition().x;
	float deltaX = direction * PLAYER_SPEED * deltaTime;
	if (posX + deltaX <= 0 || posX + PLAYER_WIDTH + deltaX >= WINDOW_WIDTH)
		return;

	m_shape.move(deltaX, 0.f);
}

void CPlayer::Shoot()
{
	if (m_reloadTime > 0)
		return;

	Vector2f position = m_shape.getPosition();
	position.x += PLAYER_WIDTH / 2 - BULLET_WIDTH / 2;
	position.y -= 2.f + BULLET_HEIGHT;

	CLaser * laser = new CLaser(position, LaserDirection::UP);
	m_lasers.push_back(laser);

	m_reloadTime = PLAYER_RELOAD;
}