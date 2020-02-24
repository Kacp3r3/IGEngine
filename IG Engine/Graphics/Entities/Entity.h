#pragma once


#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/ext/matrix_transform.hpp>


#include "Graphics/Resources/Model.h"
#include "Graphics/Resources/Material.h"


class Entity
{
public:
	Entity(Model* model, Texture* txt);
	~Entity();

public:
	void updatePos(glm::vec3 pos);
	void updateRotation(glm::vec3 rot);


public:
	void setScale(float x);
	void setPos(glm::vec3 pos);
	void setRotation(glm::vec3 rot);

public:
	glm::mat4 getTransformationMatrix();
	glm::vec3 getPos();
	glm::vec3 getRotation();
	Model* getModel();
	static Material m_Material;
	
private:
	void updateTransformMatrix();


private:
	float m_fScale;
	Model* m_Model;
	Texture* m_pTexture;
	glm::vec3 m_vecPos;
	glm::vec3 m_vecRotation;
	glm::mat4 m_matTransform;
};

