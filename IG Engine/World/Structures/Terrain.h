#pragma once
#include "Graphics/Resources/Model.h"
#include <glm/ext/matrix_transform.hpp>
class Terrain
{
public:
	Terrain(int x, int y, Texture* txt);


public:
	Model* getModel();
	glm::mat4 getTransformationMatrix();
	Texture* getTexture();

private:
	Model* generateTerrain();


private:
	const int m_nVertex = 128;
	const int m_nSize = 200;

private:
	glm::vec3 m_vecPos;
	glm::mat4 m_matTransformation;
private:
	Texture* m_pTexture;
	static Model* m_Model;
};

