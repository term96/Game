#include "Shooter.h"
#include "Resources.h"

using namespace std;
using namespace sf;

CShooter::CShooter(Vector2f position, vector<CLaser *> & lasers)
	:m_lasers(lasers)
{
	m_shape.setSize(Vector2f(SHOOTER_WIDTH, SHOOTER_HEIGHT));
	m_shape.setPosition(position);
	m_shape.setTexture(Resources::GetShooterTexture());
}

void CShooter::Update(float deltaTime)
{
	m_reloadTime -= deltaTime;
	if (m_reloadTime <= 0)
		Shoot();
	Move(deltaTime);
}

void CShooter::Hit(int damage)
{
	m_health -= damage;
}

int CShooter::GetHealth() const
{
	return m_health;
}

sf::Vector2f CShooter::GetPosition() const
{
	return m_shape.getPosition();
}

sf::RectangleShape & CShooter::GetShape()
{
	return m_shape;
}

void CShooter::SetPosition(Vector2f position)
{
	m_shape.setPosition(position);
}

void CShooter::Move(float deltaTime)
{
	m_shape.move(0, SHOOTER_SPEED * deltaTime);
}

void CShooter::Shoot()
{
	Vector2f position = m_shape.getPosition();
	position.x += SHOOTER_WIDTH / 2 - BULLET_WIDTH / 2;
	position.y += SHOOTER_HEIGHT + 2.f;

	CLaser * laser = new CLaser(position, LaserDirection::DOWN);
	m_lasers.push_back(laser);

	m_reloadTime = SHOOTER_RELOAD;
}