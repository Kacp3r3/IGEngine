#include "Terrain.h"
#include "AssetManager/AssetManager.h"
Model* Terrain::m_Model = nullptr;
Terrain::Terrain(int x, int y, Texture* txt)
{
	m_vecPos = { m_nSize*(-x),0.,m_nSize * (-y) };
	m_pTexture = txt;
	m_matTransformation = glm::mat4(1.f);
	m_matTransformation = glm::translate(m_matTransformation, m_vecPos);
	if (m_Model == nullptr) m_Model = generateTerrain();
	//if (m_Model == nullptr) m_Model = AssetManager::get().getModel("Cube");
}

Model* Terrain::getModel()
{
	return m_Model;
}

glm::mat4 Terrain::getTransformationMatrix()
{
	return m_matTransformation;
}

Texture* Terrain::getTexture()
{
	return m_pTexture;
}

Model* Terrain::generateTerrain()
{

	int count = m_nVertex * m_nVertex;
	float* vertices = new float[count * 3];
	float* normals = new float[count * 3];
	float* textureCoords = new float[count * 2];
	int* indices = new int[6 * (m_nVertex - 1) * (m_nVertex - 1)];
	int vertexPointer = 0;
	for (int i = 0; i < m_nVertex; i++) {
		for (int j = 0; j < m_nVertex; j++) {
			vertices[vertexPointer * 3] = (float)j / ((float)m_nVertex - 1) * m_nSize;
			vertices[vertexPointer * 3 + 1] = 0;
			vertices[vertexPointer * 3 + 2] = (float)i / ((float)m_nVertex - 1) * m_nSize;
			normals[vertexPointer * 3] = 0;
			normals[vertexPointer * 3 + 1] = 1;
			normals[vertexPointer * 3 + 2] = 0;
			textureCoords[vertexPointer * 2] = (float)j / ((float)m_nVertex - 1);
			textureCoords[vertexPointer * 2 + 1] = (float)i / ((float)m_nVertex - 1);
			vertexPointer++;
		}
	}
	int pointer = 0;
	for (int gz = 0; gz < m_nVertex - 1; gz++) {
		for (int gx = 0; gx < m_nVertex - 1; gx++) {
			int topLeft = (gz * m_nVertex) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * m_nVertex) + gx;
			int bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}
	return new Model(Mesh(vertices, normals, count*3,textureCoords,count*2, indices, 6 * (m_nVertex - 1) * (m_nVertex - 1)));
	
}
