#pragma once
#include "Graphics/Camera/Camera.h"

class CameraFirst : public Camera
{
public:
	CameraFirst() = delete;
	CameraFirst(glm::vec3 pos);

public:
	glm::mat4 getMatrix() override;
	void processKeyboard(Movement m, float dt);
	void processMouse(glm::vec2 offsets, bool constrain) override;
	void processScroll(float offsets) override;
	void reset();


public:
	void doubleSpeed();
	void normalSpeed();

public:
	void setFly(bool x) override;
	void setVelocity(float x) override;

public:
	glm::vec3 getFront() const;
	glm::vec3 getUp() const;
	float getVelocity() const override;
	bool getFly()const override;

	bool* ptrFly() override;
	float* ptrVelocity();

private:
	void updateCameraVectors();

private:
	bool m_bFly;//free
	float m_fVelocity;//Free
	glm::vec3 m_vecFront;//free
	glm::vec3 m_vecUp;//free
	glm::vec3 m_vecRight;//free
	glm::vec3 m_vecWorldUp;//free
};

