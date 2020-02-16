#include "CameraHUD.h"

CameraHUD::CameraHUD(Texture* cur, Mesh* mesh)
	:
	m_Croshair()
	,ortho(glm::ortho(-1.f,1.f,-.55f,.55f,0.1f,100.f))
{
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
