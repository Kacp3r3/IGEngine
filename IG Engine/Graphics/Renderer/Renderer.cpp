#include "Renderer.h"


Renderer::Renderer()
{
}


void Renderer::renderClearFrame(float r, float g, float b)
{
	glClearColor(r,g,b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::drawModel(Model* m)
{
	glBindTexture(GL_TEXTURE_2D, m->getTexture());
	m->bindVAO();
	glDrawElements(GL_TRIANGLES, m->getIndicesCount(), GL_UNSIGNED_INT, nullptr);
}