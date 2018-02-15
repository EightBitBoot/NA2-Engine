#include "vertexbuffer.h"

VertexBuffer::VertexBuffer() : m_bound(false), m_openglName(0)
{
	glGenBuffers(1, &m_openglName);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_openglName);
}

void VertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_openglName);
	m_bound = true;
}

void VertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_bound = false;
}

void VertexBuffer::buffer(void* data, GLuint size)
{
	if (!m_bound) {
		GLint preveous = 0;
		glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &preveous);

		bind();
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
		unbind();

		glBindBuffer(GL_ARRAY_BUFFER, preveous);
	}
	else {
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
	}
}