#pragma once
#include "Graphics/Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Graphics/Renderer.h"
#include "Model.h"
#include "Graphics/Shaders/Shader.h"
class CameraHUD
{
public:
	CameraHUD(Texture* cur, Mesh* mesh);

	void drawHUD(Shader& s,Renderer& gfx);
private:
	glm::mat4 ortho;
	Model m_Croshair;
};

