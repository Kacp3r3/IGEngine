#ifndef TEXTURE_H
#define TEXTURE_H

//================================================================
//= std Libs
//================================================================
#include <stb_image.h>
#include <glad/glad.h>
#include <string>
#include <vector>
#include "Utility\IGException.h"

//================================================================
//= my Libs
//================================================================
#include "Utility/Vec2.h"


//================================================================
//= Texture handling
//================================================================
class Texture
{

//================================================================
//= Ctor, Dtor
//================================================================
public:
	Texture() = delete;
	Texture(const std::string& Path, bool transparent);
	Texture(const std::string& Path, bool transparent, GLuint nSprites);
	Texture(const std::vector<std::string>& vec, bool png);
	~Texture();



//================================================================
//= Getters
//================================================================
	GLuint getID() { return m_nID; };
	double getWidth() { return m_nWidth; };
	double getHeight() { return m_nHeight; };
	GLuint getnSprites() { return m_nSprites; };

//================================================================
//= Setters
//================================================================
	void setID(GLuint x) { m_nID = x; };
	void setWidth(GLuint x) { m_nWidth=x; };
	void setHeight(GLuint x) { m_nHeight=x; };
	void setnSprites(GLuint x) { m_nSprites=x; };

//================================================================
//= Members
//================================================================
private:
	GLuint m_nID;
	GLuint m_nWidth;
	GLuint m_nHeight;
	GLuint m_nSprites;
};

#endif