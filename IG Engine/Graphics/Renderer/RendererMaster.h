#ifndef RENDERER_H
#define RENDERER_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


#include "Graphics/Shaders/Shader.h"
#include "Graphics/Basics/Model.h"
#include "Graphics/Renderer/EntityRenderer.h"
#include "Graphics/Renderer/HUDRenderer.h"
#include "Graphics/Renderer/TerrainRenderer.h"
#include "Graphics/Light/Light.h"
#include "Graphics/Camera/Camera.h"
#include "World/Structures/Terrain.h"


class RendererMaster
{
public:
	RendererMaster();
	~RendererMaster() { };


public:
	void renderScene(Light& sun, Camera& cam);
	void updateProjection();
	void resetProjection();
	void processScroll(float x);
	void addEntity(Entity* ent);
	void addTerrain(Terrain* t);

private:
	void clearScreen(float r, float g, float b);
	//void drawModel(Model* m);


public:
	void setFov(float x);
	void setFar(float x);
	void setNear(float x);


public:
	glm::mat4 getProjection() const;
	float getFov() const;
	float getFar()const;
	float getNear()const;


public:
	float* ptrNear();
	float* ptrFar();
	float* ptrFov();


private:
	Shader m_EntityShader;
	//Shader m_TerrainShader;
	//Shader m_HUDShader;
	//Shader m_SkyBoxShader;

	
private:
	EntityRenderer m_Entity;
	TerrainRenderer m_Terrain;
	HUDRenderer m_HUD;


private:
	std::vector<Entity*> m_vecEntities;
	std::vector<Terrain*> m_vecTerrains;


private:
	glm::mat4 m_matProjection;
	glm::vec3 m_vecSkyColor;
	float m_fFar;
	float m_fNear;
	float m_fFov;

public:
	static glm::vec3 specular;
	static glm::vec3 ambient;
	static glm::vec3 diffuse;
	static float shininees;
};
#endif