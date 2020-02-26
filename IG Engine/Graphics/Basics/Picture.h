#pragma once
#include <memory>
#include <fstream>
#include <glm/glm.hpp>
#include "Graphics/Basics/Texture.h"

class Picture
{
public:
	Picture(std::string& path);

public:
	glm::vec4 getPixel(int x, int z);
	int getWidth();
	int getHeight();
	int getChannels();

private:
	std::unique_ptr<unsigned char[]> m_Picture;
	int m_nHeight;
	int m_nWidth;
	int m_nChannels;
};

