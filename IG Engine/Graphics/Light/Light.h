#pragma once

#include <glm/glm.hpp>


class Light
{
public:
	Light(glm::vec3 pos, glm::vec3 color);


public:
	void setPos(glm::vec3 x);
	void setColor(glm::vec3 x);


public:
	glm::vec3 getPos();
	glm::vec3 getColor();


public:
	glm::vec3* ptrPos();
	glm::vec3* ptrColor();


private:
	glm::vec3 m_vecColor;
	glm::vec3 m_vecPos;
};

