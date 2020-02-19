#include "Entity.h"

Entity::Entity(Model* model, Texture* txt)
	:
	m_Model(model)
	, m_pTexture(txt)
	, m_vecPos(0.f, 0.f, 0.f)
	, m_vecRotation(0.f, 0.f, 0.f)
	, m_fScale(1.f)
{
	if (m_pTexture == nullptr) m_Model->haveTexture(false);
	updateTransformMatrix();
}

Entity::~Entity()
{
}

void Entity::updatePos(glm::vec3 pos)
{
	m_vecPos += pos;
	updateTransformMatrix();
}

void Entity::updateRotation(glm::vec3 rot)
{
	m_vecRotation += rot;
	updateTransformMatrix();
}

void Entity::setScale(float x)
{
	m_fScale = x;
	updateTransformMatrix();
}

void Entity::setPos(glm::vec3 pos)
{
	m_vecPos = pos;
	updateTransformMatrix();
}

void Entity::setRotation(glm::vec3 rot)
{
	m_vecRotation = rot;
	updateTransformMatrix();
}

glm::mat4 Entity::getTransformationMatrix()
{
	return m_matTransform;
}

glm::vec3 Entity::getPos()
{
	return m_vecPos;
}

glm::vec3 Entity::getRotation()
{
	return m_vecRotation;
}

Model* Entity::getModel()
{
	m_Model->setTexture(m_pTexture);
	return m_Model;
}

void Entity::updateTransformMatrix()
{
	m_matTransform = glm::mat4(1.f);
	m_matTransform = glm::translate(m_matTransform, m_vecPos);
	m_matTransform = glm::rotate(m_matTransform, glm::radians(m_vecRotation.x), glm::vec3(1.f, 0.f, 0.f));
	m_matTransform = glm::rotate(m_matTransform, glm::radians(m_vecRotation.y), glm::vec3(0.f, 1.f, 0.f));
	m_matTransform = glm::rotate(m_matTransform, glm::radians(m_vecRotation.z), glm::vec3(0.f, 0.f, 1.f));
	m_matTransform = glm::scale(m_matTransform, glm::vec3(m_fScale, m_fScale, m_fScale));
}
