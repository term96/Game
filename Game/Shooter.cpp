#include "Shooter.h"
#include "Resources.h"

using namespace std;
using namespace sf;

CShooter::CShooter(Vector2f position, vector<CLaser *> & lasers)
	:m_lasers(lasers)
	,m_animation(Resources::GetShooterAnimation(), SHOOTER_ANIM_TIME, true)
{
	m_shape.setOrigin(SHOOTER_WIDTH / 2, SHOOTER_HEIGHT / 2);
	m_shape.setSize(Vector2f(SHOOTER_WIDTH, SHOOTER_HEIGHT));
	m_shape.setPosition(position.x + SHOOTER_WIDTH / 2, position.y + SHOOTER_HEIGHT / 2);
}

void CShooter::Update(float deltaTime)
{
	m_reloadTime -= deltaTime;
	if (m_reloadTime <= 0)
		Shoot();
	Move(deltaTime);
	m_animation.Update(deltaTime);
	m_shape.setTexture(m_animation.GetTexture());
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
	position.x = m_shape.getPosition().x - LASER_WIDTH / 2;
	position.y = m_shape.getGlobalBounds().top + SHOOTER_HEIGHT + 20.f;

	CLaser * laser = new CLaser(position, LaserType::BLUE);
	m_lasers.push_back(laser);

	m_reloadTime = SHOOTER_RELOAD;
}