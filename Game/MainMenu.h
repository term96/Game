#pragma once
#include "IScene.h"
#include "TextButton.h"
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"

class CMainMenu
	: public IScene
{
public:
	CMainMenu(sf::RenderWindow & window);
	~CMainMenu();

	void Draw() const override;
	void Update() override;
	Result const * GetResult() const override;

	void CheckEvents();
	void CheckMouseClick(int x, int y);

private:
	void UpdateButtons();

	Result m_result;
	CTextButton * m_newGameButton;
	CTextButton * m_exitButton;
	sf::Sprite * m_background;
	sf::RenderWindow & m_window;
};

