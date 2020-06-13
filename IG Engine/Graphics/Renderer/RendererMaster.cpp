#include "RendererMaster.h"
#include "Engine/Engine.h"

glm::vec3 RendererMaster::ambient = { 0.4f,0.4f,0.4f };
glm::vec3 RendererMaster::specular = { 0.7f,0.7f,0.7f };
glm::vec3 RendererMaster::diffuse = { 0.3f,0.3f,0.3f };
float RendererMaster::shininees=1.f;

RendererMaster::RendererMaster()
	:
	 //m_HUDShader("Graphics/Shaders/hud.vs", "Graphics/Shaders/hud.fs")
	m_EntityShader("Graphics/Shaders/entityv.glsl", "Graphics/Shaders/entityf.glsl")
	//,m_TerrainShader("Graphics/Shaders/terrain.vs", "Graphics/Shaders/terrain.fs")
	//,m_SkyBoxShader("Graphics/Shaders/sky.vs", "Graphics/Shaders/sky.fs")
{
	m_EntityShader.use();
	m_EntityShader.setInt("texture1", 0);
	//m_SkyBoxShader.use();
	//m_SkyBoxShader.setInt("texture1", 0);
	//m_TerrainShader.use();
	//m_TerrainShader.setInt("texture1", 0);
	resetProjection();

	glViewport(0, 0, Engine::SCR_WIDTH, Engine::SCR_HEIGHT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
}


void RendererMaster::clearScreen(float r, float g, float b)
{
	glClearColor(r,g,b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RendererMaster::renderScene(Light& sun, Camera& cam)
{
	clearScreen(0.f,0.f,1.f);
	
	/*glDepthMask(GL_FALSE);
	m_SkyBoxShader.use();
	m_SkyBoxShader.setMat4("projectionMatrix", m_matProjection);
	m_SkyBoxShader.setMat4("viewMatrix", cam.getMatrix());
	AssetManager::get().getModel("SkyBox")->bindVAO();
	glBindTexture(GL_TEXTURE_CUBE_MAP, AssetManager::get().getTexture("SkyBox")->getID());
	glDrawElements(GL_TRIANGLES, AssetManager::get().getModel("SkyBox")->getIndicesCount(), GL_UNSIGNED_INT, nullptr);
	glDepthMask(GL_TRUE);*/


	//Entity Stuff
	m_EntityShader.use();
	m_EntityShader.setVec3("lightPosition", sun.getPos());
	m_EntityShader.setVec3("lightColor", sun.getColor());
	m_EntityShader.setMat4("projectionMatrix", m_matProjection);
	m_EntityShader.setMat4("viewMatrix", cam.getMatrix());
	m_EntityShader.setVec3("material.ambient", Entity::m_Material.getAmbient());
	m_EntityShader.setVec3("material.diffuse", Entity::m_Material.getDiffuse());
	m_EntityShader.setVec3("material.specular", Entity::m_Material.getSpecular());
	m_EntityShader.setFloat("material.shininess", Entity::m_Material.getShininess());
	for (auto entity : m_vecEntities)
		m_Entity.render(entity,m_EntityShader);

	//m_HUD.render(m_HUDShader);

	//Terrain
	/*m_TerrainShader.use();
	m_TerrainShader.setMat4("projectionMatrix", m_matProjection);
	m_TerrainShader.setMat4("viewMatrix", cam.getMatrix());
	m_TerrainShader.setVec3("lightPosition", sun.getPos());
	m_TerrainShader.setVec3("lightColor", sun.getColor());
	m_TerrainShader.setVec3("material.ambient", ambient);
	m_TerrainShader.setVec3("material.diffuse", diffuse);
	m_TerrainShader.setVec3("material.specular", specular);
	m_TerrainShader.setFloat("material.shininess", shininees);
	for (auto terrain : m_vecTerrains)
		m_Terrain.render(terrain, m_TerrainShader);*/
}

void RendererMaster::updateProjection()
{
	m_matProjection = glm::perspective(glm::radians(m_fFov), Engine::SCR_WIDTH / static_cast<float>(Engine::SCR_HEIGHT), m_fNear, m_fFar);
}

void RendererMaster::resetProjection()
{
	m_fNear = 0.1f;
	m_fFar = 2500.f;
	m_fFov = 75.f;
	m_matProjection = glm::perspective(glm::radians(m_fFov), Engine::SCR_WIDTH / static_cast<float>(Engine::SCR_HEIGHT), m_fNear, m_fFar);
}

void RendererMaster::processScroll(float x)
{
	m_fFov -= x;

	if (m_fFov <= 1.0f)
		m_fFov = 1.0f;
	if (m_fFov >= 75.0f)
		m_fFov = 75.0f;
}

void RendererMaster::addEntity(Entity* ent)
{
	m_vecEntities.push_back(ent);
}

void RendererMaster::addTerrain(Terrain* t)
{
	m_vecTerrains.push_back(t);
}

glm::mat4 RendererMaster::getProjection() const
{
	return m_matProjection;
}

float RendererMaster::getFov() const
{
	return m_fFov;
}

float RendererMaster::getFar() const
{
	return m_fFar;
}

float RendererMaster::getNear() const
{
	return m_fNear;
}

float* RendererMaster::ptrNear()
{
	return &m_fNear;
}

float* RendererMaster::ptrFar()
{
	return &m_fFar;
}

float* RendererMaster::ptrFov()
{
	return &m_fFov;
}

void RendererMaster::setFov(float x)
{
	m_fFov = x;
}

void RendererMaster::setFar(float x)
{
	m_fFar = x;
}

void RendererMaster::setNear(float x)
{
	m_fNear = x;
}
