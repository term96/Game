#include "Level.h"
#include <Windows.h>
#include <math.h>
#include "Resources.h"

using namespace std;
using namespace sf;

CLevel::CLevel(RenderWindow & window)
	:m_player(new CPlayer(Vector2f(WINDOW_WIDTH / 2 - PLAYER_WIDTH / 2, PLAYER_START_HEIGHT), m_lasers))
	,m_clock()
	,m_window(window)
{
	m_lastFrameTime = m_clock.getElapsedTime().asMilliseconds() / 1000.f;

	InitTexts();
	InitButtons();

	m_background.setTexture(Resources::GetBackgroundTexture());
	m_background.setPosition(0.f, static_cast<float>(-WINDOW_HEIGHT));
}

void CLevel::InitTexts()
{
	m_healthText = new CText;
	m_healthText->SetString(L"HP: " + to_string(m_player->GetHealth()));
	m_healthText->SetPosition(Vector2f(0, 0));

	m_scoreText = new CText;
	m_scoreText->SetString(L"Score: " + to_string(m_score));
	m_scoreText->SetPosition(Vector2f(0, m_healthText->GetBottomBound() + TEXT_MARGIN));

	m_targetText = new CText;
	m_targetText->SetString(L"Kills: " + to_string(m_kills) + '/' + to_string(TARGET));
	m_targetText->SetPosition(Vector2f(0, m_scoreText->GetBottomBound() + TEXT_MARGIN));
}

void CLevel::InitButtons()
{
	Vector2f position;
	m_continueButton = new CTextButton;
	m_continueButton->SetString(L"Continue");
	m_continueButton->SetCharacterSize(72);
	position.x = WINDOW_WIDTH / 2 - m_continueButton->GetWidth() / 2;
	position.y = WINDOW_HEIGHT / 2 - m_continueButton->GetHeight();
	m_continueButton->SetPosition(position);

	m_exitButton = new CTextButton;
	m_exitButton->SetString(L"Main menu");
	m_exitButton->SetCharacterSize(72);
	position.x = WINDOW_WIDTH / 2 - m_exitButton->GetWidth() / 2;
	position.y = m_continueButton->GetBottomBound() + TEXT_MARGIN;
	m_exitButton->SetPosition(position);
}

void CLevel::UpdateBackground(float deltaTime)
{
	m_background.move(0.f, BACKGROUND_SPEED * deltaTime * m_slowMultiplier);
	if (m_background.getPosition().y >= 0)
	{
		m_background.setPosition(0.f, static_cast<float>(-WINDOW_HEIGHT));
	}
}

void CLevel::Draw() const
{
	m_window.clear(Color::White);
	m_window.setMouseCursorVisible(false);
	m_window.draw(m_background);

	if (!isStopped)
	{
		for (auto laser : m_lasers)
		{
			m_window.draw(laser->GetShape());
		}
		for (auto shooter : m_shooters)
		{
			m_window.draw(shooter->GetShape());
		}
		for (auto asteroid : m_asteroids)
		{
			m_window.draw(asteroid->GetShape());
		}
		m_window.draw(m_player->GetShape());
		m_window.draw(m_healthText->GetShape());
		m_window.draw(m_targetText->GetShape());
		if (m_bonus != nullptr)
			m_window.draw(m_bonus->GetShape());

		for (auto animation : m_animations)
		{
			m_window.draw(animation->GetShape());
		}
	}
	else
	{
		m_window.draw(m_gameEndText->GetShape());
	}

	if (isPaused || isStopped)
	{
		m_window.draw(m_continueButton->GetShape());
		m_window.draw(m_exitButton->GetShape());
		m_window.setMouseCursorVisible(true);
	}
	m_window.draw(m_scoreText->GetShape());

	m_window.display();
}

void CLevel::CheckEvents()
{
	Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case Event::Closed:
			m_window.close();
			break;
		case Event::KeyReleased:
			if (event.key.code == Keyboard::Escape)
			{
				PauseGame();
			}
			break;
		case Event::MouseButtonReleased:
			CheckMouseClick(event.mouseButton.x, event.mouseButton.y);
			break;
		}
	}
}

