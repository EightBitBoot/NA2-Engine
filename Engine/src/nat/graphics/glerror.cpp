#include <iostream>

#include "glcommon.h"

//Clear all OpenGL errors in queue
static void gl_clear_errors()
{
	while (glGetError() != GL_NO_ERROR);
}

//Gets and prints all OpenGL errors.  Returns true if none are in queue.
static bool gl_check_errors(const char* file, long line, const char* function)
{
	bool success = true;;
	GLenum error;
	while (error = glGetError()) {
		switch (error) {
		case GL_INVALID_ENUM:
			printf("[GLERROR](GL_INVALID_ENUM): %s:%d \"%s\"\n", file, line, function);
			success = false;
			break;
		case GL_INVALID_VALUE:
			printf("[GLERROR](GL_INVALID_VALUE): %s:%d \"%s\"\n", file, line, function);
			success = false;
			break;
		case GL_INVALID_OPERATION:
			printf("[GLERROR](GL_INVALID_OPERATION): %s:%d \"%s\"\n", file, line, function);
			success = false;
			break;
		case GL_STACK_OVERFLOW:
			printf("[GLERROR](GL_STACK_OVERFLOW): %s:%d \"%s\"\n", file, line, function);
			success = false;
			break;
		case GL_STACK_UNDERFLOW:
			printf("[GLERROR](GL_STACK_UNDERFLOW): %s:%d \"%s\"\n", file, line, function);
			success = false;
			break;
		case GL_OUT_OF_MEMORY:
			printf("[GLERROR](GL_OUT_OF_MEMORY): %s:%d \"%s\"\n", file, line, function);
			success = false;
			break;
		default:
			printf("[GLERROR](UNKNOWN_ERROR): %s:%d \"%s\"\n", file, line, function);
			success = false;
			break;
		}
	}

	return success;
}