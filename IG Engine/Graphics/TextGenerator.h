#pragma once
#include <vector>
//================================================================
//= std Libs
//================================================================
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

//================================================================
//= my Libs
//================================================================
#include "Renderer.h"


//================================================================
//= Text display handling
//================================================================
class TextGenerator
{

//================================================================
//= Ctor, Dtor
//================================================================
public:
	TextGenerator(Vec2f start,Texture* t, GLuint width, GLuint height);


//================================================================
//= Interface
//================================================================
	//void drawString(std::unique_ptr<Renderer>& gfx,std::string x);
	void drawText(std::unique_ptr<Renderer>& gfx);
	bool Update();

//================================================================
//= Setters
//================================================================
	void setText(std::vector<std::string>& lines);


//================================================================
//= Members
//================================================================
private:
	Texture* m_Texture;
	Vec2f m_vecfStartPos;
	GLuint m_nWidth;
	GLuint m_nHeight;
	float m_fLetterSize=0.5;
	std::vector<std::string> m_vecToShow;
};