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
	Camera();
	~Camera();

public:
	virtual glm::mat4 getMatrix() = 0;
	virtual void processKeyboard(Movement m, float dt);
	virtual void processMouse(glm::vec2 offsets, bool constrain);
	virtual void processScroll(float offsets);
	virtual void reset();


	void updatePos() {};
public:
	

public:
	void setPos(const glm::vec3 pos);
	virtual void setVelocity(float x) {};
	void setSensitivity(float x);
	void setHeight(float x);
	void setPitch(float x);
	void setYaw(float x);
	void setSpeed(float x);
	virtual void setAround(float x) {};
	virtual void setFly(bool x) {};
	

	glm::vec3 getPos() const;
	float getYaw() const;
	float getPitch() const;
	virtual float getVelocity()const { return -1.f; };
	float getSensitivity()const;
	float getHeight() const;
	float getSpeed() const;
	virtual bool getFly()const { return false; };

	//Imgui shortcut
	virtual bool* ptrFly() { return nullptr; };
	float* ptrHeight();
	virtual float* ptrVelocity() { return nullptr; };
	float* ptrSensitivity();
	float* ptrPitch();
	float* ptrYaw();


protected:
	float m_fYaw;//Both
	float m_fPitch;//Both
	float m_fSensitivity;//Both
	float m_fSpeed;//Both
	float m_fHeight;//Both
	glm::vec3 m_vecPos;//Both
	glm::vec3 m_vecPosLast;//Both




	
};
#endif
