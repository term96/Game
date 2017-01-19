#include <SFML/Graphics.hpp>
#include "IScene.h"
#include "Level.h"
#include "Player.h"
#include "Constants.h"
#include "Resources.h"
#include "MainMenu.h"
#include <Windows.h>

using namespace std;
using namespace sf;

IScene * StartLevel(int level, RenderWindow & window)
{
	switch (level)
	{
	case 1:
	default:
		return new CLevel(window);
	}
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME, Style::Close | Style::Fullscreen);
	Resources::Init();
	srand(static_cast<unsigned int>(time(0)));

	IScene * level = new CMainMenu(window);
	Result const * result;
	int newLevel;

	while (window.isOpen())
	{
		level->Update();
		level->Draw();
		result = level->GetResult();
		switch (result->code)
		{
		case ResultCode::QUIT_GAME:
			window.close();
			break;
		case ResultCode::RETURN:
			delete level;
			level = new CMainMenu(window);
			break;
		case ResultCode::NEW_GAME:
		case ResultCode::RESTART:
			newLevel = result->code;
			delete level;
			level = StartLevel(newLevel, window);
			break;
		default:
			break;
		}
	}

	delete level;
	return 0;
}