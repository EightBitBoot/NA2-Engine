#include "vertexarray.h"

VertexArray::VertexArray() : m_openglName(0), m_bound(false), m_nextFormatPointer(0), m_nextFormatStride(0), m_nextFormatIndex(0)
{
	GLCALL(glGenVertexArrays(1, &m_openglName));
}

VertexArray::~VertexArray()
{
}

void VertexArray::bind()
{
	GLCALL(glBindVertexArray(m_openglName));
	m_bound = true;
}

void VertexArray::unbind()
{
	GLCALL(glBindVertexArray(0));
	m_bound = false;
}

void VertexArray::addVertex(vertex vertex)
{
	m_vertices.push_back(vertex);
}

void VertexArray::addVertices(vertex* vertices, int count)
{
	for (int i = 0; i < count; i++) {
		m_vertices.push_back(vertices[i]);
	}
}

void VertexArray::bufferVertices()
{
	if (m_vertices.size() > 0) {
		if (!m_bound) {
			GLint previous;
			GLCALL(glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &previous));

			bind();
			m_buffer.buffer(&m_vertices[0], m_vertices.size() * sizeof(vertex));
			unbind();

			GLCALL(glBindVertexArray(previous));
		}
		else {
			m_buffer.buffer(&m_vertices[0], m_vertices.size() * sizeof(vertex));
		}
	}
}

void VertexArray::pushFormat(GLenum type, int count)
{	
	GLint previousArray;
	GLint previousBuffer;

	if (!isBound()) {
		GLCALL(glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &previousArray));
		bind();
	}

	if (!m_buffer.isBound()) {
		GLCALL(glGetIntegerv(GL_VERTEX_ARRAY_BUFFER_BINDING, &previousBuffer));
		m_buffer.bind();
	}

	switch (type) {
	case GL_FLOAT:
	default:
		GLCALL(glVertexAttribPointer(m_nextFormatIndex, count, type, false, m_nextFormatStride, (void*)m_nextFormatPointer));
		
		GLCALL(glEnableVertexAttribArray(m_nextFormatIndex));
		
		m_nextFormatStride += count * sizeof(float);
		m_nextFormatPointer += count * sizeof(float);
		m_nextFormatIndex++;
	}

	if (previousBuffer) {
		m_buffer.unbind();
		GLCALL(glBindBuffer(GL_ARRAY_BUFFER, previousBuffer));
	}

	if (previousArray) {
		unbind();
		GLCALL(glBindVertexArray(previousArray));
	}
}