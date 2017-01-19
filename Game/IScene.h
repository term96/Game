#pragma once

#include "SFML\Window.hpp"
#include "Player.h"

enum ResultCode
{
	NULL_CODE, QUIT_GAME, RETURN, NEW_GAME, RESTART
};

struct Result
{
	ResultCode code = NULL_CODE;
	int data;
};

class IScene
{
public:
	virtual void Draw() const = 0;
	virtual void Update() = 0;
	virtual Result const * GetResult() const = 0;
	virtual ~IScene() = default;
};