void CLevel::CheckMouseClick(int x, int y)
{
	FloatRect mouse(static_cast<float>(x), static_cast<float>(y), 1, 1);
	if (m_continueButton->IsHovered(Mouse::getPosition()))
	{
		if (isPaused)
		{
			PauseGame();
		}
		if (isStopped)
		{
			m_result.code = ResultCode::RESTART;
			m_result.data = 1;
		}
		return;
	}
	if (m_exitButton->IsHovered(Mouse::getPosition()))
	{
		m_result.code = ResultCode::RETURN;
		m_result.data = static_cast<int>(m_score);
		return;
	}
}

void CLevel::Update()
{
	float currentTime = m_clock.getElapsedTime().asMilliseconds() / 1000.f;
	float deltaTime = currentTime - m_lastFrameTime;
	m_lastFrameTime = currentTime;

	CheckEvents();

	if (!isPaused && !isStopped)
	{
		m_gameSpeed += (1.f / GAME_SPEED_UP_RATE) * deltaTime;
		m_score += SCORE_PER_SECOND * deltaTime * m_gameSpeed;

		m_bonusTime -= deltaTime;
		m_shooterTime -= deltaTime;
		m_asteroidTime -= deltaTime;
		Generate();

		if (m_slowMultiplier < 1.f)
		{
			m_slowMultiplier += (1.f / SLOW_TIME) * deltaTime;
			if (m_slowMultiplier > 1)
				m_slowMultiplier = 1.f;
		}

		UpdateBackground(deltaTime);
		UpdatePlayer(deltaTime);
		UpdateBonus(deltaTime);
		UpdateAsteroids(deltaTime);
		UpdateShooters(deltaTime);
		UpdateAnimations(deltaTime);
		UpdateLasers(deltaTime);
		UpdateTexts();
	}
	else
	{
		UpdateButtons();
	}
}

Result const * CLevel::GetResult() const
{
	return &m_result;
}

void CLevel::UpdateLasers(float deltaTime)
{
	for (size_t i = 0; i < m_lasers.size(); ++i)
	{
		auto laser = m_lasers.at(i);
		laser->Update(deltaTime * m_slowMultiplier);
		if (laser->GetShape().getGlobalBounds().top >= WINDOW_HEIGHT || laser->GetPosition().y <= -LASER_HEIGHT / 2)
		{
			delete laser;
			m_lasers.erase(m_lasers.begin() + i);
			continue;
		}

		if (CheckCollision(laser, m_player))
		{
			CAnimRect * animRect = CreateAnimation(laser->GetPosition(), AnimType::BLUE_DAMAGE);
			m_animations.push_back(animRect);

			m_player->Hit(SHOOT_DAMAGE);
			delete laser;
			m_lasers.erase(m_lasers.begin() + i);
			continue;
		}

		for (auto shooter : m_shooters)
		{
			if (CheckCollision(laser, shooter))
			{
				CAnimRect * animRect = CreateAnimation(laser->GetPosition(), AnimType::RED_DAMAGE);
				m_animations.push_back(animRect);

				shooter->Hit(SHOOT_DAMAGE);
				delete laser;
				m_lasers.erase(m_lasers.begin() + i);
				break;
			}
		}
	}
}

void CLevel::UpdatePlayer(float deltaTime)
{
	m_player->Update(deltaTime);
	if (m_player->GetHealth() <= 0 || m_kills >= 50)
	{
		StopGame();
	}
}

void CLevel::UpdateShooters(float deltaTime)
{
	for (size_t i = 0; i < m_shooters.size(); ++i)
	{
		auto shooter = m_shooters.at(i);
		shooter->Update(deltaTime * m_slowMultiplier);
		
		if (shooter->GetHealth() <= 0)
		{
			CAnimRect * animRect = CreateAnimation(shooter->GetPosition(), AnimType::SHOOTER_EXPLOSION);
			m_animations.push_back(animRect);

			delete shooter;
			m_shooters.erase(m_shooters.begin() + i);
			m_score += SCORE_FOR_KILL * m_gameSpeed;
			++m_kills;
			continue;
		}

		if (CheckCollision(shooter, m_player))
		{
			CAnimRect * animRect = CreateAnimation(shooter->GetPosition(), AnimType::SHOOTER_EXPLOSION);
			m_animations.push_back(animRect);

			delete shooter;
			m_shooters.erase(m_shooters.begin() + i);
			m_score += SCORE_FOR_KILL * m_gameSpeed;
			m_player->Hit(BUMP_DAMAGE);
			++m_kills;
			continue;
		}

		if (shooter->GetShape().getGlobalBounds().top >= WINDOW_HEIGHT)
		{
			delete shooter;
			m_shooters.erase(m_shooters.begin() + i);
		}
	}
}

