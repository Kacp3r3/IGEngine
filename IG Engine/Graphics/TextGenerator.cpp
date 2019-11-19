#include "TextGenerator.h"

TextGenerator::TextGenerator(Vec2f start, Texture* t, GLuint width, GLuint height)
	:
	 m_vecfStartPos(start)
	,m_nWidth(width)
	,m_nHeight(height)
	,m_Texture(t)
{
}

void TextGenerator::drawText(std::unique_ptr<Renderer>& gfx)
{
	Vec2f tmp = m_vecfStartPos;
	GLuint xcount = 0, ycount = 0;
	for (auto& x : m_vecToShow)
	{
		for (auto& letter : x)
		{
			if (xcount < m_nWidth) xcount++;
			else
			{
				ycount++;
				tmp._y += m_fLetterSize;
				tmp._x = m_vecfStartPos._x;
				xcount = 0;
			}
			gfx->drawLetter(tmp, letter, m_Texture->getID(), { m_fLetterSize,m_fLetterSize }, { 1,1,1,1 });
			tmp._x += m_fLetterSize;
		}
		ycount++;
		tmp._y += m_fLetterSize;
		tmp._x = m_vecfStartPos._x;
		xcount = 0;
		if (ycount >= m_nHeight)
		{
			break;
		}
	}
}

void TextGenerator::setText(std::vector<std::string>& lines)
{
	m_vecToShow = lines;
}

bool TextGenerator::Update()
{
	if (m_vecToShow.size() >= m_nHeight)
	{
		for (size_t i = 0; i < m_vecToShow.size() - 1; ++i)
		{
			m_vecToShow[i] = m_vecToShow[i + 1];
		}
		m_vecToShow.pop_back();
	}
	return m_vecToShow.size() >= m_nHeight;
}
