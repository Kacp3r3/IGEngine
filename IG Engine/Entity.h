#pragma once
#include <glad/glad.h>
#include "Graphics/Renderer.h"
//#include <GLFW/glfw3.h>
class Entity
{
public:
	Entity(): VBO(0),VAO(0),EBO(0)
	{

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(model), model, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	};
	~Entity() { }
	void draw(Renderer* renderer) 
	{ 
		renderer->drawLine(VAO,pos);
	};

	void setPos(glm::vec3 x) { pos = x; }
private:
	float model[6] = { 0.f, 0.f, 0.f,
					   1.f, 1.f, 0.f };

	//================================================================
	//= Facey
	//================================================================
	unsigned int indices[2] = {  // note that we start from 0!
	0, 1   // second Triangle
	};


	GLuint VBO;
	GLuint VAO;
	GLuint EBO;
	glm::vec3 pos;
};

