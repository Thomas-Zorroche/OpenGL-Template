#include "Renderer.h"

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	GLClearError();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0);
	GLCheckError();
}

void Renderer::Clear(float r, float g, float b, float a) const
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}
