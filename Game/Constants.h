#pragma once

// Размеры
static const int WINDOW_WIDTH = 1366;
static const int WINDOW_HEIGHT = 768;
static const float PLAYER_WIDTH = 83.f;
static const float PLAYER_HEIGHT = 100.f;
static const float LASER_WIDTH = 14.f;
static const float LASER_HEIGHT = 26.f;
static const float SHOOTER_WIDTH = 112.f;
static const float SHOOTER_HEIGHT = 120.f;
static const float BONUS_WIDTH = 64.f;
static const float BONUS_HEIGHT = 64.f;
static const float MAX_ASTEROID_WIDTH = 122.f;
static const float MAX_ASTEROID_HEIGHT = 100.f;

// Время генерации
static const float BONUS_GENERATION = 30.f;
static const float SHOOTER_GENERATION = 6.f;
static const float ASTEROID_GENERATION = 1.25f;

// Скорости
static const float BONUS_SPEED = WINDOW_HEIGHT / 5;
static const float LASER_SPEED = 600.f;
static const float SHOOTER_SPEED = WINDOW_HEIGHT / 6;
static const float PLAYER_SPEED = WINDOW_WIDTH / 2.5f;
static const float BACKGROUND_SPEED = WINDOW_HEIGHT / 20.f;
static const float ASTEROID_VERT_SPEED = WINDOW_HEIGHT / 2;
static const int ASTEROID_MAX_HOR_TIME = 9;
static const int ASTEROID_MIN_HOR_TIME = 5;

// Повороты
static const float ASTEROID_ROTATION = 90.f;
static const float PLAYER_ROTATION = 10.f;

// Время перезарядки
static const float SHOOTER_RELOAD = 0.75f;
static const float PLAYER_RELOAD = 0.2f;

// Здоровье
static const int SHOOTER_HEALTH = 150;
static const int PLAYER_HEALTH = 1000;

// Цели миссии
static const int TARGET = 50;

// Бонусы
static const int HEALTH_BONUS = 250;
static const float SLOW_MULTIPLIER = 0.3f;
static const int SLOW_TIME = 25;

// Анимации
static const float PLAYER_ANIM_TIME = 0.75f;
static const float SHOOTER_ANIM_TIME = 0.75f;
static const float EXPLOSION_ANIM_TIME = 0.625f;
static const float DAMAGE_ANIM_TIME = 0.4f;

// Время всплывающего текста
static const float TARGET_HINT_TIME = 2.f;
static const float BONUS_HINT_TIME = 1.f;

// Другое
static const float PLAYER_START_HEIGHT = WINDOW_HEIGHT - PLAYER_HEIGHT - 20;
static const float GAME_SPEED_UP_RATE = 120.f;
static const int BUMP_DAMAGE = 200;
static const int SHOOT_DAMAGE = 50;
static const int SCORE_PER_SECOND = 100;
static const int SCORE_FOR_KILL = 1000;
static const float TEXT_MARGIN = 10.f;
static const char GAME_NAME[] = "Space Shooter";