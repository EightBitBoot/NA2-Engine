#pragma once

#include "glcommon.h"

//Manages which vertex array and vertex buffer are currently bound.  All bindings and unbindindgs should redirect through here.
class GLManager {
public:
	GLManager();
	~GLManager();

	void bindVertexArray(GLint vertexArray);
	void bindPreviousVertexArray();
	void unbindVertexArray();
	void bindVertexBuffer(GLuint vertexBuffer);
	void bindPreviousVertexBuffer();
	void unbindVertexBuffer();

	inline GLint getPreviousVertexArray()	const { return m_previousVertexArray; }
	inline GLint getCurrentVertexArray()	const { return m_currentVertexArray; }
	inline GLuint getPreviousVertexBuffer()	const { return m_previousVertexBuffer; }
	inline GLuint getCurrentVertexBuffer()	const { return m_currentVertexBuffer; }

private:
	GLint m_previousVertexArray;
	GLint m_currentVertexArray;
	GLuint m_previousVertexBuffer;
	GLuint m_currentVertexBuffer;
};
