#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Graphics/Resources/Texture.h"
#include "Graphics/Resources/Model.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/Shaders/Shader.h"
class CameraHUD
{
public:
	CameraHUD(Model* m, Texture* cur, Shader& s);

	void drawHUD(Shader& s,Renderer& gfx);
private:
	glm::mat4 m_matOrtho;
	Model* m_Croshair;
};

