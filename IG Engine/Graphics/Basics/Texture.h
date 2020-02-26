#ifndef TEXTURE_H
#define TEXTURE_H


#include <stb_image.h>
#include <glad/glad.h>
#include <string>
#include <vector>


#include "Utility\IGException.h"


class Texture
{
public:
	Texture(const std::string& path, bool transparent);
	Texture(const std::vector<std::string>& vec, bool png);
	~Texture();

public:
	void setID(GLuint x) { m_nID = x; };
	void setWidth(GLuint x) { m_nWidth=x; };
	void setHeight(GLuint x) { m_nHeight=x; };
	
public:
	GLuint getID() { return m_nID; };
	double getWidth() { return m_nWidth; };
	double getHeight() { return m_nHeight; };


private:
	GLuint m_nID;
	GLuint m_nWidth;
	GLuint m_nHeight;
};

#endif