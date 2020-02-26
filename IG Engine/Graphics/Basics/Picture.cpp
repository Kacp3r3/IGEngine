#include "Picture.h"

Picture::Picture(std::string& path)
{
	unsigned char* x = stbi_load(path.c_str(), &m_nWidth, &m_nHeight, &m_nChannels, 0);
	if (x == nullptr)throw IGEXCEPTION(std::string("Nie wczytano " + path).c_str());
	int size = m_nWidth * m_nHeight * m_nChannels;
	m_Picture = std::make_unique<unsigned char[]>(size);
	

	for (int i = 0; i < size; ++i)
		m_Picture[i] = x[i];

	delete x;
}

glm::vec4 Picture::getPixel(int x, int z)
{
	auto ind = [&](int x, int z)
	{
		return (z * m_nWidth + x) * m_nChannels;
	};
	auto p = m_Picture.get();
	if (m_nChannels == 3)
		return glm::vec4(p[ind(x,z)]+1.f, p[ind(x,z)+1]+1.f, p[ind(x,z)+2]+1.f,0.f);
	else if (m_nChannels == 4)
		return glm::vec4(p[ind(x, z)] + 1.f, p[ind(x, z) + 1] + 1.f, p[ind(x, z) + 2] + 1.f, p[ind(x, z) + 3] + 1.f);
	else return glm::vec4(0.f, 0.f, 0.f, 0.f);
}

int Picture::getWidth()
{
	return m_nWidth;
}

int Picture::getHeight()
{
	return m_nHeight;
}

int Picture::getChannels()
{
	return m_nChannels;
}
