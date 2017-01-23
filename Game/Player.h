#pragma once

#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "IObject.h"
#include "Laser.h"
#include "Constants.h"
#include "Animation.h"
#include <vector>

class CPlayer : public IObject
{
public:
	CPlayer(sf::Vector2f position, std::vector<CLaser *> & bullets);

	void Update(float deltaTime) override;
	void Hit(int damage);

	int GetHealth() const;
	sf::Vector2f GetPosition() const override;
	sf::RectangleShape & GetShape() override;

	void GiveHealth(int health);

	void SetPosition(sf::Vector2f position);
private:
	void Move(int directionX, int directionY, float deltaTime);
	void Shoot();

	CAnimation m_animation;
	std::vector<CLaser *> & m_lasers;
	int m_health = PLAYER_HEALTH;
	float m_reloadTime = PLAYER_RELOAD;
	sf::RectangleShape m_shape;
};

