#pragma once
#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "IObject.h"
#include "Laser.h"
#include "Constants.h"
#include <vector>

class CShooter :
	public IObject
{
public:
	CShooter(sf::Vector2f position, std::vector<CLaser *> & lasers);

	void Update(float deltaTime) override;
	void Hit(int damage);

	int GetHealth() const;
	sf::Vector2f GetPosition() const override;
	sf::RectangleShape & GetShape() override;

	void SetPosition(sf::Vector2f position);
private:
	void Move(float deltaTime);
	void Shoot();

	std::vector<CLaser *> & m_lasers;
	float m_reloadTime = SHOOTER_RELOAD;
	int m_health = SHOOTER_HEALTH;
	sf::RectangleShape m_shape;
};

