#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "shaders.h"

GLuint initTriangle(void);

int main() {
	//Initalize

	if (!glfwInit()) {  //Test if GLFW failed to initalize
		printf("Failed to initalize GLFW!\n");
		getchar();
		return 1;
	}

	printf("GLFW version %s\n", glfwGetVersionString());

	GLFWwindow* window = nullptr;
	window = glfwCreateWindow(896, 504, "Switch", NULL, NULL);

	if (window == nullptr) {  //Test if there was a failure to create the window
		printf("Failed to create window!");
		glfwTerminate();
		getchar();
		return 1;
	}

	glfwMakeContextCurrent(window);

	GLenum glewInitStatus = glewInit();
	if (glewInitStatus != GLEW_OK) {  //Test if GLEW failed to initalize
		printf("Failed to initalize GLEW!\n");
		printf("%s\n", glewGetErrorString(glewInitStatus));
		getchar();
		return 1;
	}

	printf("GLEW version %s\n", glewGetString(GLEW_VERSION));
	printf("OpenGL version %s\n", glGetString(GL_VERSION));

	glClearColor(0.0f, 0.0f, 0.7, 1.0f);

	GLuint shaderProgram = initTriangle();  //Initalize shader program with triangle vertices

	
	//Main Loop

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glDrawArrays(GL_TRIANGLES, 0, 3);  //Draw the triangle
		glUseProgram(shaderProgram);

		glfwSwapBuffers(window);

	}

	glfwDestroyWindow(window);

	getchar();  //Pause to read the output if necessiary

	glfwTerminate();

	return 0;
}

/*
* Buffers vertices, compiles shaders, and creates a shader program to draw a triangle
* Returns shader program id
*/

GLuint initTriangle() {
	
	float vertices[] = {
		0.1f, 0.6f,
		0.4f, -0.7f,
	   -0.3f, -0.5f
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