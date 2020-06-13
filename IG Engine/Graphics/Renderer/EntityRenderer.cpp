#include "Graphics\Renderer\EntityRenderer.h"

void EntityRenderer::render(Entity* e, Shader& s)
{
	s.setMat4("transformationMatrix", e->getTransformationMatrix());
	e->getModel()->draw(s);
	/*s.use();
	auto model = e->getModel();
	model->bindVAO();
	glBindTexture(GL_TEXTURE_2D, model->getTexture());
	glDrawElements(GL_TRIANGLES, model->getIndicesCount(), GL_UNSIGNED_INT, nullptr);*/
}
