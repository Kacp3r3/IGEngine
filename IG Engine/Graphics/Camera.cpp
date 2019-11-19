#include "Camera.h"



Camera::Camera()
{
	m_vecfFov._x = 0;
	m_vecfFov._y = 0;
	m_vecfTranslateVector._x = 0.0;
	m_vecfTranslateVector._y = 0.0;
	m_nHeight = 0;
	m_nWidth = 0;
}


Camera::Camera(GLuint width, GLuint height)
{
	m_vecfFov._x = (float)width;
	m_vecfFov._y = (float)height;
	m_vecfTranslateVector._x = 0.0;
	m_vecfTranslateVector._y = 0.0;
	m_nHeight = 0;
	m_nWidth = 0;
}

Camera::~Camera()
{
}

void Camera::setFov(float x)
{
	m_vecfFov = { x,x };
}

void Camera::initCamera(const Vec2f& pos,GLuint mapw, GLuint maph, GLuint wscreen, GLuint hscreen)
{
	setFov(10);
	m_nWidth = mapw;
	m_nHeight = maph;
	if (wscreen > hscreen)m_vecfFov._y = (hscreen / (float)wscreen) * m_vecfFov._y;
	else m_vecfFov._x = (wscreen / (float)hscreen) * m_vecfFov._x;
	m_vecfScaleFactor._x = 1.0f / m_vecfFov._x;
	m_vecfScaleFactor._y = 1.0f / m_vecfFov._y;
	float tmpx = -2 * m_vecfScaleFactor._x * (pos._x+0.5f - m_vecfFov._x / 2.0f);
	float tmpy = 2 * m_vecfScaleFactor._y * (pos._y+0.5f - m_vecfFov._y / 2.0f);

	if (tmpx < 0)m_vecfTranslateVector._x = tmpx;
	else m_vecfTranslateVector._x = 0;

	if (tmpy > 0) m_vecfTranslateVector._y = tmpy;
	else m_vecfTranslateVector._y = 0;
}

void Camera::updateCamera(const Vec2f & pos)
{
	Vec2d center = { 0.5f,0.5f };
	float tmpx = -2 * m_vecfScaleFactor._x * (pos._x + center._x - m_vecfFov._x / 2.0f);// -0.1;
	float tmpy = 2 * m_vecfScaleFactor._y * (pos._y + center._y - m_vecfFov._y / 2.0f);//+0.025;
	
	bool right = pos._x+center._x-0.1f < float(m_nWidth) - (m_vecfFov._x / 2.0f);
	bool bottom = pos._y+center._y + 0.025f < float(m_nHeight) - (m_vecfFov._y / 2.0f);

	if (tmpx < 0 && right)m_vecfTranslateVector._x = tmpx;
	else if (!right) m_vecfTranslateVector._x = -2 * m_vecfScaleFactor._x * (((float)m_nWidth - (m_vecfFov._x / 2.0f)) - m_vecfFov._x / 2.0f);
	else m_vecfTranslateVector._x = 0;

	if (tmpy > 0 && bottom) m_vecfTranslateVector._y = tmpy;
	else if (!bottom) m_vecfTranslateVector._y = 2 * m_vecfScaleFactor._y * ((float)m_nHeight - (m_vecfFov._y / 2.0f) - m_vecfFov._y / 2.0f);
	else m_vecfTranslateVector._y = 0;
}

