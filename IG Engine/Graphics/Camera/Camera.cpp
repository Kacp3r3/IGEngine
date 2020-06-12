#include "Camera.h"
#include "Engine/Engine.h"

Camera::Camera(glm::vec3 pos)
	:
	m_vecPos(pos)
	, m_fYaw(0.f)
	, m_fPitch(0.f)
	, m_fFov(75.f)
	, m_vecFront(0.f, 0.f, -1.f)
	, m_vecUp(0.f, 1.f, 0.f)
	, m_bFly(true)
	, m_fFar(400.f)
	, m_fNear(0.1f)
	, m_fHeight(1.5f)
	, m_fSensitivity(0.3f)
	, m_fVelocity(20.f)
	, m_vecWorldUp(0.f, 1.f, 0.f)
	, m_vecRight(0.f,0.f,0.f)
{
	if (!m_bFly)
		m_vecPos.y = m_fHeight;
	updateCameraVectors();
}

Camera::~Camera()
{
}

void Camera::processKeyboard(Movement m, float dt)
{
	m_vecPosLast = m_vecPos;
	float vel = m_fVelocity * dt;
	switch (m)
	{
	case Movement::FORWARD:
		m_vecPos += m_vecFront * vel;
		break;

	case Movement::BACKWARD:
		m_vecPos -= m_vecFront * vel;
		break;

	case Movement::LEFT:
		m_vecPos -= m_vecRight * vel;
		break;

	case Movement::RIGHT:
		m_vecPos += m_vecRight * vel;
		break;

	default:
		break;
	}
	if (!m_bFly)
		m_vecPos.y = m_fHeight;

	m_fSpeed = glm::length(glm::abs(m_vecPos - m_vecPosLast))/dt;
}

void Camera::processMouse(glm::vec2&& offsets, bool constrain)
{
	offsets *= m_fSensitivity;
	m_fYaw += offsets.x;
	m_fPitch -= offsets.y;

	if (constrain)
	{
		if (m_fPitch > 89.0f)
			m_fPitch = 89.0f;
		if (m_fPitch < -89.0f)
			m_fPitch = -89.0f;

		if (m_fYaw > 360.f)
			m_fYaw = 0.f;
		else if (m_fYaw < -360.f)
			m_fYaw = 0.f;
	}

	updateCameraVectors();
}

void Camera::setPos(const glm::vec3 pos)
{
	m_vecPos = pos;
}

void Camera::reset()
{
	m_fFov = 75.f;
	m_fYaw = 0.f;
	m_fPitch = 0.f;
	m_vecFront = { 0.f, 0.f, -1.f };
	m_vecUp = { 0.f, 1.f, 0.f };
	m_vecPos = { 400.f,m_fHeight,400.f };
	m_vecWorldUp = { 0.f,1.f,0.f };
	m_fNear = 0.1f;
	m_fFar = 2400.f;
	m_fVelocity = 20.f;
	m_fSensitivity = 0.3f;
	m_fHeight = 4.f;
	m_bFly = false;
	updateCameraVectors();
}

void Camera::doubleSpeed()
{
	m_fVelocity *= 2;
}

void Camera::normalSpeed()
{
	m_fVelocity /= 2.f;
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_fYaw)) * cos(glm::radians(m_fPitch));
	front.y = sin(glm::radians(m_fPitch));
	front.z = sin(glm::radians(m_fYaw)) * cos(glm::radians(m_fPitch));
	m_vecFront = glm::normalize(front);
	m_vecRight = glm::normalize(glm::cross(m_vecFront, m_vecWorldUp));
	m_vecUp = glm::normalize(glm::cross(m_vecRight, m_vecFront));
}

void Camera::updatePos()
{
	if (!m_bFly) m_vecPos.y = m_fHeight;
}



glm::vec3 Camera::getPos() const
{
	return m_vecPos;
}

glm::mat4 Camera::getMatrix()
{
	return glm::lookAt(m_vecPos, m_vecPos + m_vecFront, m_vecUp);
}

glm::vec3 Camera::getFront()const
{
	return m_vecFront;
}

glm::vec3 Camera::getUp()const
{
	return m_vecUp;
}

float Camera::getYaw()const
{
	return m_fYaw;
}

float Camera::getPitch()const
{
	return m_fPitch;
}



float Camera::getVelocity() const
{
	return m_fVelocity;
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

bool Camera::getFly() const
{
	return m_bFly;
}

bool* Camera::ptrFly()
{
	return &m_bFly;
}

float* Camera::ptrHeight()
{
	return &m_fHeight;
}



float* Camera::ptrVelocity()
{
	return &m_fVelocity;
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


void Camera::setVelocity(float x)
{
	m_fVelocity = x;
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

void Camera::setFly(bool x)
{
	m_bFly = x;
}
