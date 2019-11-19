#ifndef CAMERA_H
#define CAMERA_H

//================================================================
//= std Libs
//================================================================
#include <glad/glad.h>
#include <GLFW/glfw3.h>


//================================================================
//= My Libs
//================================================================
#include "../Utility/Vec2.h"


//================================================================
//= Visible Area
//================================================================
class Camera
{

//================================================================
//= Ctor, Dtor
//================================================================
public:
	Camera();
	Camera(GLuint width, GLuint height);
	~Camera();


//================================================================
//= Interface
//================================================================
	void initCamera(const Vec2f& pos, GLuint mapw, GLuint maph, GLuint wscreen, GLuint hscreen);
	void updateCamera(const Vec2f & pos);
	
//================================================================
//= Getters
//================================================================
	const Vec2f& getFov()const { return m_vecfFov; };
	const Vec2f& getTranslate()const { return m_vecfTranslateVector; };

//================================================================
//= Setters
//================================================================
	void setFov(float x);


private:
	Vec2f m_vecfTranslateVector;
	Vec2f m_vecfFov;
	Vec2f m_vecfScaleFactor;
	GLuint m_nWidth;
	GLuint m_nHeight;
};
#endif
