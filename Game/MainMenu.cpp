#include "MainMenu.h"
#include "Resources.h"
#include "Constants.h"

using namespace sf;

CMainMenu::CMainMenu(RenderWindow & window)
	: m_window(window)
{
	m_background = new Sprite;
	m_background->setTexture(Resources::GetBackgroundTexture());

	Vector2f position;
	m_newGameButton = new CTextButton;
	m_newGameButton->SetCharacterSize(72);
	m_newGameButton->SetFillColor(Color::White);
	m_newGameButton->SetString(L"New Game");
	position.x = WINDOW_WIDTH / 2 - m_newGameButton->GetWidth() / 2;
	position.y = WINDOW_HEIGHT / 2 - m_newGameButton->GetHeight();
	m_newGameButton->SetPosition(position);

	m_exitButton = new CTextButton;
	m_exitButton->SetCharacterSize(72);
	m_exitButton->SetFillColor(Color::White);
	m_exitButton->SetString(L"Exit");
	position.x = WINDOW_WIDTH / 2 - m_exitButton->GetWidth() / 2;
	position.y = m_newGameButton->GetBottomBound() + TEXT_MARGIN;
	m_exitButton->SetPosition(position);
}


CMainMenu::~CMainMenu()
{
	delete m_newGameButton;
	delete m_exitButton;
	delete m_background;
}

void CMainMenu::Draw() const
{
	m_window.clear(Color::White);
	m_window.draw(*m_background);
	m_window.draw(m_newGameButton->GetShape());
	m_window.draw(m_exitButton->GetShape());
	m_window.display();
}

void CMainMenu::Update()
{
	CheckEvents();
	UpdateButtons();
}

Result const * CMainMenu::GetResult() const
{
	return &m_result;
}

void CMainMenu::CheckEvents()
{
	Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case Event::Closed:
			m_window.close();
			break;
		case Event::MouseButtonReleased:
			CheckMouseClick(event.mouseButton.x, event.mouseButton.y);
			break;
		}
	}
}

void CMainMenu::CheckMouseClick(int x, int y)
{
	FloatRect mouse(static_cast<float>(x), static_cast<float>(y), 1, 1);
	if (m_newGameButton->IsHovered(Mouse::getPosition()))
	{
		m_result.code = ResultCode::NEW_GAME;
		m_result.data = 1;
		return;
	}
	if (m_exitButton->IsHovered(Mouse::getPosition()))
	{
		m_result.code = ResultCode::QUIT_GAME;
		return;
	}
}

void CMainMenu::UpdateButtons()
{
	if (m_newGameButton->IsHovered(Mouse::getPosition()))
	{
		m_newGameButton->Highlight();
	}
	else
	{
		m_newGameButton->Unhighlight();
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
