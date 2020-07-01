#include "Camera3rd.h"

Camera3rd::Camera3rd(Entity* toFollow)
	:
	Camera()
{
	m_Entity = toFollow;
	m_fZoom = 20;
	m_fAngleAround = 0;
	//processKeyboard(Movement::BACKWARD, 0.f);
	//processMouse({ 0.f,0.f }, true);
}

void Camera3rd::processScroll(float vec)
{
	calculateZoom(vec);
	processMouse({ 0.f,0.f }, true);
}

void Camera3rd::calculateZoom(float offset)
{
	m_fZoom -= offset * m_fSensitivity;
}

void Camera3rd::calculatePitch(glm::vec2& offset)
{
	m_fPitch += offset.y * m_fSensitivity;
}

void Camera3rd::calculateAngleAroundPlayer(glm::vec2& offset)
{
	m_fAngleAround -= offset.x * m_fSensitivity;
}

float Camera3rd::calculateHorizontalDistance()
{
	return m_fZoom * glm::cos(glm::radians(m_fPitch));
}

float Camera3rd::calculateVerticalDistance()
{
	return m_fZoom * glm::sin(glm::radians(m_fPitch));
}

void Camera3rd::calculatePosition(float h, float v)
{
	m_vecPos.x = m_Entity->getPos().x - h * sin(glm::radians(m_fAngleAround+m_Entity->getRotation().y));
	m_vecPos.y = m_Entity->getPos().y + v + m_fHeight;
	m_vecPos.z = m_Entity->getPos().z - h * cos(glm::radians(m_fAngleAround+m_Entity->getRotation().y));
}

void Camera3rd::setEntity(Entity* ent)
{
	m_Entity = ent;
	processMouse({ 0.f,0.f }, true);
}

glm::mat4 Camera3rd::getMatrix()
{
	glm::mat4 mat(1.f);
	mat = glm::rotate(mat, glm::radians(m_fPitch), glm::vec3(1.f, 0.f, 0.f));
	mat = glm::rotate(mat, glm::radians(m_fYaw), glm::vec3(0.f, 1.f, 0.f));
	mat = glm::translate(mat, -m_vecPos);

	return mat;
}

void Camera3rd::processKeyboard(Movement m, float dt)
{
	calculatePosition(calculateHorizontalDistance(), calculateVerticalDistance());
}

void Camera3rd::processMouse(glm::vec2 offsets, bool constrain)
{
	calculatePitch(offsets);
	calculateAngleAroundPlayer(offsets);
	m_fYaw = 180 - (m_Entity->getRotation().y + m_fAngleAround);
	calculatePosition(calculateHorizontalDistance(), calculateVerticalDistance());
}

void Camera3rd::reset()
{
	Camera::reset();
	m_fZoom = 10;
	m_fAngleAround = 0;
	m_fHeight = 2.f;
}
