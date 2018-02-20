#include <iostream>

#include <math.h>

#include "graphics\glcommon.h"

#include "graphics\vertexarray.h"
#include "graphics\glmanager.h"


#include "math\mat4.h"
#include "shader.h"

void terminal_error(const char* message);
void glfwWindowResizeCallback(GLFWwindow* window, int width, int height);

int main()
{	
	//Initialize GLFW
	if (glfwInit() == GLFW_FALSE) {
		terminal_error("Failed to initialize GLFW!");
	}

	//Create the window
	GLFWwindow* window = glfwCreateWindow(600, 400, "Switch", NULL, NULL);
	if (!window) {
		terminal_error("Failed to create window!");
	}

	//Create OpenGL context
	glfwMakeContextCurrent(window);

	//Initialize GLEW
	if (glewInit() != GLEW_OK) {
		terminal_error("Failed to initialize GLEW!");
	}

	//Print environment information
	printf("OPENGL version: %s\n", glGetString(GL_VERSION));
	printf("GLFW version: %s\n", glfwGetVersionString());
	printf("GLEW version: %s\n", glewGetString(GLEW_VERSION));


	//Set the window background color to black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glfwSetWindowSizeCallback(window, &glfwWindowResizeCallback);

	//Mark the engine as running after environment initialization
	bool stopped = false;

	vertex vertices[] = {
		{ -0.5f,  0.5f },
		{ -0.5f, -0.5f },
		{  0.5f,  0.5f },
		{  0.5f,  0.5f },
		{  0.5f, -0.5f },
		{ -0.5f, -0.5f }
	};
	
	//Initialize an OpenGL manager
	GLManager manager;

	//Create a VertexArray for the rectangle
	VertexArray vertexArray(&manager);
	vertexArray.addVertices(vertices, 6);

	vertexArray.bufferVertices();
	
	//Define the position attribute
	vertexArray.pushFormat(GL_FLOAT, 2);

	//Generate shaders
	GLCALL(GLint vertexShaderID = glCreateShader(GL_VERTEX_SHADER));
	GLCALL(GLint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER));

	//Send shader sources to OpenGL (strings are defined in shader.h)
	GLCALL(glShaderSource(vertexShaderID, 1, &vertexShader, NULL));
	GLCALL(glShaderSource(fragmentShaderID, 1, &fragmentShader, NULL));

	//Compile vertex shader and print compilation messages
	GLint success = 0;
	GLCALL(glCompileShader(vertexShaderID));
	GLCALL(glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success));
	if (success == GL_FALSE) {
		GLint logLength = 0;
		GLCALL(glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &logLength));
		char errorMessage[1024];
		GLCALL(glGetShaderInfoLog(vertexShaderID, 1024, &logLength, errorMessage));
		printf("Vertex: "); terminal_error(errorMessage);
	}

	//Compile fragment shader and print compilation messages
	success = 0;
	GLCALL(glCompileShader(fragmentShaderID));
	GLCALL(glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success));
	if (success == GL_FALSE) {
		GLint logLength = 0;
		GLCALL(glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &logLength));
		char errorMessage[1024];
		GLCALL(glGetShaderInfoLog(fragmentShaderID, 1024, &logLength, errorMessage));
		printf("Fragment: ");  terminal_error(errorMessage);
	}

	//Generate shader program
	GLuint shaderProgramID = glCreateProgram();
	
	//Attach compiled shaders
	GLCALL(glAttachShader(shaderProgramID, vertexShaderID));
	GLCALL(glAttachShader(shaderProgramID, fragmentShaderID));

	GLCALL(glLinkProgram(shaderProgramID));
	
	//Clean up extra shaders
	GLCALL(glDetachShader(shaderProgramID, vertexShaderID));
	GLCALL(glDetachShader(shaderProgramID, fragmentShaderID));

	GLCALL(glDeleteShader(vertexShaderID));
	GLCALL(glDeleteShader(fragmentShaderID));

	//Get the uniform location of the rotation matrix in the shader programs
	GLCALL(GLint rotationMatLocation = glGetUniformLocation(shaderProgramID, "rotMat"));

	if (rotationMatLocation == -1) {
		terminal_error("Couldn't find uniform");
	}

	//Initialize an identity matrix for rotations
	mat4 matrix;

	matrix[0][0] = 1;
	matrix[1][1] = 1;
	matrix[2][2] = 1;
	matrix[3][3] = 1;

	//Angle to rotate the rectangle
	float angle = 0.0f;

	//MAIN LOOP
	while (!stopped) {
		GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		glfwPollEvents();

		//Adjust the angle if the left or right key is being pressed
		int leftState = glfwGetKey(window, GLFW_KEY_LEFT);
		if (leftState == GLFW_PRESS) {
			angle -= 0.01f;
		}

		int rightState = glfwGetKey(window, GLFW_KEY_RIGHT);
		if (rightState == GLFW_PRESS) {
			angle += 0.01f;
		}

		//Compute the rotation and store in the rotation matrix
		float negAngleCos = cos(-1.0f * angle);
		float negAngleSin = sin(-1.0f * angle);

		matrix[0][0] = negAngleCos;
		matrix[0][2] = negAngleSin;
		matrix[2][0] = negAngleSin;
		matrix[2][2] = negAngleCos;
		
		//Draw the rectangle
		vertexArray.bind();
		GLCALL(glUseProgram(shaderProgramID));
		GLCALL(glUniformMatrix4fv(rotationMatLocation, 1, GL_FALSE, &matrix[0][0]));
		GLCALL(glDrawArrays(GL_TRIANGLES, 0, 6));
		GLCALL(glUseProgram(0));
		vertexArray.unbind();

		//Present the final product
		glfwSwapBuffers(window);

		//Exit if the window is closed
		if (glfwWindowShouldClose(window)) {
			stopped = true;
		}
	}

	//Cleanup shader program
	GLCALL(glDeleteProgram(shaderProgramID));

	//Close the window
	glfwDestroyWindow(window);
	//Shutdown GLFW
	glfwTerminate();
	
	//Pause so log is readable
	getchar();

	return 0;
}

//Exit the program if a fatal error is encountered
void terminal_error(const char* message)
{
	printf(message);
	glfwTerminate();
	getchar();
	exit(-1);
}

//GLFW window callback that resizes the OpenGL Viewport to the new window dimensions
void glfwWindowResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}