#pragma once


#include <glad/glad.h>


#include "Graphics/Entities/Entity.h"
#include "Graphics/Shaders/Shader.h"


class EntityRenderer
{
public:
	EntityRenderer()=default;

public:
	void render(Entity* e, Shader& s);
};

