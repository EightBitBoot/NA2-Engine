#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "shaders.h"
#include "log\Log.h"

using namespace SWI;

GLuint initTriangle(int& numberOfVertices);
GLuint initRectangle(int& numberOfVertices);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

int main() {
	//Initalize
	if (!glfwInit()) {  //Test if GLFW failed to initalize
		Logger::getInstance()->log(Logger::LogLevelERROR, "Failed to initalize GLFW!");
		getchar();
		return 1;
	}

	Logger::getInstance()->log(Logger::LogLevelINFO, "GLFW version %s", glfwGetVersionString());

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow* window = nullptr;
	window = glfwCreateWindow(896, 504, "Switch", NULL, NULL);

	if (window == nullptr) {  //Test if there was a failure to create the window
		Logger::getInstance()->log(Logger::LogLevelERROR, "Failed to create window!");
		glfwTerminate();
		getchar();
		return 1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	GLenum glewInitStatus = glewInit();
	if (glewInitStatus != GLEW_OK) {  //Test if GLEW failed to initalize
		Logger::getInstance()->log(Logger::LogLevelERROR, "Failed to initalize GLEW");
		Logger::getInstance()->log(Logger::LogLevelERROR, "%s", glewGetErrorString(glewInitStatus));
		getchar();
		return 1;
	}

	Logger::getInstance()->log(Logger::LogLevelINFO, "GLEW version %s", glewGetString(GLEW_VERSION));
	Logger::getInstance()->log(Logger::LogLevelINFO, "OpenGL version %s", glGetString(GL_VERSION));

	glClearColor(0.0f, 0.0f, 0.7, 1.0f);

	int numberOfVertices;
	GLuint shaderProgram = initTriangle(numberOfVertices);  //Initalize shader program with triangle vertices
	// GLuint shaderProgram = initRectangle(numberOfVertices); //Initalize shader program with triangle vertices

	//Main Loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glDrawArrays(GL_TRIANGLES, 0, numberOfVertices);  //Draw the triangle
		glUseProgram(shaderProgram);

		glfwSwapBuffers(window);

	}

	glfwDestroyWindow(window);

	getchar();  //Pause to read the output if necessiary

	glfwTerminate();

	Logger::close();

	return 0;
}

/*
* Buffers vertices, compiles shaders, and creates a shader program to draw a triangle
* Returns shader program id
*/

GLuint initTriangle(int& numberOfVertices) {

	numberOfVertices = 3;

	float vertices[] = {
		-0.5f, -0.5f,
		 0.0f,  0.5f,
		 0.5f, -0.5f,
	};

	//Create Vertex Array Object
	GLuint vertexArrayObject;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	//Create Vertex Buffer Object
	GLuint vertexBufferObject;
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

	//Buffer Vertices
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Compile Vertex Shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//Compile Fragment Shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//Create and Link Shader Program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//Set Position Attribute
	GLuint positionAttribute = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(positionAttribute);

	return shaderProgram;
}

/*
* Buffers vertices, compiles shaders, and creates a shader program to draw a rectangle
* Returns shader program id
*/

GLuint initRectangle(int& numberOfVertices) {

	numberOfVertices = 6;

	float vertices[] = {
		-0.5f,  0.5f,
		 0.5f,  0.5f,
		-0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f, -0.5f,
		 0.5f, -0.5f
	};

	//Create Vertex Array Object
	GLuint vertexArrayObject;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	//Create Vertex Buffer Object
	GLuint vertexBufferObject;
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

	//Buffer Vertices
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Compile Vertex Shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//Compile Fragment Shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//Create and Link Shader Program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//Set Position Attribute
	GLuint positionAttribute = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(positionAttribute);

	return shaderProgram;

}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}