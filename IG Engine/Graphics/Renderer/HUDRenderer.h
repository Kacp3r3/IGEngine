#pragma once


#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_transform.hpp>


#include "Graphics/Shaders/Shader.h"
#include "AssetManager/AssetManager.h"


class HUDRenderer
{
public:
	HUDRenderer();

public:
	void render(Shader& s);
private:
	glm::mat4 m_matOrtho;
	Model* m_Cursor;
};