void CLevel::UpdateAsteroids(float deltaTime)
{
	for (size_t i = 0; i < m_asteroids.size(); ++i)
	{
		auto asteroid = m_asteroids[i];
		asteroid->Update(deltaTime * m_slowMultiplier);

		if (CheckCollision(m_player, asteroid))
		{
			CAnimRect * animRect = CreateAnimation(asteroid->GetPosition(), AnimType::ASTEROID_EXPLOSION);
			m_animations.push_back(animRect);

			delete asteroid;
			m_asteroids.erase(m_asteroids.begin() + i);
			m_player->Hit(BUMP_DAMAGE);
			continue;
		}
		if (asteroid->GetShape().getGlobalBounds().top >= WINDOW_HEIGHT)
		{
			delete asteroid;
			m_asteroids.erase(m_asteroids.begin() + i);
		}
	}
}

void CLevel::UpdateBonus(float deltaTime)
{
	if (m_bonus == nullptr)
		return;

	m_bonus->Update(deltaTime);
	if (CheckCollision(m_player, m_bonus))
	{
		switch (m_bonus->GetType())
		{
		case HEALTH:
			m_player->GiveHealth(HEALTH_BONUS);
			break;
		case SLOW_MO:
			m_slowMultiplier = SLOW_MULTIPLIER;
			break;
		}

		delete m_bonus;
		m_bonus = nullptr;
		return;
	}
	if (m_bonus->GetPosition().y >= WINDOW_HEIGHT)
	{
		delete m_bonus;
		m_bonus = nullptr;
	}
}

void CLevel::UpdateAnimations(float deltaTime)
{
	for (size_t i = 0; i < m_animations.size(); ++i)
	{
		auto animation = m_animations[i];
		animation->Update(deltaTime * m_slowMultiplier);
		if (animation->IsStopped())
		{
			delete animation;
			m_animations.erase(m_animations.begin() + i);
		}
	}
}

void CLevel::UpdateTexts()
{
	m_healthText->SetString(L"HP: " + to_string(m_player->GetHealth()));
	m_scoreText->SetString(L"Score: " + to_string(static_cast<int>(m_score)));
	m_targetText->SetString(L"Kills: " + to_string(m_kills) + '/' + to_string(TARGET));
}

void CLevel::UpdateButtons()
{
	if (m_continueButton->IsHovered(Mouse::getPosition()))
	{
		m_continueButton->Highlight();
	}
	else
	{
		m_continueButton->Unhighlight();
	}
	if (m_exitButton->IsHovered(Mouse::getPosition()))
	{
		m_exitButton->Highlight();
	}
	else
	{
		m_exitButton->Unhighlight();
	}
}

CAnimRect * CLevel::CreateAnimation(Vector2f position, AnimType type)
{
	CAnimRect * animRect = nullptr; 
	switch (type)
	{
	case AnimType::ASTEROID_EXPLOSION:
		animRect = new CAnimRect(position, Resources::GetAsteroidExplosion(), EXPLOSION_ANIM_TIME);
		break;
	case AnimType::SHOOTER_EXPLOSION:
		animRect = new CAnimRect(position, Resources::GetShooterExplosion(), EXPLOSION_ANIM_TIME);
		break;
	case AnimType::RED_DAMAGE:
		animRect = new CAnimRect(position, Resources::GetRedDamage(), DAMAGE_ANIM_TIME);
		break;
	case AnimType::BLUE_DAMAGE:
		animRect = new CAnimRect(position, Resources::GetBlueDamage(), DAMAGE_ANIM_TIME);
		break;
	}
	
	return animRect;
}

