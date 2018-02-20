#include "vertexbuffer.h"

VertexBuffer::VertexBuffer(GLManager* manager) : m_openglName(0), m_manager(manager), m_bound(false)
{
	GLCALL(glGenBuffers(1, &m_openglName));
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::bind()
{
	m_manager->bindVertexBuffer(m_openglName);
	m_bound = true;
}

void VertexBuffer::unbind()
{
	m_manager->unbindVertexBuffer();
	m_bound = false;
}

void VertexBuffer::buffer(void* data, GLuint size)
{
	if (!m_bound) {
		bind();
		GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
		bindPrevious();
	}
	else {
		GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
	}
}

void VertexBuffer::bindPrevious()
{
	m_manager->bindPreviousVertexBuffer();
	m_bound = false;
}
