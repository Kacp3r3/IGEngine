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
	Texture() {};
	Texture(const std::string& path);
	Texture(const std::vector<std::string>& vec);
	Texture(const Texture& txt)
	{
		m_Type = txt.m_Type;
		m_Path = txt.m_Path;
		m_nID = txt.m_nID;
	}
	~Texture();

public:
	void setID(GLuint x) { m_nID = x; };
	void setWidth(GLuint x) { m_nWidth=x; };
	void setHeight(GLuint x) { m_nHeight=x; };
	void setPath(std::string& x) { m_Path = x; };
	void setPath(const char* x) { m_Path = std::string(x); };
	void setType(std::string& x) { m_Type = x; };
	void setType(const char* x) { m_Type = std::string(x); };
public:
	GLuint getID() { return m_nID; };
	double getWidth() { return m_nWidth; };
	double getHeight() { return m_nHeight; };
	std::string getType() { return m_Type; };
	std::string getPath() { return m_Path; };

private:
	std::string m_Type;
	std::string m_Path;

private:
	GLuint m_nID;
	GLuint m_nWidth;
	GLuint m_nHeight;
};

#endif