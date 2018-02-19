#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>

extern void glClearErrors();
extern bool glCheckErrors(const char*, long line, const char* function);

#define GLCALL(x) glClearErrors(); x; if(!glCheckErrors(__FILE__, __LINE__, #x)) __debugbreak()

typedef struct vertex {
	float x;
	float y;
} vertex;
