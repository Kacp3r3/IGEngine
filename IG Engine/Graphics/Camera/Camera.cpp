#include "Camera.h"


Camera::Camera(glm::vec3 pos)
	:
	m_vecPos(pos)
	, m_yaw(0.f)
	, m_pitch(0.f)
	, m_fov(75.f)
	, m_vecFront(0.f, 0.f, -1.f)
	, m_vecUp(0.f, 1.f, 0.f)
	, m_bAllowFlight(false)
{
}

Camera::~Camera()
{
}

void Camera::updatePos(const glm::vec3 pos)
{
	m_vecPos += pos;
	if(!m_bAllowFlight)
		m_vecPos.y = m_CamHeight;
}

void Camera::setPos(const glm::vec3 pos)
{
	m_vecPos = pos;
}

void Camera::updateYaw(float x)
{
	m_yaw += x;
	if (m_yaw > 360.f)
		m_yaw = 0.f;
	else if (m_yaw < -360.f)
		m_yaw = 0.f;
}

void Camera::updatePitch(float x)
{
	m_pitch -= x;
	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;
}

void Camera::updateFov(float x)
{
	m_fov -= x;
}

void Camera::reset()
{
	m_fov = 75.f;
	m_yaw = -90.f;
	m_pitch = 0.f;
	m_vecFront = { 0.f, 0.f, -1.f };
	m_vecUp = { 0.f, 1.f, 0.f };
	m_vecPos = { 0.f,m_CamHeight,3.f };
}

float Camera::getFov()
{
	return m_fov;
}

glm::vec3 Camera::getPos()
{
	return m_vecPos;
}

glm::mat4 Camera::getView()
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	direction.y = sin(glm::radians(m_pitch));
	direction.z = sin(glm::radians(m_yaw)) *cos(glm::radians(m_pitch));
	m_vecFront = glm::normalize(direction);
	glm::mat4 view(1.f);
	view = glm::lookAt(m_vecPos, m_vecPos + m_vecFront, m_vecUp);
	return view;
}

glm::vec3 Camera::getFront()
{
	return m_vecFront;
}

glm::vec3 Camera::getUp()
{
	return m_vecUp;
}

float Camera::getYaw()
{
	return m_yaw;
}

float Camera::getPitch()
{
	return m_pitch;
}

bool* Camera::getFlight()
{
	return &m_bAllowFlight;
}

void Camera::setFov(float x)
{
	m_fov = x;
}



//void Camera::initCamera(const Vec2f& pos,GLuint mapw, GLuint maph, GLuint wscreen, GLuint hscreen)
//{
//	setFov(10);
//	m_nWidth = mapw;
//	m_nHeight = maph;
//	if (wscreen > hscreen)m_vecfFov._y = (hscreen / (float)wscreen) * m_vecfFov._y;
//	else m_vecfFov._x = (wscreen / (float)hscreen) * m_vecfFov._x;
//	m_vecfScaleFactor._x = 1.0f / m_vecfFov._x;
//	m_vecfScaleFactor._y = 1.0f / m_vecfFov._y;
//	float tmpx = -2 * m_vecfScaleFactor._x * (pos._x+0.5f - m_vecfFov._x / 2.0f);
//	float tmpy = 2 * m_vecfScaleFactor._y * (pos._y+0.5f - m_vecfFov._y / 2.0f);
//
//	if (tmpx < 0)m_vecfTranslateVector._x = tmpx;
//	else m_vecfTranslateVector._x = 0;
//
//	if (tmpy > 0) m_vecfTranslateVector._y = tmpy;
//	else m_vecfTranslateVector._y = 0;
//}

//void Camera::updateCamera(const Vec2f & pos)
//{
//	Vec2d center = { 0.5f,0.5f };
//	float tmpx = -2 * m_vecfScaleFactor._x * (pos._x + center._x - m_vecfFov._x / 2.0f);// -0.1;
//	float tmpy = 2 * m_vecfScaleFactor._y * (pos._y + center._y - m_vecfFov._y / 2.0f);//+0.025;
//	
//	bool right = pos._x+center._x-0.1f < float(m_nWidth) - (m_vecfFov._x / 2.0f);
//	bool bottom = pos._y+center._y + 0.025f < float(m_nHeight) - (m_vecfFov._y / 2.0f);
//
//	if (tmpx < 0 && right)m_vecfTranslateVector._x = tmpx;
//	else if (!right) m_vecfTranslateVector._x = -2 * m_vecfScaleFactor._x * (((float)m_nWidth - (m_vecfFov._x / 2.0f)) - m_vecfFov._x / 2.0f);
//	else m_vecfTranslateVector._x = 0;
//
//	if (tmpy > 0 && bottom) m_vecfTranslateVector._y = tmpy;
//	else if (!bottom) m_vecfTranslateVector._y = 2 * m_vecfScaleFactor._y * ((float)m_nHeight - (m_vecfFov._y / 2.0f) - m_vecfFov._y / 2.0f);
//	else m_vecfTranslateVector._y = 0;
//}