void CLevel::Generate()
{
	float x;

	if (m_bonusTime <= 0)
	{
		x = static_cast<float>(WINDOW_WIDTH / 3 + rand() % static_cast<int>(WINDOW_WIDTH / 3 - BONUS_WIDTH));
		m_bonus = new CBonus(Vector2f(static_cast<float>(x), -BONUS_HEIGHT));
		m_bonusTime = BONUS_GENERATION;
	}

	if (m_asteroidTime <= 0)
	{
		x = static_cast<float>(rand() % static_cast<int>(WINDOW_WIDTH - MAX_ASTEROID_WIDTH));
		CAsteroid * asteroid = new CAsteroid(Vector2f(x, -MAX_ASTEROID_HEIGHT));
		m_asteroids.push_back(asteroid);
		m_asteroidTime = ASTEROID_GENERATION / m_slowMultiplier / m_gameSpeed;
	}

	if (m_shooterTime <= 0)
	{
		CShooter * shooter;
		x = static_cast<float>(rand() % static_cast<int>(WINDOW_WIDTH - SHOOTER_WIDTH * 6));

		for (int i = 0; i < 3; ++i)
		{
			shooter = new CShooter(Vector2f(x, -SHOOTER_HEIGHT), m_lasers);
			m_shooters.push_back(shooter);
			x += SHOOTER_WIDTH * 2;
		}

		m_shooterTime = SHOOTER_GENERATION / m_slowMultiplier;
	}
}

void CLevel::PauseGame()
{
	isPaused = !isPaused;
}

void CLevel::StopGame()
{
	isStopped = true;
	m_gameEndText = new CText;
	m_gameEndText->SetCharacterSize(72);
	
	if (m_player->GetHealth() <= 0)
	{
		m_gameEndText->SetString(L"You lose");
	}
	else
	{
		m_gameEndText->SetString(L"You won! (+50000)");
		m_score += 50000;
		m_scoreText->SetString(L"Score: " + to_string(static_cast<int>(m_score)));
	}

	Vector2f position;
	position.x = WINDOW_WIDTH / 2 - m_gameEndText->GetWidth() / 2;
	position.y = WINDOW_HEIGHT / 2 - m_gameEndText->GetHeight() * 2;
	m_gameEndText->SetPosition(position);

	m_scoreText->SetCharacterSize(72);
	position.x = WINDOW_WIDTH / 2 - m_scoreText->GetWidth() / 2;
	position.y = m_gameEndText->GetBottomBound() + TEXT_MARGIN;
	m_scoreText->SetPosition(position);

	m_continueButton->SetString(L"Try again");
	position.x = WINDOW_WIDTH / 2 - m_continueButton->GetWidth() / 2;
	position.y = m_scoreText->GetBottomBound() + m_continueButton->GetHeight() + TEXT_MARGIN;
	m_continueButton->SetPosition(position);

	position.x = WINDOW_WIDTH / 2 - m_exitButton->GetWidth() / 2;
	position.y = m_continueButton->GetBottomBound() + TEXT_MARGIN;
	m_exitButton->SetPosition(position);
}

bool CLevel::CheckCollision(IObject * first, IObject * second)
{
	static FloatRect firstCorrected;
	static FloatRect secondCorrected;

	FloatRect firstRect = first->GetShape().getGlobalBounds();
	firstCorrected.left = firstRect.left + firstRect.width * 0.05f;
	firstCorrected.top = firstRect.top + firstRect.height * 0.05f;
	firstCorrected.height = firstRect.height * 0.9f;
	firstCorrected.width = firstRect.width * 0.9f;

	FloatRect secondRect = second->GetShape().getGlobalBounds();
	secondCorrected.left = secondRect.left + secondRect.width * 0.05f;
	secondCorrected.top = secondRect.top + secondRect.height * 0.05f;
	secondCorrected.height = secondRect.height * 0.9f;
	secondCorrected.width = secondRect.width * 0.9f;

	return firstCorrected.intersects(secondCorrected);
}

CLevel::~CLevel()
{
	delete m_player;
	delete m_healthText;
	delete m_scoreText;
	delete m_targetText;
	delete m_continueButton;
	delete m_exitButton;

	if (m_gameEndText != nullptr)
		delete m_gameEndText;
	if (m_bonus != nullptr)
		delete m_bonus;

	for (auto laser : m_lasers)
		delete laser;
	for (auto shooter : m_shooters)
		delete shooter;
	for (auto asteroid : m_asteroids)
		delete asteroid;
}

/*
1. Тип снаряда, траектория, тип повреждений
2. Анимации взрыва, полёта, повреждений
3. Астероиды, которые крутятся, и летят не только вертикально
*/