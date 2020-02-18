#include "CameraHUD.h"

CameraHUD::CameraHUD(Texture* cur, Mesh* mesh)
	:
	m_Croshair()
	, m_matOrtho(glm::ortho(-1.f,1.f,-.55f,.55f,0.1f,100.f))
{
	m_Croshair.addData(mesh);
	m_Croshair.setTexture(cur);
	m_matOrtho = glm::translate(m_matOrtho, glm::vec3(0.f, 0.f, -3.f));
	m_matOrtho = glm::scale(m_matOrtho, glm::vec3(0.03f, 0.03f, 0.03f));
}

void CameraHUD::drawHUD(Shader& s, Renderer& gfx)
{
	//Croshair
	s.setMat4("model", m_matOrtho);
	gfx.drawModel(&m_Croshair);
}
