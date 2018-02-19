#include "vertexbuffer.h"

VertexBuffer::VertexBuffer() : m_bound(false), m_openglName(0)
{
	GLCALL(glGenBuffers(1, &m_openglName));
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::bind()
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_openglName));
	m_bound = true;
}

void VertexBuffer::unbind()
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	m_bound = false;
}

void VertexBuffer::buffer(void* data, GLuint size)
{
	if (!m_bound) {
		GLint preveous = 0;
		GLCALL(glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &preveous));

		bind();
		GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
		unbind();

		GLCALL(glBindBuffer(GL_ARRAY_BUFFER, preveous));
	}
	else {
		GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
	}
}