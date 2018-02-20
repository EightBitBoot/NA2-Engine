#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>

extern void glClearErrors();
extern bool glCheckErrors(const char*, long line, const char* function);

//Macro for OpenGL error testing
#define GLCALL(x) glClearErrors(); x; if(!glCheckErrors(__FILE__, __LINE__, #x)) __debugbreak()

//Vertex data struct
typedef struct vertex {
	float x;
	float y;
} vertex;
