#ifndef CAMERA_H
#define CAMERA_H

//================================================================
//= std Libs
//================================================================
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>


//================================================================
//= My Libs
//================================================================
#include "Utility/Vec2.h"


//================================================================
//= Visible Area
//================================================================
class Camera
{

//================================================================
//= Ctor, Dtor
//================================================================
public:
	Camera()=delete;
	Camera(glm::vec3 pos);
	~Camera();


//================================================================
//= Interface
//================================================================
	void updatePos(const glm::vec3 pos);
	void setPos(const glm::vec3 pos);
	void updateYaw(float x);
	void updatePitch(float x);
	void updateFov(float x);
	void reset();
	
//================================================================
//= Getters
//================================================================
	float getFov();
	glm::vec3 getPos();
	glm::mat4 getView();
	glm::vec3 getFront();
	glm::vec3 getUp();
	float getYaw();
	float getPitch();

	bool* getFlight();
//================================================================
//= Setters
//================================================================
	void setFov(float x);


private:
	glm::vec3 m_vecPos;
	glm::vec3 m_vecFront;
	glm::vec3 m_vecUp;

	float m_fov;
	float m_yaw;
	float m_pitch;

	bool m_bAllowFlight;
	float m_CamHeight = 1.5f;
};
#endif
