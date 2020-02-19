#include "Light.h"

Light::Light(glm::vec3 pos, glm::vec3 color)
	:
	 m_vecPos(pos)
	,m_vecColor(color)
{
}

void Light::setPos(glm::vec3 x)
{
	m_vecPos = x;
}

void Light::setColor(glm::vec3 x)
{
	m_vecColor = x;
}

glm::vec3 Light::getPos()
{
	return m_vecPos;
}

glm::vec3 Light::getColor()
{
	return m_vecColor;
}

glm::vec3* Light::ptrPos()
{
	return &m_vecPos;
}

glm::vec3* Light::ptrColor()
{
	return &m_vecColor;
}
