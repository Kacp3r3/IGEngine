#include "TerrainRenderer.h"

TerrainRenderer::TerrainRenderer()
{
}

void TerrainRenderer::render(Terrain* t, Shader& s)
{
	s.use();
	s.setMat4("transformationMatrix", t->getTransformationMatrix());
	t->getModel()->draw(s);
}
