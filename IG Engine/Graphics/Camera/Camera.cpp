#include "Camera.h"
#include "Engine/Engine.h"

Camera::Camera()
	:
	  m_fYaw(0.f)
	, m_fPitch(30.f)
	, m_fSpeed(0.f)
	, m_vecPos( 0.f,0.f,0.f )
	, m_vecPosLast(0.f,0.f,0.f)
	, m_fSensitivity(0.3f)	
	, m_fHeight(2.f)
{}

Camera::~Camera()
{
}

void Camera::processKeyboard(Movement m, float dt)
{
	}

void Camera::processMouse(glm::vec2 offsets, bool constrain)
{
	
}

void Camera::processScroll(float offsets)
{
}

void Camera::setPos(const glm::vec3 pos)
{
	m_vecPos = pos;
}

void Camera::reset()
{
	m_fYaw = 0.f;
	m_fPitch = 30.f;
	m_fHeight = 2.f;
	m_fSensitivity = 0.3f;
	m_vecPos = { 0.f,m_fHeight,0.f };
}




glm::vec3 Camera::getPos() const
{
	return m_vecPos;
}


float Camera::getYaw()const
{
	return m_fYaw;
}

float Camera::getPitch()const
{
	return m_fPitch;
}





float Camera::getSensitivity() const
{
	return m_fSensitivity;
}

float Camera::getHeight() const
{
	return m_fHeight;
}

float Camera::getSpeed()const
{
	return m_fSpeed;
}


float* Camera::ptrHeight()
{
	return &m_fHeight;
}





float* Camera::ptrSensitivity()
{
	return &m_fSensitivity;
}

float* Camera::ptrPitch()
{
	return &m_fPitch;
}

float* Camera::ptrYaw()
{
	return &m_fYaw;
}




void Camera::setSensitivity(float x)
{
	m_fSensitivity = x;
}

void Camera::setHeight(float x)
{
	m_fHeight = x;
}

void Camera::setPitch(float x)
{
	m_fPitch = x;
}

void Camera::setYaw(float x)
{
	m_fYaw = x;
}

void Camera::setSpeed(float x)
{
	m_fSpeed = x;
}

