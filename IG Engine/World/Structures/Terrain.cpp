#include "Terrain.h"
#include "AssetManager/AssetManager.h"
Terrain::Terrain(int x, int z, Texture* txt, Picture* hmp)
	:
	 m_vecHeights()
{
	m_Hmp = hmp;
	m_vecPos = { x*m_nSize,0.,z * m_nSize };
	m_pTexture = txt;
	m_matTransformation = glm::mat4(1.f);
	m_matTransformation = glm::translate(m_matTransformation, m_vecPos);
	m_Model = generateTerrain();
	//if (m_Model == nullptr) m_Model = AssetManager::get().getModel("Cube");
}

Terrain::~Terrain()
{
	delete m_Model;
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

float Terrain::getHeight(glm::vec2 coords)
{
	return getHeight(coords.x, coords.y);
}

float Terrain::getHeight(float worldX, float worldZ)
{
	if (worldX < 0.f || worldZ < 0.f) return m_MaxHeight + 1.f;
	float TerrainX = worldX - m_vecPos.x;
	float TerrainZ = worldZ - m_vecPos.z;

	if (TerrainX > 800.f || TerrainZ > 800.f)return m_MaxHeight + 1.f;

	float squaresize = m_nSize / (m_nVertices-1.f);
	int gridX = TerrainX / squaresize;
	int gridZ = TerrainZ / squaresize;

	if (gridX <0 || gridX > m_nVertices - 1 || gridZ < 0 || gridZ > m_nVertices - 1)
		return m_MaxHeight + 1.f;

	float xCoord = TerrainX;
	while (xCoord > squaresize)
		xCoord -= squaresize;
	xCoord /= squaresize;
	float zCoord = TerrainZ;
	while (zCoord > squaresize)
		zCoord -= squaresize;
	zCoord /= squaresize;

	float answer;
	if (xCoord < (1 - zCoord)) {
		answer = barrycentric({ 0, m_vecHeights[gridZ][gridX] , 0 }, { 1,
				m_vecHeights[gridZ][gridX + 1], 0 }, { 0,
					m_vecHeights[gridZ + 1][gridX], 1 }, { xCoord, zCoord });
	}
	else {
		answer = barrycentric({ 1, m_vecHeights[gridZ][gridX + 1], 0 }, { 1,
				m_vecHeights[gridZ + 1][gridX + 1], 1 }, { 0,
					m_vecHeights[gridZ + 1][gridX], 1 }, { xCoord, zCoord });
	}

	return answer;
}

Model* Terrain::generateTerrain()
{
	int m_nVertex = m_Hmp->getWidth();
	m_nVertices = m_nVertex;
	int count = m_nVertex * m_nVertex;
	//m_Vertices = new float[count * 3];
	float* vertices = new float[count*3];
	float* normals = new float[count * 3];
	float* textureCoords = new float[count * 2];
	int* indices = new int[6 * (m_nVertex - 1) * (m_nVertex - 1)];
	int vertexPointer = 0;
	for (int i = 0; i < m_nVertex; i++) {
		m_vecHeights.emplace_back();
		for (int j = 0; j < m_nVertex; j++) {
			vertices[vertexPointer * 3] = (float)j / ((float)m_nVertex - 1) * m_nSize;
			glm::vec4 pixel = m_Hmp->getPixel(j, i);
			float height = ((pixel.x + pixel.y + pixel.z) / (m_MaxPixelValue / 2.f) -1.f)*m_MaxHeight;
			vertices[vertexPointer * 3 + 1] = height;
			m_vecHeights[i].push_back(height);
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
	return new Model(Mesh(vertices, normals, count,textureCoords,count*2, indices, 6 * (m_nVertex - 1) * (m_nVertex - 1),m_pTexture));
	//return nullptr;
}

float Terrain::getHeight(int x, int z)
{
	if (x < 0 || z < 0 || x >= m_Hmp->getWidth() || z >= m_Hmp->getHeight()) return 0;
	return m_vecHeights[z][x];
}

float Terrain::barrycentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos)
{
		float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
		float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
		float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
		float l3 = 1.0f - l1 - l2;
		return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}
