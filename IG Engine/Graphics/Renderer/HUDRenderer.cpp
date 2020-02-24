#include "HUDRenderer.h"

HUDRenderer::HUDRenderer()
	:
	m_matOrtho(glm::ortho(-1.f, 1.f, -.55f, .55f, 0.1f, 100.f))
{
	m_Cursor = AssetManager::get().getModel("Plane");
	m_Cursor->setTexture(AssetManager::get().getTexture("Cursor"));
	m_matOrtho = glm::translate(m_matOrtho, glm::vec3(0.f, 0.f, -3.f));
	m_matOrtho = glm::scale(m_matOrtho, glm::vec3(0.06f, 0.06f, 0.06f));
}

void HUDRenderer::render(Shader& s)
{
	s.use();
	s.setMat4("model", m_matOrtho);
	m_Cursor->bindVAO();
	glBindTexture(GL_TEXTURE_2D, m_Cursor->getTexture());
	glDrawElements(GL_TRIANGLES, m_Cursor->getIndicesCount(), GL_UNSIGNED_INT, nullptr);
}
