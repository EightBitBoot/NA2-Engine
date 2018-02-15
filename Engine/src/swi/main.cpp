#include <iostream>

#include <math.h>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "graphics\vertexarray.h"
#include "graphics\vertex.h"

#include "math\mat4.h"
#include "shader.h"

void terminal_error(const char* message);
void glfwWindowResizeCallback(GLFWwindow* window, int width, int height);

int main()
{
	if (glfwInit() == GLFW_FALSE) {
		terminal_error("Failed to initalize GLFW!");
	}

	GLFWwindow* window = glfwCreateWindow(600, 400, "Switch", NULL, NULL);
	if (!window) {
		terminal_error("Failed to create window!");
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		terminal_error("Failed to initalize GLEW!");
	}

	printf("OPENGL version: %s\n", glGetString(GL_VERSION));
	printf("GLFW version: %s\n", glfwGetVersionString());
	printf("GLEW version: %s\n", glewGetString(GLEW_VERSION));

	bool stopped = false;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glfwSetWindowSizeCallback(window, &glfwWindowResizeCallback);

	//float vertices[] = {
	//	-0.5f,  0.5f,
	//	-0.5f, -0.5f,
	//	 0.5f,  0.5f,
	//	 0.5f,  0.5f,
	//	 0.5f, -0.5f,
	//	-0.5f, -0.5f
	//};

	vertex vertices[] = {
		{ -0.5f,  0.5f },
		{ -0.5f, -0.5f },
		{  0.5f,  0.5f },
		{  0.5f,  0.5f },
		{  0.5f, -0.5f },
		{ -0.5f, -0.5f }
	};

	//GLuint vertexArrayID = -1;
	//glGenVertexArrays(1, &vertexArrayID);

	//if (vertexArrayID == -1) {
	//	terminal_error("Failed to create vao!");
	//}

	//glBindVertexArray(vertexArrayID);
	//
	//GLuint arrayBufferID = -1;
	//glGenBuffers(1, &arrayBufferID);

	//if (arrayBufferID == -1) {
	//	terminal_error("Failed to create vao!");
	//}

	//glBindBuffer(GL_ARRAY_BUFFER, arrayBufferID);

	//glBufferData(GL_ARRAY_BUFFER, 6 * (2 * sizeof(float)), vertices, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//glEnableVertexAttribArray(0);

	VertexArray vertexArray;
	vertexArray.addVertices(vertices, 6);
	vertexArray.bufferVertices();

	vertexArray.pushFormat(GL_FLOAT, 2);

	GLint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShaderID, 1, &vertexShader, NULL);
	glShaderSource(fragmentShaderID, 1, &fragmentShader, NULL);

	GLint success = 0;
	glCompileShader(vertexShaderID);
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		GLint logLength = 0;
		glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &logLength);
		char errorMessage[1024];
		glGetShaderInfoLog(vertexShaderID, 1024, &logLength, errorMessage);
		printf("Vertex: "); terminal_error(errorMessage);
	}

	success = 0;
	glCompileShader(fragmentShaderID);
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		GLint logLength = 0;
		glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &logLength);
		char errorMessage[1024];
		glGetShaderInfoLog(fragmentShaderID, 1024, &logLength, errorMessage);
		printf("Fragment: ");  terminal_error(errorMessage);
	}

	GLuint shaderProgramID = glCreateProgram();
	
	glAttachShader(shaderProgramID, vertexShaderID);
	glAttachShader(shaderProgramID, fragmentShaderID);

	glLinkProgram(shaderProgramID);
	
	glDetachShader(shaderProgramID, vertexShaderID);
	glDetachShader(shaderProgramID, fragmentShaderID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	GLint rotationMatLocation = glGetUniformLocation(shaderProgramID, "rotMat");

	if (rotationMatLocation == -1) {
		terminal_error("Couldn't find uniform");
	}

	mat4 matrix;

	matrix[0][0] = 1;
	matrix[1][1] = 1;
	matrix[2][2] = 1;
	matrix[3][3] = 1;


	float angle = 0.0f;

	while (!stopped) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwPollEvents();

		int leftState = glfwGetKey(window, GLFW_KEY_LEFT);
		if (leftState == GLFW_PRESS) {
			angle -= 0.01f;
		}

		int rightState = glfwGetKey(window, GLFW_KEY_RIGHT);
		if (rightState == GLFW_PRESS) {
			angle += 0.01f;
		}

		float negAngleCos = cos(-1.0f * angle);
		float negAngleSin = sin(-1.0f * angle);

		matrix[0][0] = negAngleCos;
		matrix[0][2] = negAngleSin;
		matrix[2][0] = negAngleSin;
		matrix[2][2] = negAngleCos;
		
		vertexArray.bind();
		glUseProgram(shaderProgramID);
		glUniformMatrix4fv(rotationMatLocation, 1, GL_FALSE, &matrix[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glUseProgram(0);
		vertexArray.unbind();

		glfwSwapBuffers(window);


		if (glfwWindowShouldClose(window)) {
			stopped = true;
		}
	}

	glDeleteProgram(shaderProgramID);

	glfwDestroyWindow(window);
	glfwTerminate();

	getchar();
	return 0;
}

void terminal_error(const char* message)
{
	printf(message);
	glfwTerminate();
	getchar();
	exit(-1);
}

void glfwWindowResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}