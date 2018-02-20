#include "glmanager.h"


GLManager::GLManager() : m_previousVertexArray(0), m_currentVertexArray(0), m_previousVertexBuffer(0), m_currentVertexBuffer(0)
{
}

GLManager::~GLManager()
{
}

void GLManager::bindVertexArray(GLint vertexArray)
{
	m_previousVertexArray = m_currentVertexArray;
	m_currentVertexArray = vertexArray;
	GLCALL(glBindVertexArray(m_currentVertexArray));
}

void GLManager::bindPreviousVertexArray()
{
	GLint temp = m_currentVertexArray;
	m_currentVertexArray = m_previousVertexArray;
	m_previousVertexArray = temp;
	GLCALL(glBindVertexArray(m_currentVertexArray));
}

void GLManager::unbindVertexArray()
{
	m_previousVertexArray = m_currentVertexArray;
	m_currentVertexArray = 0;
	GLCALL(glBindVertexArray(m_currentVertexArray));
}

void GLManager::bindVertexBuffer(GLuint vertexBuffer)
{
	m_previousVertexBuffer = m_currentVertexBuffer;
	m_currentVertexBuffer = vertexBuffer;
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_currentVertexBuffer));
}

void GLManager::bindPreviousVertexBuffer()
{
	GLint temp = m_currentVertexBuffer;
	m_currentVertexBuffer = m_previousVertexBuffer;
	m_previousVertexBuffer = temp;
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_currentVertexBuffer));
}

void GLManager::unbindVertexBuffer()
{
	m_previousVertexBuffer = m_currentVertexBuffer;
	m_currentVertexBuffer = 0;
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_currentVertexBuffer));
}
