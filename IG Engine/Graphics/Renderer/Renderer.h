#ifndef RENDERER_H
#define RENDERER_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "Graphics/Resources/Model.h"


class Renderer
{
public:
	Renderer();
	~Renderer() { };


public:
	void renderClearFrame(float r, float g, float b);
	void drawModel(Model* m);
};
#endif