#include "Graphics\Renderer\EntityRenderer.h"

void EntityRenderer::render(Entity* e, Shader& s)
{
	s.use();
	s.setMat4("transformationMatrix", e->getTransformationMatrix());
	auto model = e->getModel();
	model->bindVAO();
	glBindTexture(GL_TEXTURE_2D, model->getTexture());
	glDrawElements(GL_TRIANGLES, model->getIndicesCount(), GL_UNSIGNED_INT, nullptr);
}
