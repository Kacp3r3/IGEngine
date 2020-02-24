#pragma once

#include "Graphics/Shaders/Shader.h"
#include "World/Structures/Terrain.h"

class TerrainRenderer
{
public:
	TerrainRenderer();
	
	
public:
	void render(Terrain* t, Shader& s);
};

