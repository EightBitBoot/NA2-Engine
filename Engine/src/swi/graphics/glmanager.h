#pragma once

#include "glcommon.h"

namespace nat {
	//Manages which vertex array and vertex buffer are currently bound.  All bindings and unbindings should redirect through here.
	class GLManager {
	public:
		GLManager();
		~GLManager();

		void bindVertexArray(GLuint vertexArray);
		void bindPreviousVertexArray();
		void unbindVertexArray();

		void bindVertexBuffer(GLuint vertexBuffer);
		void bindPreviousVertexBuffer();
		void unbindVertexBuffer();

		void useShader(GLuint program);
		void usePreviousShader();
		void unuseShader();

		inline GLuint getPreviousVertexArray()	const { return m_previousVertexArray; }
		inline GLuint getCurrentVertexArray()	const { return m_currentVertexArray; }

		inline GLuint getPreviousVertexBuffer()	const { return m_previousVertexBuffer; }
		inline GLuint getCurrentVertexBuffer()	const { return m_currentVertexBuffer; }

		inline GLuint getPreviousShader()		const { return m_previousShader; }
		inline GLuint getCurrentShader()		const { return m_currentShader; }

	private:
		GLuint m_previousVertexArray;
		GLuint m_currentVertexArray;

		GLuint m_previousVertexBuffer;
		GLuint m_currentVertexBuffer;

		GLuint m_previousShader;
		GLuint m_currentShader;
	};
}