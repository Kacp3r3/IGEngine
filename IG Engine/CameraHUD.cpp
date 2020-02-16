#include "CameraHUD.h"

CameraHUD::CameraHUD(Texture* cur)
	:
	m_Croshair()
	,ortho(glm::ortho(-1.f,1.f,-.55f,.55f,0.1f,100.f))
{
	Mesh mesh = {
		//Front
		{1.0f, 1.f, 1.f, //0
		 1.f, -1.f, 1.f,   //1
		-1.f, -1.f, 1.f,	  //2
		-1.f,  1.f, 1.f}
		,{0.f,1.f,
		  0.f,0.f,
		  1.f,0.f,
		  1.f,1.f}
		,{0,1,3, 1,2,3
		 }
	};;
	m_Croshair.addData(mesh);
	m_Croshair.setTexture(cur);
}

void CameraHUD::drawHUD(Shader& s, Renderer& gfx)
{
	//Croshair
	glm::mat4 cpos = ortho;
	cpos = glm::translate(cpos, glm::vec3(0.f, 0.f, -3.f));
	cpos = glm::scale(cpos, glm::vec3(0.03f, 0.03f, 0.03f));
	s.setMat4("model", cpos);
	gfx.drawModel(&m_Croshair);
}
