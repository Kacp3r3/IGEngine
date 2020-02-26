#include "Terrain.h"
#include "AssetManager/AssetManager.h"
Model* Terrain::m_Model = nullptr;
const float Terrain::m_MaxPixelValue = 256.f+256.f+256.f;
const float Terrain::m_MaxHeight = 40.f;
Terrain::Terrain(int x, int z, Texture* txt, Picture* hmp)
{
	m_Vertices = nullptr;
	m_Hmp = hmp;
	m_vecPos = { x*m_nSize,0.,z * m_nSize };
	m_pTexture = txt;
	m_matTransformation = glm::mat4(1.f);
	m_matTransformation = glm::translate(m_matTransformation, m_vecPos);
	if (m_Model == nullptr) m_Model = generateTerrain();
	//if (m_Model == nullptr) m_Model = AssetManager::get().getModel("Cube");
}

float Terrain::getHeight()
{

	return 0.0f;
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
	int m_nVertex = m_Hmp->getWidth();
	int count = m_nVertex * m_nVertex;
	m_Vertices = new float[count * 3];
	float* vertices = m_Vertices;
	float* normals = new float[count * 3];
	float* textureCoords = new float[count * 2];
	int* indices = new int[6 * (m_nVertex - 1) * (m_nVertex - 1)];
	int vertexPointer = 0;
	for (int i = 0; i < m_nVertex; i++) {
		for (int j = 0; j < m_nVertex; j++) {
			vertices[vertexPointer * 3] = (float)j / ((float)m_nVertex - 1) * m_nSize;
			glm::vec4 pixel = m_Hmp->getPixel(j, i);
			float height = ((pixel.x + pixel.y + pixel.z) / (m_MaxPixelValue / 2.f) -1.f)*m_MaxHeight;
			vertices[vertexPointer * 3 + 1] = height;
			vertices[vertexPointer * 3 + 2] = (float)i / ((float)m_nVertex - 1) * m_nSize;
			
			textureCoords[vertexPointer * 2] = (float)j / ((float)m_nVertex - 1);
			textureCoords[vertexPointer * 2 + 1] = (float)i / ((float)m_nVertex - 1);
			vertexPointer++;
		}
	}
	vertexPointer = 0;
	for (int i = 0; i < m_nVertex; i++) {
		for (int j = 0; j < m_nVertex; j++) {
			glm::vec3 normal;
			normal.x = getHeight(j - 1, i) - getHeight(j + 1, i);
			normal.y = 2.f;
			normal.z = getHeight(j, i - 1) - getHeight(j, i + 1);
			normal = glm::normalize(normal);

			normals[vertexPointer * 3] = normal.x;
			normals[vertexPointer * 3 + 1] = normal.y;
			normals[vertexPointer * 3 + 2] = normal.z;
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

float Terrain::getHeight(int x, int z)
{
	if (x < 0 || z < 0 || x >= m_Hmp->getWidth() || z >= m_Hmp->getHeight()) return 0;
	return m_Vertices[(z*m_Hmp->getWidth()+x)*m_Hmp->getChannels()+1];
}
