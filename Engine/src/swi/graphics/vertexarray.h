#pragma once

#include<vector>

#include <GL\glew.h>

#include "vertexbuffer.h"
#include "vertex.h"

class VertexArray {
public:
	VertexArray();
	~VertexArray();

	void addVertex(vertex vertex);
	void addVertices(vertex* vertices, int count);

	void pushFormat(GLenum type, int count);

	void bufferVertices();

	void bind();
	void unbind();

private:
	bool m_bound;
	GLuint m_openglName;
	std::vector<vertex> m_vertices;
	VertexBuffer m_buffer;
	unsigned int m_nextFormatIndex;
	unsigned int m_nextFormatStride;
	unsigned int m_nextFormatPointer;

public:
	inline bool isBound() const { return m_bound; }
};