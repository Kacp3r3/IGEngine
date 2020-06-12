#pragma once


#include <glm/ext/matrix_transform.hpp>


#include "Graphics/Basics/Model.h"
#include "Graphics/Basics/Picture.h"


class Terrain
{
public:
	Terrain(int x, int z, Texture* txt, Picture* hmp);
	~Terrain();

public:
	Model* getModel();
	glm::mat4 getTransformationMatrix();
	Texture* getTexture();
	float getHeight(float worldX, float worldZ);
	float getHeight(glm::vec2 coords);
private:
	Model* generateTerrain();
	float getHeight(int x, int z);
	float barrycentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos);

public:
	static constexpr int m_nSize = 800;
	static constexpr float m_MaxHeight = 40.f;
	static constexpr float m_MaxPixelValue = 255.f + 255.f + 255.f;

private:
	std::vector<std::vector<float>> m_vecHeights;

private:
	glm::vec3 m_vecPos;
	glm::mat4 m_matTransformation;
	float m_nVertices;
private:
	Texture* m_pTexture;
	Model* m_Model;
	Picture* m_Hmp;
};

