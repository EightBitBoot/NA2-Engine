#pragma once

#include <GL\glew.h>

class VertexBuffer {
public:
	VertexBuffer();
	~VertexBuffer();

	void bind();
	void unbind();

	void buffer(void* data, GLuint size);

private:
	GLuint m_openglName;
	bool m_bound;

public:
	inline bool isBound() const { return m_bound; }
};
