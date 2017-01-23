#pragma once
#include "SFML\Window.hpp"
#include "IScene.h"
#include "IObject.h"
#include "Player.h"
#include "Laser.h"
#include "Shooter.h"
#include "Text.h"
#include "Asteroid.h"
#include "Bonus.h"
#include "TextButton.h"
#include "AnimRect.h"
#include <vector>

enum AnimType
{
	ASTEROID_EXPLOSION, SHOOTER_EXPLOSION, BLUE_DAMAGE, RED_DAMAGE
};

class CLevel :
	public IScene
{
public:
	CLevel(sf::RenderWindow & window);
	~CLevel();

	static bool CheckCollision(IObject * first, IObject * second);

	void Draw() const override; 
	void Update() override;
	Result const * GetResult() const override;
private:
	void InitTexts();
	void InitButtons();

	void UpdateBackground(float deltaTime);
	void UpdateLasers(float deltaTime);
	void UpdatePlayer(float deltaTime);
	void UpdateShooters(float deltaTime);
	void UpdateAsteroids(float deltaTime);
	void UpdateBonus(float deltaTime);
	void UpdateAnimations(float deltaTime);
	void UpdateTexts();
	void UpdateButtons();

	void CreateAnimation(sf::Vector2f position, AnimType type);

	void Generate();

	void CheckEvents();
	void CheckMouseClick(int x, int y);

	void PauseGame();
	void StopGame();

	bool isPaused = false;
	bool isStopped = false;

	float m_lastFrameTime;
	float m_gameSpeed = 1.f;
	float m_score = 0;
	int m_kills = 0;

	float m_slowMultiplier = 1.f;

	float m_bonusTime = BONUS_GENERATION;
	float m_shooterTime = SHOOTER_GENERATION;
	float m_asteroidTime = ASTEROID_GENERATION;

	sf::RenderWindow & m_window;
	sf::Clock m_clock;
	Result m_result;

	std::vector<CLaser *> m_lasers;
	std::vector<CShooter *> m_shooters;
	std::vector<CAsteroid *> m_asteroids;
	std::vector<CAnimRect *> m_animations;
	CPlayer * m_player;
	CBonus * m_bonus = nullptr;

	CText * m_healthText;
	CText * m_scoreText;
	CText * m_targetText;
	CText * m_gameEndText = nullptr;

	CTextButton * m_continueButton;
	CTextButton * m_exitButton;

	sf::Sprite m_background;
	sf::Font font;
};

