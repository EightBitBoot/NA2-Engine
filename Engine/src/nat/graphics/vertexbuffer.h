#pragma once

#include "glcommon.h"

#include "glmanager.h"

namespace nat {
	//Wrapper for the OpenGL array buffer
	class VertexBuffer {
	public:
		VertexBuffer(GLManager* manager);
		~VertexBuffer();

		void bind();
		void unbind();

		void buffer(void* data, GLuint size);

		friend class VertexArray;

	private:
		VertexBuffer();

		void bindPrevious();

		GLuint m_handle;

		GLManager* m_manager;

		bool m_bound;

	public:
		inline GLint getOpenglName()	const { return m_handle; }
		inline bool isBound()			const { return m_bound; }
	};
}