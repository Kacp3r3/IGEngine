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


//================================================================
//= Rendering everything
//================================================================
class Renderer
{

//================================================================
//= Ctor, Dtor
//================================================================
public:
	Renderer();
	~Renderer() { };


//================================================================
//= Interface
//================================================================
	void renderClearFrame(float r, float g, float b);
	void renderTestFrame();
	void drawLetter(Vec2f pos, char letter, GLuint IdTexture, Vec2f scale, glm::vec4 color);
	void draw(Vec2f pos, Texture* texture);
	void refreshCameraSettings();
	void setTextureCoords(GLuint x);
	void setTextureCoords(Vec2i x);
	//void drawSelf(double x, double y, GLuint IdTexture, double scaleX = 0.0, double scaleY = 0.0, glm::vec4 color = glm::vec4(1.0));




//================================================================
//= Members
//================================================================
private:

	float fOffsetShader = 0.03125f;
	//Drawing values
	float m_fScaleFactorX;
	float m_fScaleFactorY;
	float m_fStartPosX;
	float m_fStartPosY;
	float m_fTranslateValueX;
	float m_fTranslateValueY;

	//Main renderShader
	Shader m_SpriteSheetShader;


	//Reference to camera
	std::unique_ptr<Camera> m_Camera;


	//Vbo vao ebo itp
	unsigned int VBO, VAO, EBO;

	//Dla mapy
	float vertices3[20] = {
		// positions          // textures coords
		1.0f,  1.0f, 0.0f,   0.03125f, 1.0f,  // top right
		1.0f, -1.0f, 0.0f,   0.03125f, 0.96875f,  // bottom right
		-1.0f, -1.0f, 0.0f,   0.0f, 0.96875f,  // bottom left
		-1.0f,  1.0f, 0.0f,   0.0f, 1.0f,  // top left 
	};

	float vertices[20] = {
	 0.5f,  0.5f, 0.0f,  0.03125f, 1.0f,  //  // top right
	 0.5f, -0.5f, 0.0f,  0.03125f, 0.96875f, // bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.96875f, // bottom left
	-0.5f,  0.5f, 0.0f,    0.0f, 1.0f,  // to // top left 
	};

	float vertices2[20] = {
		// positions          // textures coords
		1.0f,  1.0f, 0.0f,   0.0625f, 1.0f,  // top right
		1.0f, -1.0f, 0.0f,   0.0625f, 0.9375f,  // bottom right
		-1.0f, -1.0f, 0.0f,   0.0f, 0.9375f,  // bottom left
		-1.0f,  1.0f, 0.0f,   0.0f, 1.0f,  // top left 
	};

	//================================================================
	//= Facey
	//================================================================
	unsigned int indices[6] = {  // note that we start from 0!
	0, 1, 3,  // first Triangle
	1, 2, 3   // second Triangle
	};


	////Tymczasowo dla reszty ferajny
	//float vertices2[20] = {
	//	// positions          // textures coords
	//	1.0f,  1.0f, 0.0f,   1.0f, 1.0f,  // top right
	//	1.0f, -1.0f, 0.0f,   1.0f, 0.0f,  // bottom right
	//	-1.0f, -1.0f, 0.0f,   0.0f, 0.0f,  // bottom left
	//	-1.0f,  1.0f, 0.0f,   0.0f, 1.0f,  // top left 
	//};




	//float vertices[20] = {
	//	// positions          // textures coords
	//	0.5f,  0.5f, 0.0f,  
	//	0.5f, -0.5f, 0.0f,  
	//	-0.5f, -0.5f, 0.0f, 
	//	-0.5f,  0.5f, 0.0f,  
	//};

	
};
#endif