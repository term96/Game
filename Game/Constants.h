#pragma once

// Размеры
static const int WINDOW_WIDTH = 1366;
static const int WINDOW_HEIGHT = 768;
static const float PLAYER_WIDTH = 112.f;
static const float PLAYER_HEIGHT = 75.f;
static const float BULLET_WIDTH = 14.f;
static const float BULLET_HEIGHT = 31.f;
static const float SHOOTER_WIDTH = 103.f;
static const float SHOOTER_HEIGHT = 84.f;
static const float BONUS_WIDTH = 64.f;
static const float BONUS_HEIGHT = 64.f;
static const float MAX_METEOR_WIDTH = 101.f;
static const float MAX_METEOR_HEIGHT = 96.f;

// Время генерации
static const float BONUS_GENERATION = 45.f;
static const float SHOOTER_GENERATION = 6.f;
static const float METEOR_GENERATION = 0.8f;

// Скорости
static const float BONUS_SPEED = WINDOW_HEIGHT / 5;
static const float SHOOTER_SPEED = WINDOW_HEIGHT / 6;
static const float PLAYER_SPEED = WINDOW_WIDTH / 2.5f;
static const float BACKGROUND_SPEED = WINDOW_HEIGHT / 20.f;
static const float METEOR_ROTATION = 90.f;
static const float METEOR_VERT_SPEED = WINDOW_HEIGHT / 2;
static const int METEOR_MAX_HOR_SPEED = 7;
static const int METEOR_MIN_HOR_SPEED = 4;

// Время перезарядки
static const float SHOOTER_RELOAD = 0.75f;
static const float PLAYER_RELOAD = 0.25f;

// Здоровье
static const int SHOOTER_HEALTH = 100;
static const int PLAYER_HEALTH = 1000;

// Цели миссии
static const int TARGET = 50;

// Бонусы
static const int HEALTH_BONUS = 250;
static const float SLOW_MULTIPLIER = 0.3f;
static const int SLOW_TIME = 25;

// Другое
static const float GAME_SPEED_UP_RATE = 120.f;
static const int BUMP_DAMAGE = 200;
static const int SHOOT_DAMAGE = 50;
static const int SCORE_PER_SECOND = 100;
static const int SCORE_FOR_KILL = 1000;
static const float TEXT_MARGIN = 10.f;
static const char GAME_NAME[] = "Space Shooter";