#include "Animation.h"

using namespace std;
using namespace sf;

CAnimation::CAnimation(vector<Texture> const & textures, float animationTime, bool repeated)
	:m_textures(textures)
{
	m_frame = 0;
	m_time = 0;
	m_animationTime = animationTime;
	m_repeated = repeated;
}

const sf::Texture * CAnimation::GetTexture() const
{
	return &m_textures.at(m_frame);
}

void CAnimation::Update(float deltaTime)
{
	m_time += deltaTime;
	if (m_time >= m_animationTime)
	{
		m_time = 0;
		if (!m_repeated)
		{
			m_stopped = true;
		}
	}
	m_frame = static_cast<int>(m_time / (m_animationTime / m_textures.size()));
}

bool CAnimation::IsStopped() const
{
	return m_stopped;
}

int CAnimation::GetFrame() const
{
	return m_frame;
}
