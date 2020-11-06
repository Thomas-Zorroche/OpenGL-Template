#pragma once

#include <glad/glad.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include <iostream>

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static void GLCheckError()
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] : " << error << std::endl;
	}
}

class Renderer
{
public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void Clear(float r = 0.1f, float g = 0.1f, float b = 0.15f, float a = 1.0f) const;
};