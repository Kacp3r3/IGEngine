#pragma once


#include <glm/ext/matrix_transform.hpp>


#include "Graphics/Basics/Model.h"
#include "Graphics/Basics/Picture.h"


class Terrain
{
public:
	Terrain(int x, int z, Texture* txt, Picture* hmp);


public:
	float getHeight();
	Model* getModel();
	glm::mat4 getTransformationMatrix();
	Texture* getTexture();

private:
	Model* generateTerrain();
	float getHeight(int x, int z);

private:
	static const int m_nSize = 800;
	static const float m_MaxHeight;
	static const float m_MaxPixelValue;

private:
	float* m_Vertices;

private:
	glm::vec3 m_vecPos;
	glm::mat4 m_matTransformation;
private:
	Texture* m_pTexture;
	static Model* m_Model;
	Picture* m_Hmp;
};

