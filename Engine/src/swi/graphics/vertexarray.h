#pragma once

#include<vector>

#include "glcommon.h"

#include "glmanager.h"
#include "vertexbuffer.h"

//Wrapper for the OpenGL vertex array object
class VertexArray {
public:
	VertexArray(GLManager* manager);
	~VertexArray();

	void addVertex(vertex vertex);
	void addVertices(vertex* vertices, int count);

	void pushFormat(GLenum type, int count);

	void bufferVertices();

	void bind();
	void unbind();

	void bindBuffer();
	void unbindBuffer();

private:
	VertexArray();

	void bindPrevious();

	std::vector<vertex> m_vertices;

	GLuint m_handle;
	
	VertexBuffer m_buffer;
	GLManager* m_manager;
	
	unsigned int m_nextFormatIndex;
	unsigned int m_nextFormatStride;
	unsigned int m_nextFormatPointer;
	bool m_bound;

public:
	inline GLint getOpenglName()	const	{ return m_handle; }
	inline bool isBound()			const	{ return m_bound; }
};