#include "CameraFirst.h"


void CameraFirst::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_fYaw)) * cos(glm::radians(m_fPitch));
	front.y = sin(glm::radians(m_fPitch));
	front.z = sin(glm::radians(m_fYaw)) * cos(glm::radians(m_fPitch));
	m_vecFront = glm::normalize(front);
	m_vecRight = glm::normalize(glm::cross(m_vecFront, m_vecWorldUp));
	m_vecUp = glm::normalize(glm::cross(m_vecRight, m_vecFront));
}

void CameraFirst::reset()
{
	Camera::reset();
	m_vecFront = { 0.f, 0.f, -1.f };
	m_vecUp = { 0.f, 1.f, 0.f };
	m_vecWorldUp = { 0.f,1.f,0.f };
	m_fVelocity = 20.f;
	m_bFly = false;
	updateCameraVectors();
}

void CameraFirst::doubleSpeed()
{
	m_fVelocity *= 2;
}

void CameraFirst::normalSpeed()
{
	m_fVelocity /= 2.f;
}

CameraFirst::CameraFirst(glm::vec3 pos)
	:
	Camera()
	, m_vecFront(0.f, 0.f, -1.f)
	, m_vecUp(0.f, 1.f, 0.f)
	, m_bFly(true)
	, m_fVelocity(20.f)
	, m_vecWorldUp(0.f, 1.f, 0.f)
	, m_vecRight(0.f,0.f,0.f)
{
	if (!m_bFly)
		m_vecPos.y = m_fHeight;
	updateCameraVectors();
}

glm::mat4 CameraFirst::getMatrix()
{
	return glm::lookAt(m_vecPos, m_vecPos + m_vecFront, m_vecUp);
}

void CameraFirst::processKeyboard(Movement m, float dt)
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

	m_fSpeed = glm::length(glm::abs(m_vecPos - m_vecPosLast)) / dt;

}

void CameraFirst::processMouse(glm::vec2 offsets, bool constrain)
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

void CameraFirst::processScroll(float offsets)
{

}

float CameraFirst::getVelocity() const
{
	return m_fVelocity;
}

bool CameraFirst::getFly() const
{
	return m_bFly;
}

bool* CameraFirst::ptrFly()
{
	return &m_bFly;
}

float* CameraFirst::ptrVelocity()
{
	return &m_fVelocity;
}

void CameraFirst::setVelocity(float x)
{
	m_fVelocity = x;
}

void CameraFirst::setFly(bool x)
{
	m_bFly = x;
}

glm::vec3 CameraFirst::getFront()const
{
	return m_vecFront;
}

glm::vec3 CameraFirst::getUp()const
{
	return m_vecUp;
}