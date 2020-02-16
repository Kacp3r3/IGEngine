#ifndef RENDERER_H
#define RENDERER_H

//================================================================
//= std Libs
//================================================================
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


//================================================================
//= My Libs
//================================================================
//#include "../AssetManager/AssetManager.h"
#include "../Utility/Enums.h"
#include "Shaders/Shader.h"
//#include "../Map/Map.h"
#include "../Utility/Vec2.h"
#include "Camera.h"
#include "Texture.h"
#include <memory>
#include "..\Model.h"

//================================================================
//= Rendering everything
//================================================================
class Renderer
{

//================================================================
//= Ctor, Dtor
//================================================================
public:
	Renderer(int w, int h);
	~Renderer() { };

//================================================================
//= Interface
//================================================================
	void renderClearFrame(float r, float g, float b);
	void renderTestFrame();
	void drawLine(GLuint& VAO, glm::vec3& translation);
	void drawModel(Model* m);
	void drawModel(Model* m, glm::mat4& rotation);
	void drawLine(float x1, float y1, float x2, float y2);
	//void drawSelf(double x, double y, GLuint IdTexture, double scaleX = 0.0, double scaleY = 0.0, glm::vec4 color = glm::vec4(1.0));

//================================================================
//= Members
//================================================================
private:
	//Main renderShader

	//Reference to camera
	std::unique_ptr<Camera> m_Camera;
	glm::mat4 proj;
	glm::mat4 view;

	GLuint VBO;
	GLuint VAO;
	GLuint EBO;

	float model[6] = { 0.f, 0.f, 0.f,
					   1.f, 1.f, 0.f };

	//================================================================
	//= Facey
	//================================================================
	unsigned int indices[2] = {  // note that we start from 0!
	0, 1   // second Triangle
	};
};
#endif