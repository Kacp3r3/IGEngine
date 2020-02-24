//#include "CameraHUD.h"
//#include "Engine/Engine.h"
//CameraHUD::CameraHUD(Model* model, Texture* txt, Shader& s)
//	:
//	m_Croshair(model)
//	//, m_matOrtho(glm::ortho(0.f,static_cast<float>(Engine::SCR_WIDTH),0.f, static_cast<float>(Engine::SCR_HEIGHT),-1.f,1.f))
//	, m_matOrtho(glm::ortho(-1.f, 1.f, -.55f, .55f, 0.1f, 100.f))
//{
//	m_matOrtho = glm::translate(m_matOrtho, glm::vec3(0.f, 0.f, -3.f));
//	m_matOrtho = glm::scale(m_matOrtho, glm::vec3(0.06f, 0.06f, 0.06f));
//	m_Croshair->setTexture(txt);
//	glm::mat4 tmp(1.0f);
//	s.setMat4("transformationMatrix", tmp);
//	s.setMat4("projectionMatrix", m_matOrtho);
//	s.setMat4("viewMatrix", tmp);
//}
//
//void CameraHUD::drawHUD(Shader& s, RendererMaster& gfx)
//{
//	glm::mat4 tmp(1.0f);
//	s.setMat4("transformationMatrix", tmp);
//	s.setMat4("projectionMatrix", m_matOrtho);
//	s.setMat4("viewMatrix", tmp);
//	//Croshair
//	gfx.drawModel(m_Croshair);
//}
