#include "Renderer.h"


Renderer::Renderer(int w, int h)
{
	//To ma byæ wywo³ane przed u¿yciem jakiejkolwiek tekstury
	proj = glm::perspective(glm::radians(45.0f), (float)w / (float)h, 0.1f, 100.0f);
	//glm::mat4 proj = glm::mat4(1.f);
	view = glm::mat4(1.f);
	view = glm::translate(view, glm::vec3(0.f, 0.f, -3.f));
}


void Renderer::renderClearFrame(float r, float g, float b)
{
	glClearColor(r,g,b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::renderTestFrame()
{
	/*m_SpriteSheetShader.use();
	glBindVertexArray(VAO);
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
	trans = glm::translate(trans, glm::vec3(sin(glfwGetTime()), cos(glfwGetTime()), 0.f));
	m_SpriteSheetShader.setMat4("transformation", trans);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);*/
}
//void Renderer::drawLine(float x1, float y1, float x2, float y2)
//{
//	glBindVertexArray(VAO);
//
//	//Magia z skalowaniem
//	x1 = 2 * x1 / Engine::SCR_WIDTH;
//	y1 = 2 * y1 / Engine::SCR_HEIGHT;
//
//	x2 = 2 * x2 / Engine::SCR_WIDTH;
//	y2 = 2 * y2 / Engine::SCR_HEIGHT;
//
//	//Update vertexow
//	model[0] = x1;
//	model[1] = y1;
//	model[3] = x2;
//	model[4] = y2;
//	
//	//Bindowanie
//	glBindBuffer(GL_ARRAY_BUFFER,VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(model), model, GL_DYNAMIC_DRAW);
//
//
//	//Rysowanie
//	glm::mat4 model = glm::mat4(1.f);
//	//m_SpriteSheetShader.setMat4("model", model);
//	glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
//
//	//Sprzatanie
//	glBindVertexArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//}
void Renderer::drawLine(GLuint& VAO,glm::vec3& translation)
{
	//m_SpriteSheetShader.use();
	glm::mat4 model = glm::mat4(1.f);
	model = glm::translate(model, translation);
	//m_SpriteSheetShader.setMat4("model", model);
	glBindVertexArray(VAO);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
 	glBindVertexArray(0);
}

void Renderer::drawModel(Model* m)
{
	glBindTexture(GL_TEXTURE_2D, m->getTexture());
	m->bindVAO();
	glDrawElements(GL_TRIANGLES, m->getIndicesCount(), GL_UNSIGNED_INT, nullptr);
}

//void Renderer::drawLetter(Vec2f pos, char letter, GLuint IdTexture, Vec2f scale, glm::vec4 color)
//{
//	float offsetx = (letter % 16)*0.0625f;
//	float offsety = (letter / 16) * 0.0625f;
//	//m_TextShader.use();
//	//m_TextShader.setFloat("offsetX", offsetx);
//	//m_TextShader.setFloat("offsetY", offsety);
//
//	glm::mat4 model = glm::mat4(1.0f);
//	model = glm::translate(model, glm::vec3(-m_fStartPosX, m_fStartPosY, 0.0f));
//	model = glm::translate(model, glm::vec3(m_fTranslateValueX*pos._x, -m_fTranslateValueY * pos._y, 0.0f));
//
//	model = glm::scale(model, glm::vec3(m_fScaleFactorX, m_fScaleFactorY, 0.0f));
//	model = glm::scale(model, glm::vec3(scale._x, scale._y , 0.0f));
//
//
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, IdTexture);
//
//	//m_TextShader.use();
//	//m_TextShader.setMat4("model", model);
//	glBindVertexArray(VAO);
//
//	
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//	glBindVertexArray(0);
//}

//void Renderer::setTextureCoords(GLuint x)
//{
//	m_SpriteSheetShader.use();
//	GLuint nr = x;
//	float offsetx = (float)(nr%32)* fOffsetShader;
//	float offsety = GLuint(nr / 32)* fOffsetShader;
//	// Just for fun
//	//if (nr == 8) offsety = 0.25f*(rand() % 4);
//	m_SpriteSheetShader.setFloat("offsetX", offsetx);
//	m_SpriteSheetShader.setFloat("offsetY", offsety);
//}
//
//void Renderer::setTextureCoords(Vec2i vec)
//{
//	m_SpriteSheetShader.use();
//	m_SpriteSheetShader.setFloat("offsetX", vec._x* fOffsetShader);
//	m_SpriteSheetShader.setFloat("offsetY", vec._y* fOffsetShader);
//}
//
//
//void Renderer::refreshCameraSettings()
//{
//	m_fScaleFactorX = 1.0f / m_Camera->getFov()._x;
//	m_fScaleFactorY = 1.0f / m_Camera->getFov()._y;
//
//	m_fStartPosX = 1 - m_fScaleFactorX;
//	m_fStartPosY = 1 - m_fScaleFactorY;
//
//	m_fTranslateValueX = 2 * m_fScaleFactorX;
//	m_fTranslateValueY = 2 * m_fScaleFactorY;
//}
//
//void Renderer::draw(Vec2f pos,Texture* texture)
//{
//
//	//==============================================================================
//
//	m_SpriteSheetShader.use();
//	//Eksperymentalnie udowodniono ze dziala xD
//	glm::mat4 model = glm::mat4(1.0f);
//	model = glm::translate(model, glm::vec3(-m_fStartPosX, m_fStartPosY, 0.0f));
//	model = glm::translate(model, glm::vec3(m_fTranslateValueX*pos._x, -m_fTranslateValueY * pos._y, 0.0f));
//	model = glm::translate(model, glm::vec3((float)m_Camera->getTranslate()._x, (float)m_Camera->getTranslate()._y, 0.0f));
//
//
//	//Skalowanko lepiej na koncu xD
//	//model = glm::scale(model, glm::vec3(scale > 0 ? scale:ScaleFactorX, scale > 0 ? scale : ScaleFactorY, 0.0f));
//	model = glm::scale(model, glm::vec3(m_fScaleFactorX, m_fScaleFactorY, 0.0f));
//	//if(big!=1.0)model = glm::scale(model, glm::vec3((float)big));
//
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, texture->getID());
//
//	m_SpriteSheetShader.use();
//
//	m_SpriteSheetShader.setMat4("model", model);
//	glBindVertexArray(VAO);
//	
//
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//	glBindVertexArray(0);
//}