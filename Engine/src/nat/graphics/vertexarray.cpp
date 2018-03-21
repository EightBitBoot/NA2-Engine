#include "vertexarray.h"

namespace nat {
	VertexArray::VertexArray(GLManager* manager) : m_handle(0), m_buffer(manager), m_manager(manager), m_bound(false), m_nextFormatIndex(0), m_nextFormatStride(0), m_nextFormatPointer(0)
	{
		GLCALL(glGenVertexArrays(1, &m_handle));
	}

	VertexArray::~VertexArray()
	{
	}

	void VertexArray::bind()
	{
		m_manager->bindVertexArray(m_handle);
		m_bound = true;
	}

	void VertexArray::unbind()
	{
		m_manager->unbindVertexArray();
		m_bound = false;
	}

	void VertexArray::bindBuffer()
	{
		m_buffer.bind();
	}

	void VertexArray::unbindBuffer()
	{
		m_buffer.unbind();
	}

	void VertexArray::bindPrevious()
	{
		m_manager->bindPreviousVertexArray();
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
				bind();
				m_buffer.buffer(&m_vertices[0], m_vertices.size() * sizeof(vertex));
				bindPrevious();
			}
			else {
				m_buffer.buffer(&m_vertices[0], m_vertices.size() * sizeof(vertex));
			}
		}
	}

	void VertexArray::pushFormat(GLenum type, int count)
	{
		if (!isBound()) {
			bind();
		}

		if (!m_buffer.isBound()) {
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

		if (m_manager->getPreviousVertexBuffer() != m_buffer.getOpenglName())
		{
			m_buffer.bindPrevious();
		}

		if (m_manager->getPreviousVertexArray() != m_handle) {
			bindPrevious();
		}
	}
}