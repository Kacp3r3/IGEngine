#pragma once

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Graphics/Basics/Model.h"
#include "Graphics/Basics/Material.h"

class Entity
{
public:
	Entity(Model* model);
	~Entity();

public:
	virtual void processKeyboard(Movement m, float dt) {};

public:
	void updatePos(glm::vec3 pos);
	void updateRotation(glm::vec3 rot);
	void setScale(float x);
	void setPos(glm::vec3 pos);
	void setRotation(glm::vec3 rot);
	void setRotationY(float x);

public:
	glm::mat4 getTransformationMatrix();
	glm::vec3 getPos();
	glm::vec3 getRotation();
	Model* getModel();
	
private:
	void updateTransformMatrix();

protected:
	float m_fVelocity;
	float m_fRotationSpeed;
	float m_fCurrentVelocity;
	float m_fCurrentRotationSpeed;

protected:
	Model* m_Model;
	glm::vec3 m_vecPos;
	glm::vec3 m_vecRotation;
	glm::mat4 m_matTransform;
	float m_fScale;
};

