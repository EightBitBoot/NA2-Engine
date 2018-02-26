#include "glmanager.h"


GLManager::GLManager() : m_previousVertexArray(0), m_currentVertexArray(0), m_previousVertexBuffer(0), m_currentVertexBuffer(0), m_previousShader(0), m_currentShader(0)
{
}

GLManager::~GLManager()
{
}

void GLManager::bindVertexArray(GLuint vertexArray)
{
	m_previousVertexArray = m_currentVertexArray;
	m_currentVertexArray = vertexArray;
	GLCALL(glBindVertexArray(m_currentVertexArray));
}

void GLManager::bindPreviousVertexArray()
{
	GLuint temp = m_currentVertexArray;
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
	GLuint temp = m_currentVertexBuffer;
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

void GLManager::useShader(GLuint shader)
{
	m_previousShader = m_currentShader;
	m_currentShader = shader;
	GLCALL(glUseProgram(m_currentShader));
}

void GLManager::usePreviousShader()
{
	GLuint temp = m_currentShader;
	m_currentShader = m_previousShader;
	m_previousShader = temp;
	GLCALL(glUseProgram(m_currentShader));
}

void GLManager::unuseShader()
{
	m_previousShader = m_currentShader;
	m_currentShader = 0;
	GLCALL(glUseProgram(m_currentShader));
}
