#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Utility/Enums.h"
#include "Entities/Entity.h"
#include "Graphics/Camera/Camera.h"

class Camera3rd : public Camera
{
public:
	Camera3rd() = delete;
	Camera3rd(Entity* toFollow);
	~Camera3rd()=default;

public:
	void processScroll(float vec);
	glm::mat4 getMatrix();
	void processKeyboard(Movement m, float dt);
	void processMouse(glm::vec2 offsets, bool constrain);
	void reset();


private:
	void calculateZoom(float offset);
	void calculatePitch(glm::vec2& offset);
	void calculateAngleAroundPlayer(glm::vec2& offset);
	float calculateHorizontalDistance();
	float calculateVerticalDistance();
	void calculatePosition(float h, float v);


public:
	void setAround(float x) { m_fAngleAround = x; }
	void setEntity(Entity* ent);
private:
	Entity* m_Entity;
	float m_fZoom;
	float m_fAngleAround;
};

