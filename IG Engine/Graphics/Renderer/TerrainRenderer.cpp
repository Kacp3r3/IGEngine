#include "TerrainRenderer.h"

TerrainRenderer::TerrainRenderer()
{
}

void TerrainRenderer::render(Terrain* t, Shader& s)
{
	/*s.use();
	s.setMat4("transformationMatrix", t->getTransformationMatrix());
	auto model = t->getModel();
	model->bindVAO();
	glBindTexture(GL_TEXTURE_2D, t->getTexture()->getID());
	glDrawElements(GL_TRIANGLES, model->getIndicesCount(), GL_UNSIGNED_INT, nullptr);*/
}
