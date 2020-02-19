#ifndef CAMERA_H
#define CAMERA_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Utility/Enums.h"


class Camera
{
public:
	Camera()=delete;
	Camera(glm::vec3 pos);
	~Camera();

public:
	glm::mat4 getMatrix();
	glm::mat4 getProjection();
	void processKeyboard(Movement m, float dt);
	void processMouse(glm::vec2&& offsets, bool constrain);
	void processScroll(float x);
	void updateProjection();
	void updateCameraVectors();
	void updatePos();
	void reset();


public:
	void doubleSpeed();
	void normalSpeed();

public:
	void setPos(const glm::vec3 pos);
	void setFov(float x);
	void setFar(float x);
	void setNear(float x);
	void setVelocity(float x);
	void setSensitivity(float x);
	void setHeight(float x);
	void setPitch(float x);
	void setYaw(float x);
	void setSpeed(float x);
	void setFly(bool x);
	

	glm::vec3 getPos() const;
	glm::vec3 getFront() const;
	glm::vec3 getUp() const;
	float getFov() const;
	float getYaw() const;
	float getPitch() const;
	float getFar()const;
	float getNear()const;
	float getVelocity()const;
	float getSensitivity()const;
	float getHeight()const;
	float getSpeed() const;
	bool getFly()const;

	//Imgui shortcut
	bool* ptrFly();
	float* ptrHeight();
	float* ptrNear();
	float* ptrFar();
	float* ptrVelocity();
	float* ptrSensitivity();
	float* ptrPitch();
	float* ptrYaw();
	float* ptrFov();

private:
	float m_fFov;
	float m_fYaw;
	float m_fPitch;
	float m_fHeight;
	float m_fSensitivity;
	float m_fVelocity;
	float m_fNear;
	float m_fFar;
	float m_fSpeed;
	bool m_bFly;
	glm::vec3 m_vecPos;
	glm::vec3 m_vecPosLast;
	glm::vec3 m_vecFront;
	glm::vec3 m_vecUp;
	glm::vec3 m_vecRight;
	glm::vec3 m_vecWorldUp;
	glm::mat4 m_matProjection;
};
#endif
