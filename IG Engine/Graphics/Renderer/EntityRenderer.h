#pragma once


#include <glad/glad.h>


#include "Entities/Entity.h"
#include "Graphics/Shaders/Shader.h"


class EntityRenderer
{
public:
	EntityRenderer()=default;

public:
	void render(Entity* e, Shader& s);
};

